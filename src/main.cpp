#include <iostream>
#include "karatsuba.hpp"

using namespace karatsuba;

int main(void)
{
    std::string input_strings[2];
    SignedVector input_vectors[2];

    // Value input with validation
    for (int i = 0; i < 2; i++) {
        std::cout << "Enter value " << i + 1 << " ? ";
        std::cin >> input_strings[i];

        // Check if input is a number and within acceptable range
        if (!NumberHelper::isNumber(input_strings[i])) {
            std::cout << "Invalid input. Please enter a valid number.\n";
            return 1;
        }

        // Convert string to vector
        input_vectors[i] = VectorUtils::stringToVector(input_strings[i]);
    }

    // Check if either input is zero
    if (input_vectors[0].isZero() || input_vectors[1].isZero()) {
        std::cout << "One of the inputs is empty, exiting program.\\n";
        return 1;
    }

    // Perform multiplication
    SignedVector karatsuba_output = VectorOperations::multiplyVectors(input_vectors[0], input_vectors[1]);

    // Display result
    std::cout << "\nResult = ";
    VectorUtils::displayVector(karatsuba_output);

    return 0;
}