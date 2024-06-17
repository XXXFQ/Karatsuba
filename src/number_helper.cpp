#include <math.h>

#include "karatsuba/number_helper.hpp"

namespace karatsuba
{
    unsigned NumberHelper::countDigits(unsigned num)
    {
        return log10(num) + 1;
    }

    bool NumberHelper::isNumber(const std::string& str)
    {
        return std::all_of(str.begin(), str.end(), [](char c) { return isdigit(c) != 0; });
    }
}