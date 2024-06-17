#include "karatsuba/vector_utils.hpp"

namespace karatsuba
{
    std::vector<int> VectorUtils::stringToVector(const std::string& str)
    {
        std::vector<int> result_values;
        bool is_negative = str[0] == '-';
        int start = is_negative ? 1 : 0;

        for (int i = str.length() - 1; i >= start; i--) {
            if (!std::isdigit(str[i])) return {0};
            result_values.push_back(str[i] - '0');
        }

        if (is_negative) {
            result_values.back() *= -1;
        }

        return result_values;
    }

    void VectorUtils::displayVector(const std::vector<int>& array)
    {
        std::vector<int> clean_array = VectorOperations::removeLeadingZeros(VectorOperations::handleCarry(array));
        if (clean_array.size() == 1) {
            std::cout << clean_array[0] << std::endl;
            return;
        }

        if (clean_array.back() < 0) {
            std::cout << '-';
            clean_array.back() *= -1;
        }

        for (int i = clean_array.size() - 1; i >= 0; i--) {
            std::cout << clean_array[i];
        }
        std::cout << std::endl;
    }
}