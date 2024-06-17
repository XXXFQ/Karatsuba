#ifndef   KARATSUBA_MULTIPLIER_HPP
#define   KARATSUBA_MULTIPLIER_HPP

#include <math.h>
#include <iostream>
#include <vector>
#include "karatsuba/vector_operations.hpp"
#include "karatsuba/tree.hpp"

namespace karatsuba
{
    class Multiplier
    {
    public:
        /**
         * @brief Multiplies two vectors using Karatsuba algorithm.
         * @param vec1 The first vector to multiply.
         * @param vec2 The second vector to multiply.
         * @return A vector containing the result of the multiplication.
         */
        static std::vector<int> multiplyVectors(const std::vector<int>&, const std::vector<int>&);
    };
}

#endif