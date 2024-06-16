#include <math.h>

#include "karatsuba/number_helper.hpp"

namespace karatsuba
{
    unsigned NumberHelper::countDigits(unsigned num)
    {
        return log10(num) + 1;
    }

    bool NumberHelper::isDigit(char c)
    {
        return c >= '0' && c <= '9';
    }
}