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
        // 先頭が負の数の場合、マイナス記号を除去
        if (str[0] == '-') {
            return std::all_of(str.begin() + 1, str.end(), [](char c) { return isdigit(c) != 0; });
        }
        return std::all_of(str.begin(), str.end(), [](char c) { return isdigit(c) != 0; });
    }
}