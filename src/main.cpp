#include <iostream>

#include "karatsuba.hpp"

int main(void)
{
    std::string string_data[2];
    std::vector<std::vector<int>> values(2);

    // 値の入力
    for (int i = 0; i < values.size(); i++) {
        std::cout << "values " << i + 1 << " ? ";
        std::cin >> string_data[i];
        values[i] = karatsuba::stringToVector(string_data[i]);
    }

    // 配列が空の場合、関数を抜ける
    if (!values[0].size() || !values[1].size()) return 0;

    // 計算結果を格納
    const std::vector<int> answer = karatsuba::multiplyVectors(values[0], values[1]);

    // 結果の表示
    std::cout << "\nanswer = ";
    karatsuba::displayVector(answer);

    system("PAUSE");
    return 0;
}