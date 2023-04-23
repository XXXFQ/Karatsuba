#include <math.h>

#include "karatsuba/utils.hpp"

namespace karatsuba
{
    unsigned Utils::get_digit(unsigned num)
    {
        return log10(num) + 1;
    }
}