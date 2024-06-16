#include "karatsuba/karatsuba.hpp"
#include "karatsuba/tree.hpp"

namespace karatsuba
{
    std::vector<int> getLeftPart(const std::vector<int>& values, int count)
    {
        std::vector<int> result;
        for (int i = count - 1; i >= 0; --i) {
            result.push_back(values[values.size() - 1 - i]);
        }
        return result;
    }

    std::vector<int> getRightPart(const std::vector<int>& values, int count)
    {
        std::vector<int> result;
        for (int i = 0; i < count; ++i) {
            result.push_back(values[i]);
        }
        return result;
    }

    std::vector<int> addLeftAndRightParts(const std::vector<int>& values, int count)
    {
        return addVectors(getLeftPart(values, count), getRightPart(values, count));
    }

    std::vector<int> removeLeadingZeros(const std::vector<int>& values)
    {
        std::vector<int> result = values;
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        return result;
    }

    std::vector<int> addVectors(const std::vector<int>& values1, const std::vector<int>& values2)
    {
        std::vector<int> result(std::max(values1.size(), values2.size()), 0);
        for (size_t i = 0; i < result.size(); ++i) {
            if (i < values1.size()) {
                result[i] += values1[i];
            }
            if (i < values2.size()) {
                result[i] += values2[i];
            }
        }
        return result;
    }

    std::vector<int> subtractVectors(const std::vector<int>& values1, const std::vector<int>& values2)
    {
        std::vector<int> result(std::max(values1.size(), values2.size()), 0);
        for (size_t i = 0; i < result.size(); ++i) {
            if (i < values1.size()) {
                result[i] += values1[i];
            }
            if (i < values2.size()) {
                result[i] -= values2[i];
            }
        }
        return result;
    }

    std::vector<int> shiftVector(const std::vector<int>& values, int multiplier)
    {
        std::vector<int> result(values.size() + multiplier, 0);
        for (size_t i = 0; i < values.size(); ++i) {
            result[i + multiplier] = values[i];
        }
        return result;
    }

    std::vector<int> handleCarry(std::vector<int> values)
    {
        for (size_t i = 0; i < values.size(); i++) {
            // Borrowing process
            if (values[i] < 0) {
                int borrow = (abs(values[i]) + 9) / 10;
                values[i + 1] -= borrow;
                values[i] += borrow * 10;
            }

            // Carrying process
            if (values[i] >= 10) {
                if (i + 1 == values.size()) {
                    values.push_back(0);
                }
                int carry_count = values[i] / 10;
                values[i] %= 10;
                values[i + 1] += carry_count;
            }
        }
        return values;
    }

    std::vector<int> multiplyVectors(const std::vector<int>& values1, const std::vector<int>& values2)
    {
        // 1. キャリー処理を行う
        std::vector<int> lhs = handleCarry(values1);
        std::vector<int> rhs = handleCarry(values2);

        // 2. どちらかのベクトルが0の場合、結果は0となる
        if ((lhs.size() == 1 && lhs[0] == 0) || (rhs.size() == 1 && rhs[0] == 0)) {
            return std::vector<int>{0};
        }

        // 3. 木構造の準備
        const int max_digits = std::max(lhs.size(), rhs.size());
        const int aligned_digits = pow(2, ceil(log2(max_digits))); // 2の冪乗に調整
        const int tree_depth = log2(aligned_digits) + 1; // 木の深さを決定

        // 木構造の各要素を格納する配列を用意
        std::vector<Tree> tree_elements(1); // 0番目の要素はダミーで使わない
        std::vector<int> layer_start_index(2);

        const int value1_index = 0, value2_index = 1;
        
        // treeの各層の、elements配列上でのインデックスを算出。
        layer_start_index[value1_index] = 0;
        layer_start_index[value2_index] = 1;
        for (int i = 1; i <= tree_depth - 1; i++) {
            layer_start_index.push_back(layer_start_index[i] + pow(3, i - 1));
        }

        // 4. 木構造の構築
        tree_elements.push_back(Tree(lhs, rhs, aligned_digits));
        for (int depth = 1; depth <= tree_depth - 1; depth++) {
            for (int i = 1; i <= pow(3, depth - 1); i++) {
                // 親ノードの要素を取得
                Tree parent_node = tree_elements[layer_start_index[depth] + i - 1];

                // 子ノードの桁数を算出
                int half_digit_count = parent_node.getDigitCount() / 2;

                // 子ノードの追加
                tree_elements.push_back(
                    Tree(
                        getLeftPart(parent_node.getValues(value1_index), half_digit_count),
                        getLeftPart(parent_node.getValues(value2_index), half_digit_count),
                        half_digit_count
                    )
                );
                tree_elements.push_back(
                    Tree(
                        getRightPart(parent_node.getValues(value1_index), half_digit_count),
                        getRightPart(parent_node.getValues(value2_index), half_digit_count),
                        half_digit_count
                    )
                );
                tree_elements.push_back(
                    Tree(
                        addLeftAndRightParts(parent_node.getValues(value1_index), half_digit_count),
                        addLeftAndRightParts(parent_node.getValues(value2_index), half_digit_count),
                        half_digit_count
                    )
                );
            }
        }

        // 5. 最下層の計算
        for (int i = 1; i <= pow(3, tree_depth - 1); i++) {
            Tree *element = &tree_elements[layer_start_index[tree_depth] + i - 1];
            int mul = element->getValue(value1_index, 0) * element->getValue(value2_index, 0);
            element->setResult((mul / 10 * 10) + (mul % 10), 2);
        }

        // 6. 各層の計算結果を集計
        for (int dp = tree_depth - 1; dp >= 1; dp--) { // 最下層より一つ上の層から順に処理
            for (int i = 1; i <= pow(3, dp - 1); i++) { // 各層の要素数だけ繰り返す
                Tree *parent = &tree_elements[layer_start_index[dp] + i - 1];
                int cidx = layer_start_index[dp + 1] + (i - 1) * 3;

                // 「γ - α - β」の計算
                std::vector<int> s1 = subtractVectors(tree_elements[cidx + 2].getResult(), tree_elements[cidx].getResult());
                std::vector<int> s2 = subtractVectors(s1, tree_elements[cidx + 1].getResult());

                // 「α * 10^k」の計算
                std::vector<int> p1 = shiftVector(tree_elements[cidx].getResult(), parent->getDigitCount());

                // 「(γ - α - β) * 10^(k/2)」の計算
                std::vector<int> p2 = shiftVector(s2, parent->getDigitCount() / 2);

                parent->setResult(addVectors(addVectors(p1, p2), tree_elements[cidx + 1].getResult()));
            }
        }

        return tree_elements[layer_start_index[1]].getResult();
    }

    std::vector<int> stringToVector(const std::string& str)
    {
        std::vector<int> result_values;
        bool is_negative = str[0] == '-';
        int start = is_negative ? 1 : 0;

        for (int i = str.length() - 1; i >= start; i--) {
            if (!std::isdigit(str[i])) return {0};
            result_values.push_back(str[i] - '0');
        }

        if (is_negative) {
            result_values.back() *= -1;
        }

        return result_values;
    }

    void displayVector(const std::vector<int>& array)
    {
        std::vector<int> clean_array = removeLeadingZeros(handleCarry(array));
        if (clean_array.size() == 1) {
            std::cout << clean_array[0] << std::endl;
            return;
        }

        if (clean_array.back() < 0) {
            std::cout << '-';
            clean_array.back() *= -1;
        }

        for (int i = clean_array.size() - 1; i >= 0; i--) {
            std::cout << clean_array[i];
        }
        std::cout << std::endl;
    }
}