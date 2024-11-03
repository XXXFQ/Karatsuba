#ifndef   KARATSUBA_VECTOR_UTILS_HPP
#define   KARATSUBA_VECTOR_UTILS_HPP

#include <iostream>
#include <vector>
#include "karatsuba/signed_vector.hpp"
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
        static SignedVector stringToSignedVector(const std::string&);

        /**
         * @brief Checks if a string has a negative sign.
         * @param str The string to check.
         * @return True if the string has a negative sign, false otherwise.
         */
        static bool hasNegativeSign(const std::string&);
        
        /**
         * @brief Displays a vector of integers.
         * @param vector_values The vector to display.
         */
        static void displayVector(const SignedVector&);
    };
}

#endif