#include <math.h>

#include "karatsuba/utils.hpp"

namespace karatsuba
{
    unsigned Utils::get_digits(unsigned num)
    {
        return log10(num) + 1;
    }

    bool Utils::is_digit(char c)
    {
        return c >= '0' && c <= '9';
    }
}