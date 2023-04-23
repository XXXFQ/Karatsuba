#ifndef   KARATSUBA_KARATSUBA_HPP
#define   KARATSUBA_KARATSUBA_HPP

#include <vector>

namespace karatsuba
{
    std::vector<int> add(std::vector<int>, std::vector<int>);
    std::vector<int> sub(std::vector<int>, std::vector<int>);
    std::vector<int> shift(std::vector<int>, int);
    std::vector<int> carry(std::vector<int>);
    std::vector<int> multiplication(int, int);
}

#endif