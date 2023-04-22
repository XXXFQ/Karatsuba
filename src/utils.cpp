#include <math.h>

#include "karatsuba/utils.hpp"

namespace karatsuba
{
    unsigned Utils::getDigit(unsigned num)
    {
        return log10(num) + 1;
    }
}