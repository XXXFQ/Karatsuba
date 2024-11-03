#include "karatsuba/vector_utils.hpp"

namespace karatsuba
{
    SignedVector VectorUtils::stringToSignedVector(const std::string& str)
    {
        std::vector<int> result_values;
        bool has_negative_sign = VectorUtils::hasNegativeSign(str); // Check if the string has a negative sign
        int start = has_negative_sign ? 1 : 0; // Start index for the loop

        // Convert string to vector
        for (int i = str.length() - 1; i >= start; i--) {
            if (!std::isdigit(str[i])) return SignedVector({}, false);
            result_values.push_back(str[i] - '0');
        }

        return SignedVector(result_values, has_negative_sign);
    }

    bool VectorUtils::hasNegativeSign(const std::string& str)
    {
        return str[0] == '-';
    }

    void VectorUtils::displayVector(const SignedVector& vector_values)
    {
        // Get the vector values
        std::vector<int> values = VectorOperations::removeLeadingZeros(VectorOperations::handleCarry(vector_values.getValues()));

        // Check if the vector is empty or contains only zeros
        if (values.empty() || (values.size() == 1 && values[0] == 0)) {
            std::cout << "0" << std::endl;
            return;
        }

        // Display the negative sign if the vector is negative
        if (vector_values.isNegative()) {
            std::cout << '-';
        }

        // Display the vector values
        for (auto it = values.rbegin(); it != values.rend(); ++it) {
            std::cout << *it;
        }
        std::cout << std::endl;
    }
}