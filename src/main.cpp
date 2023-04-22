#include "karatsuba.hpp"

#include <iostream>

int main(void)
{
    int values[2];
    size_t arraySize = sizeof(values) / sizeof(int);
    bool startFlag = false;

    for (int i = 0; i < arraySize; i++) {
        std::cout << "value_" << i << "? ";
        std::cin >> values[i];
    }

    // 計算結果を格納
    std::vector<int> answer = karatsuba::multiplication(values[0], values[1]);

    // 結果の表示
    if (answer.size() != 1) {
        for (int index = answer.size() - 1; index >= 0; index--) {
            if (!startFlag && answer[index] != 0) {
                startFlag = true;
            }
            if (startFlag) {
                std::cout << answer[index];
            }

        }
        std::cout << "" << std::endl;
    } else {
        std::cout << answer[0] << std::endl;
    }
    
    system("PAUSE");
    return 0;
}