#include "karatsuba/multiplier.hpp"

namespace karatsuba
{
    std::vector<int> Multiplier::multiplyVectors(const std::vector<int>& first_vector, const std::vector<int>& second_vector)
    {
        const int left_hand_side_index = 0, right_hand_side_index = 1;
        
        // 1. キャリー処理を行う
        std::vector<int> left_hand_side = VectorOperations::handleCarry(first_vector);
        std::vector<int> right_hand_side = VectorOperations::handleCarry(second_vector);

        // 2. どちらかのベクトルが0の場合、結果は0となる
        if (VectorOperations::isZero(left_hand_side) || VectorOperations::isZero(right_hand_side)) {
            return std::vector<int>{0};
        }

        // 3. 木構造の準備
        const int max_digits = std::max(left_hand_side.size(), right_hand_side.size());
        const int aligned_digits = pow(2, ceil(log2(max_digits))); // 2の冪乗に調整
        const int tree_depth = log2(aligned_digits) + 1; // 木の深さを決定

        // 木構造の各要素を格納する配列を用意
        std::vector<Tree> tree_elements(1); // 0番目の要素はダミーで使わない
        std::vector<int> layer_start_index(2);
        
        // treeの各層の、elements配列上でのインデックスを算出。
        layer_start_index[left_hand_side_index] = 0;
        layer_start_index[right_hand_side_index] = 1;
        for (int i = 1; i <= tree_depth - 1; i++) {
            layer_start_index.push_back(layer_start_index[i] + pow(3, i - 1));
        }

        // 4. 木構造の構築
        tree_elements.push_back(Tree(left_hand_side, right_hand_side, aligned_digits));
        for (int depth = 1; depth <= tree_depth - 1; depth++) {
            for (int i = 1; i <= pow(3, depth - 1); i++) {
                // 親ノードの要素を取得
                Tree parent_node = tree_elements[layer_start_index[depth] + i - 1];

                // 子ノードの桁数を算出
                int half_digit_count = parent_node.getDigitCount() / 2;

                // 子ノードの追加
                tree_elements.push_back(
                    Tree(
                        VectorOperations::getLeftPart(parent_node.getValues(left_hand_side_index), half_digit_count),
                        VectorOperations::getLeftPart(parent_node.getValues(right_hand_side_index), half_digit_count),
                        half_digit_count
                    )
                );
                tree_elements.push_back(
                    Tree(
                        VectorOperations::getRightPart(parent_node.getValues(left_hand_side_index), half_digit_count),
                        VectorOperations::getRightPart(parent_node.getValues(right_hand_side_index), half_digit_count),
                        half_digit_count
                    )
                );
                tree_elements.push_back(
                    Tree(
                        VectorOperations::addLeftAndRightParts(parent_node.getValues(left_hand_side_index), half_digit_count),
                        VectorOperations::addLeftAndRightParts(parent_node.getValues(right_hand_side_index), half_digit_count),
                        half_digit_count
                    )
                );
            }
        }

        // 5. 最下層の計算
        for (int i = 1; i <= pow(3, tree_depth - 1); i++) {
            Tree *element = &tree_elements[layer_start_index[tree_depth] + i - 1];
            int mul = element->getValue(left_hand_side_index, 0) * element->getValue(right_hand_side_index, 0);
            element->setResult((mul / 10 * 10) + (mul % 10), 2);
        }

        // 6. 各層の計算結果を集計
        for (int dp = tree_depth - 1; dp >= 1; dp--) { // 最下層より一つ上の層から順に処理
            for (int i = 1; i <= pow(3, dp - 1); i++) { // 各層の要素数だけ繰り返す
                Tree *parent = &tree_elements[layer_start_index[dp] + i - 1];
                int cidx = layer_start_index[dp + 1] + (i - 1) * 3;

                // 「γ - α - β」の計算
                std::vector<int> s1 = VectorOperations::subtractVectors(tree_elements[cidx + 2].getResult(), tree_elements[cidx].getResult());
                std::vector<int> s2 = VectorOperations::subtractVectors(s1, tree_elements[cidx + 1].getResult());

                // 「α * 10^k」の計算
                std::vector<int> p1 = VectorOperations::shiftVector(tree_elements[cidx].getResult(), parent->getDigitCount());

                // 「(γ - α - β) * 10^(k/2)」の計算
                std::vector<int> p2 = VectorOperations::shiftVector(s2, parent->getDigitCount() / 2);

                parent->setResult(VectorOperations::addVectors(VectorOperations::addVectors(p1, p2), tree_elements[cidx + 1].getResult()));
            }
        }

        return tree_elements[layer_start_index[1]].getResult();
    }
}