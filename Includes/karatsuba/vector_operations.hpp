#ifndef   KARATSUBA_VECTOR_OPERATIONS_HPP
#define   KARATSUBA_VECTOR_OPERATIONS_HPP

#include <math.h>
#include <vector>

namespace karatsuba
{
    class VectorOperations
    {
    public:
        /**
         * @brief Vectors from larger indices.
         * @param values The vector from which to extract elements.
         * @param count The number of elements to extract.
         * @return A vector containing the largest 'count' elements.
         */
        static std::vector<int> getLeftPart(const std::vector<int>&, int);

        /**
         * @brief Vectors from smaller indices.
         * @param values The vector from which to extract elements.
         * @param count The number of elements to extract.
         * @return A vector containing the smallest 'count' elements.
         */
        static std::vector<int> getRightPart(const std::vector<int>&, int);

        /**
         * @brief Adds the results of getLeftPart() and getRightPart().
         * @param values The vector from which to extract elements.
         * @param count The number of elements to extract and add.
         * @return A vector containing the sum of the left and right parts.
         */
        static std::vector<int> addLeftAndRightParts(const std::vector<int>&, int);

        /**
         * @brief Removes leading zeros from the vector.
         * @param values The vector from which to remove leading zeros.
         * @return A vector without leading zeros.
         */
        static std::vector<int> removeLeadingZeros(const std::vector<int>&);

        /**
         * @brief Adds two vectors element-wise.
         * @param values1 The first vector to add.
         * @param values2 The second vector to add.
         * @return A vector containing the element-wise sum.
         */
        static std::vector<int> addVectors(const std::vector<int>&, const std::vector<int>&);

        /**
         * @brief Subtracts two vectors element-wise.
         * @param values1 The vector from which to subtract.
         * @param values2 The vector to subtract.
         * @return A vector containing the element-wise difference.
         */
        static std::vector<int> subtractVectors(const std::vector<int>&, const std::vector<int>&);

        /**
         * @brief Multiplies a vector by 10^k (shifts the vector).
         * @param values The vector to multiply.
         * @param multiplier The power of 10 to multiply by.
         * @return A vector multiplied by 10^k.
         */
        static std::vector<int> shiftVector(const std::vector<int>&, int);

        /**
         * @brief Carries over digits in a vector (handles overflow).
         * @param values The vector to process.
         * @return A vector with carried over digits.
         */
        static std::vector<int> handleCarry(std::vector<int>);

        /**
         * @brief Checks if a vector is zero.
         * @param values The vector to check.
         * @return True if the vector is zero, false otherwise.
         */
        static bool isZero(const std::vector<int>&);
    };
}

#endif