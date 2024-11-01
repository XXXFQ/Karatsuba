#include "karatsuba/vector_operations.hpp"

namespace karatsuba
{
    std::vector<int> VectorOperations::getLeftPart(const std::vector<int>& values, int count)
    {
        return std::vector<int>(values.end() - count, values.end());
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
        auto result = values;
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        return result;
    }

    std::vector<int> VectorOperations::addVectors(const std::vector<int>& values1, const std::vector<int>& values2)
    {
        std::vector<int> result(std::max(values1.size(), values2.size()), 0);
        for (size_t i = 0; i < result.size(); ++i) {
            if (i < values1.size()) result[i] += values1[i];
            if (i < values2.size()) result[i] += values2[i];
        }
        return result;
    }

    std::vector<int> VectorOperations::subtractVectors(const std::vector<int>& values1, const std::vector<int>& values2)
    {
        std::vector<int> result(std::max(values1.size(), values2.size()), 0);
        for (size_t i = 0; i < result.size(); ++i) {
            if (i < values1.size()) result[i] += values1[i];
            if (i < values2.size()) result[i] -= values2[i];
        }
        return result;
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