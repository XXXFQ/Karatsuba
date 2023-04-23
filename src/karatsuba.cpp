#include <math.h>
#include <vector>

#include "karatsuba/karatsuba.hpp"
#include "karatsuba/tree.hpp"

namespace karatsuba
{
    // 桁ごとの加算を行う
    std::vector<int> add(std::vector<int> values1, std::vector<int> values2)
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
    std::vector<int> sub(std::vector<int> values1, std::vector<int> values2)
    {
        std::vector<int> result_values;
        for (int i = 0; i < std::min(values1.size(), values2.size()); i++) {
            int sub_data = values1[i] - values2[i];

            if (sub_data >= 0) {
                result_values.push_back(sub_data);
            } else {
                // 減算結果が負の値の場合、繰り下げを行って正の値に調整する。
                int carry_count = sub_data / -10 + 1;
                result_values.push_back(carry_count * 10 + sub_data);
                values1[i + 1] -= carry_count;
            }
        }
        return result_values;
    }

    // valuesを10^k倍する。
    std::vector<int> shift(std::vector<int> values, int multiplier)
    {
        std::vector<int> result_values;

        // 0埋め処理
        for (int k = 0; k < multiplier; k++) {
            result_values.push_back(0);
        }

        // 値のシフト処理
        for (int i = 0; i < values.size(); i++) {
            result_values.push_back(values[i]);
        }
        return result_values;
    }

    // 繰り上がり・繰り下がり処理を行う
    std::vector<int> carry(std::vector<int> values)
    {
        int length = values.size();
        
        for (int i = 0; i < length; i++) {
            if (Utils::get_digit(values[i]) > 1) {
                int carry_count = values[i] / 10;
                values[i] %= 10;
                values[i + 1] += carry_count;
            }
        }
        return values;
    }

    std::vector<int> multiplication(const int value1, const int value2)
    {
        if (!value1 || !value2) return std::vector<int>(1, 0);

        std::vector<Tree> elements(1);
        std::vector<int> layer_top(2);
        const int value1_index = 0, value2_index = 1;
        const int digits = pow(2, ceil(log2(std::max(Utils::get_digit(value1), Utils::get_digit(value2)))));
        const int t_depth = log2(digits) + 1;
        
        // treeの各層の、elements配列上でのインデックスを算出。
        layer_top[value1_index] = 0;
        layer_top[value2_index] = 1;
        for (int i = 1; i <= t_depth - 1; i++) {
            layer_top.push_back(layer_top[i] + pow(3, i - 1));
        }

        // treeを構築
        elements.push_back(Tree(value1, value2, digits));
        for (int dp = 1; dp <= t_depth - 1; dp++) {
            for (int i = 1; i <= pow(3, dp - 1); i++) {
                // 親ノードの要素を取得
                Tree parent = elements[layer_top[dp] + i - 1];

                // 子ノードの桁数を算出
                int cn = parent.digits() / 2;

                // 子ノードの追加
                elements.push_back(Tree(parent.left(value1_index, cn), parent.left(value2_index, cn), cn));
                elements.push_back(Tree(parent.right(value1_index, cn), parent.right(value2_index, cn), cn));
                elements.push_back(Tree(parent.lradd(value1_index, cn), parent.lradd(value2_index, cn), cn));
            }
        }

        // 最下層の計算
        for (int i = 1; i <= pow(3, t_depth - 1); i++) {
            Tree *element = &elements[layer_top[t_depth] + i - 1];
            int mul = element->get_value(value1_index, 0) * element->get_value(value2_index, 0);
            int value = (mul / 10 * 10) + (mul % 10);
            element->set_result(value, 2);
        }

        // 最下層以外の計算
        for (int dp = t_depth - 1; dp >= 1; dp--) { // 最下層より一つ上の層から順に処理
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

                // βを計算
                std::vector<int> p3 = elements[cidx + 1].get_result();

                parent->set_result(add(add(p1, p2), p3));
            }
        }

        return carry(elements[layer_top[1]].get_result());
    }
}