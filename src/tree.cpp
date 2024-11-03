#include "karatsuba/tree.hpp"

namespace karatsuba
{
    void Tree::Node::initializeNode(int node_data, const int digits)
    {
        this->digits_ = digits;

        // 1桁の場合は、直接格納する
        if (this->getDigitCount() == 1) {
            this->values_.push_back(node_data);
            return;
        }

        // 値を桁ごとに格納する
        if (this->getDigitCount() < NumberHelper::countDigits(node_data)) {
            for (int i = 0; node_data > 0; i++) {
                this->values_.push_back(node_data % 10);
                node_data = node_data / 10;

                // 繰り下がり処理
                if (node_data != 0) {
                    this->values_[i] += 10;
                    node_data--;
                }

                // 配列に格納しきれない桁を、さらに繰り下げて格納する
                if (this->getDigitCount() - 1 <= i && node_data > 0) {
                    this->values_[i] += node_data * 10;
                    node_data = 0;
                }
            }
            return;
        }

        // 桁ごとの値を順番に格納する
        while (node_data != 0) {
            this->values_.push_back(node_data % 10);
            node_data /= 10;
        }

        // 上位桁の0埋め処理
        while (this->values_.size() < this->getDigitCount()) {
            this->values_.push_back(0);
        }
    }

    Tree::Tree(const std::vector<int>& data1, const std::vector<int>& data2, const int digits)
    {
        this->digits_ = digits;
        this->value_[0].setValues(data1, this->getDigitCount());
        this->value_[1].setValues(data2, this->getDigitCount());
    }

    void Tree::Node::setValues(const std::vector<int>& values)
    {
        this->values_ = values;
        this->digits_ = values_.size();
    }

    void Tree::Node::setValues(const std::vector<int>& values, int digits)
    {
        this->setValues(values);
        this->digits_ = digits;

        // 値を桁ごとに調整する
        while (this->getValues().size() > this->getDigitCount()) {
            for (int i = 0; i < this->getValues().size() - 1; i++) {
                this->values_[i] += 10;
                this->values_[i + 1]--;
            }
            this->values_.pop_back();
        }

        // 上位桁の0埋め処理
        while (this->getValues().size() < this->getDigitCount()) {
            this->values_.push_back(0);
        }
    }

    void Tree::setResult(int data, int digits)
    {
        this->result_.initializeNode(data, digits);
    }

    void Tree::setResult(const std::vector<int>& values)
    {
        this->result_.setValues(values);
    }

    std::vector<int> Tree::getResult() const
    {
        std::vector<int> result_values;

        for (int i = 0; i < this->result_.getDigitCount(); i++) {
            result_values.push_back(this->result_.getValue(i));
        }
        return result_values;
    }

    int Tree::getValue(int node_index, int value_index) const
    {
        if (value_index < 0 || value_index >= this->getDigitCount()) {
            return 0;
        }
        return this->value_[node_index].getValue(value_index);
    }
}