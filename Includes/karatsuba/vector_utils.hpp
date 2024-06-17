#ifndef   KARATSUBA_VECTOR_UTILS_HPP
#define   KARATSUBA_VECTOR_UTILS_HPP

#include <iostream>
#include <vector>
#include "karatsuba/vector_operations.hpp"

namespace karatsuba
{
    class VectorUtils
    {
    public:
        /**
         * @brief Converts a string to a vector of integers.
         * @param str The string to convert.
         * @return A vector of integers representing the string.
         */
        static std::vector<int> stringToVector(const std::string&);

        /**
         * @brief Displays a vector of integers.
         * @param array The vector to display.
         */
        static void displayVector(const std::vector<int>&);
    };
}

#endif