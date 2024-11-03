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
        // 空文字列を除外
        if (str.empty()) return false;

        // 先頭が '-' であればそれ以降を数字としてチェック
        size_t start = (str[0] == '-') ? 1 : 0;

        // 残りの部分がすべて数字であるかを確認
        return start < str.size() && std::all_of(str.begin() + start, str.end(), [](char c) { return isdigit(c) != 0; });
    }
}