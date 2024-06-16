#ifndef   KARATSUBA_KARATSUBA_HPP
#define   KARATSUBA_KARATSUBA_HPP

#include <math.h>
#include <iostream>
#include <vector>

namespace karatsuba
{
    /**
     * @brief Vectors from larger indices.
     * @param values The vector from which to extract elements.
     * @param count The number of elements to extract.
     * @return A vector containing the largest 'count' elements.
     */
    std::vector<int> getLeftPart(const std::vector<int>& values, int count);

    /**
     * @brief Vectors from smaller indices.
     * @param values The vector from which to extract elements.
     * @param count The number of elements to extract.
     * @return A vector containing the smallest 'count' elements.
     */
    std::vector<int> getRightPart(const std::vector<int>& values, int count);

    /**
     * @brief Adds the results of getLeftPart() and getRightPart().
     * @param values The vector from which to extract elements.
     * @param count The number of elements to extract and add.
     * @return A vector containing the sum of the left and right parts.
     */
    std::vector<int> addLeftAndRightParts(const std::vector<int>& values, int count);

    /**
     * @brief Removes leading zeros from the vector.
     * @param values The vector from which to remove leading zeros.
     * @return A vector without leading zeros.
     */
    std::vector<int> removeLeadingZeros(const std::vector<int>& values);

    /**
     * @brief Adds two vectors element-wise.
     * @param values1 The first vector to add.
     * @param values2 The second vector to add.
     * @return A vector containing the element-wise sum.
     */
    std::vector<int> addVectors(const std::vector<int>& values1, const std::vector<int>& values2);

    /**
     * @brief Subtracts two vectors element-wise.
     * @param values1 The vector from which to subtract.
     * @param values2 The vector to subtract.
     * @return A vector containing the element-wise difference.
     */
    std::vector<int> subtractVectors(const std::vector<int>& values1, const std::vector<int>& values2);

    /**
     * @brief Multiplies a vector by 10^k (shifts the vector).
     * @param values The vector to multiply.
     * @param multiplier The power of 10 to multiply by.
     * @return A vector multiplied by 10^k.
     */
    std::vector<int> shiftVector(const std::vector<int>& values, int multiplier);

    /**
     * @brief Carries over digits in a vector (handles overflow).
     * @param values The vector to process.
     * @return A vector with carried over digits.
     */
    std::vector<int> handleCarry(std::vector<int> values);

    /**
     * @brief Multiplies two vectors using Karatsuba algorithm.
     * @param values1 The first vector to multiply.
     * @param values2 The second vector to multiply.
     * @return A vector containing the result of the multiplication.
     */
    std::vector<int> multiplyVectors(const std::vector<int>& values1, const std::vector<int>& values2);

    /**
     * @brief Converts a string to a vector of integers.
     * @param str The string to convert.
     * @return A vector of integers representing the string.
     */
    std::vector<int> stringToVector(const std::string& str);

    /**
     * @brief Displays a vector of integers.
     * @param array The vector to display.
     */
    void displayVector(const std::vector<int>& array);
}

#endif