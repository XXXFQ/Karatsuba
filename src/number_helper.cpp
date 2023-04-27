#include <math.h>

#include "karatsuba/number_helper.hpp"

namespace karatsuba
{
    unsigned NumberHelper::get_digits(unsigned num)
    {
        return log10(num) + 1;
    }

    bool NumberHelper::is_digit(char c)
    {
        return c >= '0' && c <= '9';
    }
}