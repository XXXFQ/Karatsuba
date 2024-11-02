#include "karatsuba/vector_operations.hpp"

namespace karatsuba
{
    std::vector<int> VectorOperations::getLeftPart(const std::vector<int>& values, int count)
    {
        return std::vector<int>(values.begin(), values.begin() + count);
    }

    std::vector<int> VectorOperations::getRightPart(const std::vector<int>& values, int count)
    {
        return std::vector<int>(values.begin(), values.begin() + count);
    }

    std::vector<int> VectorOperations::addLeftAndRightParts(const std::vector<int>& values, int count)
    {
        return addVectors(getLeftPart(values, count), getRightPart(values, count));
    }

    std::vector<int> VectorOperations::removeLeadingZeros(const std::vector<int>& values)
    {
        auto vector_copy = values;
        while (vector_copy.size() > 1 && vector_copy.back() == 0) {
            vector_copy.pop_back();
        }
        return vector_copy;
    }

    std::vector<int> VectorOperations::addVectors(const std::vector<int>& left_vector, const std::vector<int>& right_vector)
    {
        std::vector<int> result(std::max(left_vector.size(), right_vector.size()), 0);

        for (size_t i = 0; i < result.size(); ++i) {
            if (i < left_vector.size()) result[i] += left_vector[i];
            if (i < right_vector.size()) result[i] += right_vector[i];
        }
        return result;
    }

    std::vector<int> VectorOperations::subtractVectors(const std::vector<int>& left_vector, const std::vector<int>& right_vector)
    {
        std::vector<int> result(std::max(left_vector.size(), right_vector.size()), 0);

        for (size_t i = 0; i < result.size(); ++i) {
            if (i < left_vector.size()) result[i] += left_vector[i];
            if (i < right_vector.size()) result[i] -= right_vector[i];
        }
        return result;
    }

    SignedVector VectorOperations::multiplyVectors(const SignedVector& left_vector, const SignedVector& right_vector)
    {
        const int left_hand_side_index = 0, right_hand_side_index = 1;
        bool result_is_negative = left_vector.isNegative() ^ right_vector.isNegative();

        // Perform carry handling
        auto left_hand_side = VectorOperations::handleCarry(left_vector.getValues());
        auto right_hand_side = VectorOperations::handleCarry(right_vector.getValues());

        // If either vector is zero, result is zero
        if (VectorOperations::isZero(left_hand_side) || VectorOperations::isZero(right_hand_side)) {
            return std::vector<int>{0};
        }

        // Prepare tree structure
        const int max_digits = std::max(left_hand_side.size(), right_hand_side.size());
        const int aligned_digits = static_cast<int>(pow(2, ceil(log2(max_digits)))); // Adjust to next power of 2
        const int tree_depth = static_cast<int>(log2(aligned_digits)) + 1;

        std::vector<Tree> tree_elements(1); // index 0 is unused
        std::vector<int> layer_start_index(2);

        // Calculate layer start indices
        layer_start_index[left_hand_side_index] = 0;
        layer_start_index[right_hand_side_index] = 1;
        for (int i = 1; i <= tree_depth - 1; i++) {
            layer_start_index.push_back(layer_start_index[i] + static_cast<int>(pow(3, i - 1)));
        }

        // Construct the tree
        tree_elements.emplace_back(Tree(left_hand_side, right_hand_side, aligned_digits));
        for (int depth = 1; depth <= tree_depth - 1; depth++) {
            const int nodes_in_layer = static_cast<int>(pow(3, depth - 1));
            for (int i = 1; i <= nodes_in_layer; i++) {
                Tree parent_node = tree_elements[layer_start_index[depth] + i - 1];

                int half_digit_count = parent_node.getDigitCount() / 2;

                // Add child nodes
                tree_elements.emplace_back(Tree(
                    VectorOperations::getLeftPart(parent_node.getValues(left_hand_side_index), half_digit_count),
                    VectorOperations::getLeftPart(parent_node.getValues(right_hand_side_index), half_digit_count),
                    half_digit_count
                ));
                tree_elements.emplace_back(Tree(
                    VectorOperations::getRightPart(parent_node.getValues(left_hand_side_index), half_digit_count),
                    VectorOperations::getRightPart(parent_node.getValues(right_hand_side_index), half_digit_count),
                    half_digit_count
                ));
                tree_elements.emplace_back(Tree(
                    VectorOperations::addLeftAndRightParts(parent_node.getValues(left_hand_side_index), half_digit_count),
                    VectorOperations::addLeftAndRightParts(parent_node.getValues(right_hand_side_index), half_digit_count),
                    half_digit_count
                ));
            }
        }

        // Calculate the lowest layer
        const int lowest_layer_nodes = static_cast<int>(pow(3, tree_depth - 1));
        for (int i = 1; i <= lowest_layer_nodes; i++) {
            Tree *element = &tree_elements[layer_start_index[tree_depth] + i - 1];
            int mul = element->getValue(left_hand_side_index, 0) * element->getValue(right_hand_side_index, 0);
            element->setResult((mul / 10 * 10) + (mul % 10), 2);
        }

        // Aggregate results from each layer
        for (int dp = tree_depth - 1; dp >= 1; dp--) {
            const int nodes_in_layer = static_cast<int>(pow(3, dp - 1));
            for (int i = 1; i <= nodes_in_layer; i++) {
                Tree *parent = &tree_elements[layer_start_index[dp] + i - 1];
                int cidx = layer_start_index[dp + 1] + (i - 1) * 3;

                // Calculate (γ - α - β)
                auto s1 = VectorOperations::subtractVectors(tree_elements[cidx + 2].getResult(), tree_elements[cidx].getResult());
                auto s2 = VectorOperations::subtractVectors(s1, tree_elements[cidx + 1].getResult());

                // Calculate α * 10^k
                auto p1 = VectorOperations::shiftVector(tree_elements[cidx].getResult(), parent->getDigitCount());

                // Calculate (γ - α - β) * 10^(k/2)
                auto p2 = VectorOperations::shiftVector(s2, parent->getDigitCount() / 2);

                parent->setResult(VectorOperations::addVectors(VectorOperations::addVectors(p1, p2), tree_elements[cidx + 1].getResult()));
            }
        }

        // Retrieve the result
        return SignedVector(tree_elements[layer_start_index[1]].getResult(), result_is_negative);
    }

    std::vector<int> VectorOperations::shiftVector(const std::vector<int>& values, int multiplier)
    {
        std::vector<int> result(values.size() + multiplier, 0);
        std::copy(values.begin(), values.end(), result.begin() + multiplier);
        return result;
    }

    std::vector<int> VectorOperations::handleCarry(std::vector<int> values)
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

    bool VectorOperations::isZero(const std::vector<int>& values)
    {
        return values.size() == 1 && values[0] == 0;
    }
}