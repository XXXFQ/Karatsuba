#include <math.h>

#include "karatsuba/tree.hpp"

namespace karatsuba
{
    // 受け取った値を元にノードを作成する
    void Tree::Node::newNode(int value, const int N)
    {
        digits = N;

        // 値を直接格納する
        if (digits == 1) {
            values.push_back(value);
            return;
        }
        
        // 値を繰り下げて格納する
        if (digits < Utils::getDigit(value)) {
            for (int i = 0; value > 0; i++) {
                values.push_back(value % 10);
                value = value / 10;

                // 繰り下がり処理
                if (value != 0) {
                    values[i] += 10;
                    value -= 1;
                }

                // 配列に格納しきれない桁を、さらに繰り下げて格納する
                if (digits - 1 <= i && value > 0) {
                    values[i] += value * 10;
                    value = 0;
                }
            }
            return;
        }

        // 桁ごとの値を順番に格納する
        while (value != 0) {
            values.push_back(value % 10);
            value /= 10;
        }

        // 上位桁の0埋め処理
        while (values.size() < digits) {
            values.push_back(0);
        }
    }

    void Tree::Node::setValues(const std::vector<int> newValues)
    {
        values = newValues;
        digits = values.size();
    }

    int Tree::Node::getValue(const int index)
    {
        return values[index];
    }

    int Tree::Node::left(const int N)
    {
        int data = 0;
        for (int i = 0; i < N; i++) {
            data += values[values.size() - 1 - i] * pow(10, N - 1 - i);
        }
        return data;
    }

    int Tree::Node::right(const int N)
    {
        int data = 0;
        for (int i = 0; i < N; i++) {
            data += values[i] * pow(10, i);
        }
        return data;
    }

    Tree::Tree()
    {
    }

    Tree::Tree(const int data1, const int data2, const int N)
    {
        digits = N;
        value[0].newNode(data1, digits);
        value[1].newNode(data2, digits);
    }

    std::vector<int> Tree::getResult()
    {
        std::vector<int> resultValues;

        for (int i = 0; i < result.getDigits(); i++) {
            resultValues.push_back(result.getValue(i));
        }
        return resultValues;
    }

    // 演算結果を格納する処理
    void Tree::setResult(const int data, const int N)
    {
        result.newNode(data, N);
    }

    // 演算結果を配列ごと格納する処理
    void Tree::setResult(const std::vector<int> values)
    {
        result.setValues(values);
    }

    int Tree::getValue(int indexValue, int index)
    {
        if (index < 0 || index >= digits) {
            return 0;
        }
        return value[indexValue].getValue(index);
    }

    // nodeのvaluesのインデックスが大きい方のN個の要素を返す
    int Tree::left(const int index, const int N)
    {
        return value[index].left(N);
    }

    // nodeのvaluesのインデックスが小さい方のN個の要素を返す
    int Tree::right(const int index, const int N)
    {
        return value[index].right(N);
    }

    // left() + right()の結果を返す
    int Tree::lradd(const int index, const int N)
    {
        return left(index, N) + right(index, N);
    }

    // 桁ごとの加算を行う
    std::vector<int> Tree::add(std::vector<int> values1, std::vector<int> values2)
    {
        std::vector<int> resultValues;
        for (int i = 0; i < std::max(values1.size(), values2.size()); i++) {
            resultValues.push_back(0);
            if (i < values1.size()) {
                resultValues[i] += values1[i];
            }
            if (i < values2.size()) {
                resultValues[i] += values2[i];
            }
        }
        return resultValues;
    }

    // 桁ごとの減算を行う
    std::vector<int> Tree::sub(std::vector<int> values1, std::vector<int> values2)
    {
        std::vector<int> resultValues;
        for (int i = 0; i < std::min(values1.size(), values2.size()); i++) {
            int subData = values1[i] - values2[i];

            if (subData >= 0) {
                resultValues.push_back(subData);
            } else {
                // 減算結果が負の値の場合、繰り下げを行って正の値に調整する。
                int carryCount = subData / -10 + 1;
                resultValues.push_back(carryCount * 10 + subData);
                values1[i + 1] -= carryCount;
            }
        }
        return resultValues;
    }

    // valuesを10^k倍する。
    std::vector<int> Tree::shift(std::vector<int> values, int multiplier)
    {
        std::vector<int> resultValues;

        // 0埋め処理
        for (int k = 0; k < multiplier; k++) {
            resultValues.push_back(0);
        }

        // 値のシフト処理
        for (int i = 0; i < values.size(); i++) {
            resultValues.push_back(values[i]);
        }
        return resultValues;
    }

    // 繰り上がり・繰り下がり処理を行う
    std::vector<int> Tree::carry(std::vector<int> values)
    {
        int length = values.size();
        
        for (int i = 0; i < length; i++) {
            if (Utils::getDigit(values[i]) > 1) {
                int carry_count = values[i] / 10;
                values[i] %= 10;
                values[i + 1] += carry_count;
            }
        }
        return values;
    }
}