#ifndef   KARATSUBA_KARATSUBA_HPP
#define   KARATSUBA_KARATSUBA_HPP

#include <math.h>
#include <iostream>
#include <vector>

namespace karatsuba
{
    std::vector<int> left(std::vector<int>, int);
    std::vector<int> right(std::vector<int>, int);
    std::vector<int> lradd(std::vector<int>, int);
    std::vector<int> remove_zero_fill(std::vector<int>);
    std::vector<int> add(std::vector<int>, std::vector<int>);
    std::vector<int> sub(std::vector<int>, std::vector<int>);
    std::vector<int> shift(std::vector<int>, int);
    std::vector<int> carry(std::vector<int>);
    std::vector<int> mul(std::vector<int>, std::vector<int>);
    std::vector<int> convert_to_vector(std::string);
    void show_vector(std::vector<int>);
}

#endif