#include "karatsuba/karatsuba.hpp"
#include "karatsuba/tree.hpp"

namespace karatsuba
{
    // valuesのインデックスが大きい方のN個の要素を返す
    std::vector<int> left(const std::vector<int> values, const int count)
    {
        std::vector<int> result_values;

        for (int i = count - 1; i >= 0; i--) {
            result_values.push_back(values[values.size() - 1 - i]);
        }
        return result_values;
    }

    // valuesのインデックスが小さい方のN個の要素を返す
    std::vector<int> right(const std::vector<int> values, const int count)
    {
        std::vector<int> result_values;

        for (int i = 0; i < count; i++) {
            result_values.push_back(values[i]);
        }
        return result_values;
    }

    // left() + right()の結果を返す
    std::vector<int> lradd(const std::vector<int> values, const int count)
    {
        return add(left(values, count), right(values, count));
    }

    // 上位桁の0を除去する
    std::vector<int> remove_zero_fill(std::vector<int> values)
    {
        for (int i = values.size() - 1; i > 0; i--) {
            if (values[i]) break;
            values.pop_back();
        }
        return values;
    }

    // 桁ごとの加算を行う
    std::vector<int> add(const std::vector<int> values1, const std::vector<int> values2)
    {
        std::vector<int> result_values;

        for (int i = 0; i < std::max(values1.size(), values2.size()); i++) {
            result_values.push_back(0);
            if (i < values1.size()) {
                result_values[i] += values1[i];
            }
            if (i < values2.size()) {
                result_values[i] += values2[i];
            }
        }
        return result_values;
    }

    // 桁ごとの減算を行う
    std::vector<int> sub(const std::vector<int> values1, const std::vector<int> values2)
    {
        std::vector<int> result_values;

        for (int i = 0; i < std::max(values1.size(), values2.size()); i++) {
            result_values.push_back(0);
            if (i < values1.size()) {
                result_values[i] += values1[i];
            }
            if (i < values2.size()) {
                result_values[i] -= values2[i];
            }
        }
        return result_values;
    }

    // valuesを10^k倍する。
    std::vector<int> shift(const std::vector<int> values, const int multiplier)
    {
        std::vector<int> result_values;

        // 0埋め処理
        for (int k = 0; k < multiplier; k++) {
            result_values.push_back(0);
        }

        // 値のシフト処理
        for (int value : values) {
            result_values.push_back(value);
        }
        return result_values;
    }

    // 繰り上がり・繰り下がり処理を行う
    std::vector<int> carry(std::vector<int> values)
    {
        for (int i = 0; i < values.size(); i++) {
            // 繰り下がり処理
            if (values[i] < 0 && i + 1 < values.size()) {
                int carry_count = values[i] / -10 + 1;
                values[i] += carry_count * 10;
                values[i + 1] -= carry_count;
            }

            // 繰り上がり処理
            if (values[i] >= 0 && Utils::get_digits(values[i]) > 1) {
                if (i + 1 >= values.size()) {
                    values.push_back(0);
                }
                int carry_count = values[i] / 10;
                values[i] %= 10;
                values[i + 1] += carry_count;
            }
        }
        return values;
    }

    // 2つの配列value1とvalue2の乗算を行う
    std::vector<int> mul(std::vector<int> value1, std::vector<int> value2)
    {
        value1 = carry(value1);
        value2 = carry(value2);

        // 配列に0のみ格納されていたら、演算結果の0を返す
        if ((!value1[0] && value1.size() == 1) || (!value2[0] && value2.size() == 1)) {
            return std::vector<int>(1, 0);
        }

        // elements配列の初期化
        std::vector<Tree> elements(1); // 0番目の要素はダミーで使わない
        std::vector<int> layer_top(2); // 各層の先頭要素のインデックスを保持
        const int digits = pow(2, ceil(log2(std::max(value1.size(), value2.size())))); // 2の冪乗になるように桁数を決定
        const int tree_depth = log2(digits) + 1; // treeの深さを決定
        const int value1_index = 0, value2_index = 1;
        
        // treeの各層の、elements配列上でのインデックスを算出。
        layer_top[value1_index] = 0;
        layer_top[value2_index] = 1;
        for (int i = 1; i <= tree_depth - 1; i++) {
            layer_top.push_back(layer_top[i] + pow(3, i - 1));
        }

        // treeを構築
        elements.push_back(Tree(value1, value2, digits));
        for (int dp = 1; dp <= tree_depth - 1; dp++) {
            for (int i = 1; i <= pow(3, dp - 1); i++) {
                // 親ノードの要素を取得
                Tree parent = elements[layer_top[dp] + i - 1];

                // 子ノードの桁数を算出
                int cn = parent.digits() / 2;

                // 子ノードの追加
                elements.push_back(Tree(left(parent.get_values(value1_index), cn), left(parent.get_values(value2_index), cn), cn));
                elements.push_back(Tree(right(parent.get_values(value1_index), cn), right(parent.get_values(value2_index), cn), cn));
                elements.push_back(Tree(lradd(parent.get_values(value1_index), cn), lradd(parent.get_values(value2_index), cn), cn));
            }
        }

        // 最下層の計算
        for (int i = 1; i <= pow(3, tree_depth - 1); i++) {
            Tree *element = &elements[layer_top[tree_depth] + i - 1];
            int mul = element->get_value(value1_index, 0) * element->get_value(value2_index, 0);
            element->set_result((mul / 10 * 10) + (mul % 10), 2);
        }

        // 最下層以外の計算
        for (int dp = tree_depth - 1; dp >= 1; dp--) { // 最下層より一つ上の層から順に処理
            for (int i = 1; i <= pow(3, dp - 1); i++) { // 各層の要素数だけ繰り返す
                Tree *parent = &elements[layer_top[dp] + i - 1];
                int cidx = layer_top[dp + 1] + (i - 1) * 3;

                // 「γ - α - β」の計算
                std::vector<int> s1 = sub(elements[cidx + 2].get_result(), elements[cidx].get_result());
                std::vector<int> s2 = sub(s1, elements[cidx + 1].get_result());

                // 「α * 10^k」の計算
                std::vector<int> p1 = shift(elements[cidx].get_result(), parent->digits());

                // 「(γ - α - β) * 10^(k/2)」の計算
                std::vector<int> p2 = shift(s2, parent->digits() / 2);

                parent->set_result(add(add(p1, p2), elements[cidx + 1].get_result()));
            }
        }
        return elements[layer_top[1]].get_result();
    }

    std::vector<int> convert_to_vector(std::string str)
    {
        std::vector<int> result_values;

        for (int i = str.length() - 1; i >= 0; i--) {
            char c = str[i];

            // 数値以外の文字があった場合、関数を抜ける
            if (i && !std::isdigit(c)) return std::vector<int>(0);
            if (!i && !std::isdigit(c) && str[0] != '-') return std::vector<int>(0);
            if (!std::isdigit(c)) break;

            result_values.push_back(int(c - '0'));
        }

        if (str[0] == '-') {
            result_values[result_values.size() - 1] *= -1;
        }

        return result_values;
    }

    // 結果の表示
    void show_vector(std::vector<int> array)
    {
        array = remove_zero_fill(carry(array));
        if (array.size() == 1) {
            std::cout << array[0] << std::endl;
            return;
        }

        for (int index = array.size() - 1; index >= 0; index--) {
            std::cout << array[index];
        }
        std::cout << "" << std::endl;
    }
}