#include <iostream>

#include "karatsuba.hpp"

int main(void)
{
    std::string string_data[2];
    std::vector<std::vector<int>> values(2);

    for (int i = 0; i < values.size(); i++) {
        std::cout << "values " << i + 1 << " ? ";
        std::cin >> string_data[i];
        values[i] = karatsuba::convert_to_vector(string_data[i]);
    }

    // 配列が空の場合、関数を抜ける
    if (!values[0].size() || !values[1].size()) return 0;

    // 計算結果を格納
    std::vector<int> answer = karatsuba::mul(values[0], values[1]);

    // 結果の表示
    std::cout << "\nanswer = ";
    karatsuba::show_vector(answer);

    system("PAUSE");
    return 0;
}