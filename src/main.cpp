#include <iostream>
#include "karatsuba.hpp"

using namespace karatsuba;

int main(int argc, char* argv[])
{
    std::string input_strings[2];
    SignedVector input_vectors[2];

    if (argc == 1) {
        for (int i = 0; i < 2; i++) {
            std::cout << "Enter value " << i + 1 << ": ";
            std::cin >> input_strings[i];

            // 入力が数値かどうかのチェック
            if (!NumberHelper::isNumber(input_strings[i])) {
                std::cerr << "Error: Invalid input. Please enter a valid number.\n";
                return 1;
            }
        }
    } else if (argc == 3) {
        input_strings[0] = argv[1];
        input_strings[1] = argv[2];

        for (int i = 0; i < 2; i++) {
            // 入力が数値かどうかのチェック
            if (!NumberHelper::isNumber(input_strings[i])) {
                std::cerr << "Error: Invalid input: " << input_strings[i] << ".\n";
                return 1;
            }
        }
    } else {
        std::cerr << "Usage: " << argv[0] << " <value1> <value2> (or run without arguments for interactive mode)\n";
        return 1;
    }

    // 文字列を SignedVector に変換
    for (int i = 0; i < 2; i++) {
        input_vectors[i] = VectorUtils::stringToSignedVector(input_strings[i]);
    }

    // どちらかの入力がゼロの場合はゼロを出力して終了
    if (input_vectors[0].isZero() || input_vectors[1].isZero()) {
        std::cout << "0\n";
        return 0;
    }

    // 乗算を実行
    SignedVector karatsuba_output = VectorOperations::multiplyVectors(input_vectors[0], input_vectors[1]);

    // 結果を出力
    VectorUtils::displayVector(karatsuba_output);

    return 0;
}