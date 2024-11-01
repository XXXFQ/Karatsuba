#include <iostream>
#include "karatsuba.hpp"

int main(void)
{
    std::string string_data[2];
    std::vector<std::vector<int>> values(2);

    // Value input with validation
    for (int i = 0; i < values.size(); i++) {
        std::cout << "Enter value " << i + 1 << " ? ";
        std::cin >> string_data[i];

        // Check if input is a number and within acceptable range
        if (!karatsuba::NumberHelper::isNumber(string_data[i])) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            return 1;
        }

        // Convert string to vector
        values[i] = karatsuba::VectorUtils::stringToVector(string_data[i]);
    }

    // If either array is empty, exit
    if (values[0].empty() || values[1].empty()) {
        std::cout << "One of the inputs is empty, exiting program.\n";
        return 1;
    }

    // Perform multiplication
    const std::vector<int> answer = karatsuba::Multiplier::multiplyVectors(values[0], values[1]);

    // Display result
    std::cout << "\nResult = ";
    karatsuba::VectorUtils::displayVector(answer);

    return 0;
}