#ifndef   KARATSUBA_NUMBER_HELPER_HPP
#define   KARATSUBA_NUMBER_HELPER_HPP

#include <iostream>
#include <algorithm>

namespace karatsuba
{
    class NumberHelper
    {
    public:
        /**
         * @brief 数値の桁数を数える。
         * @param num 桁数を数える数値。
         * @return 桁数。
         */
        static unsigned countDigits(unsigned);

        /**
         * @brief 文字列が数値かどうかを判定する。
         * @param str 判定する文字列。
         * @return 数値の場合はtrue、それ以外はfalse。
         */
        static bool isNumber(const std::string&);
    };
}

#endif