#include <math.h>

#include "karatsuba/tree.hpp"

namespace karatsuba
{
    // 受け取った値を元にノードを作成する
    void Tree::Node::new_node(int node_data, const int digits)
    {
        this->digits_ = digits;

        // 値を直接格納する
        if (this->digits_ == 1) {
            this->values_.push_back(node_data);
            return;
        }
        
        // 値を繰り下げて格納する
        if (this->digits_ < Utils::get_digit(node_data)) {
            for (int i = 0; node_data > 0; i++) {
                this->values_.push_back(node_data % 10);
                node_data = node_data / 10;

                // 繰り下がり処理
                if (node_data != 0) {
                    this->values_[i] += 10;
                    node_data -= 1;
                }

                // 配列に格納しきれない桁を、さらに繰り下げて格納する
                if (this->digits_ - 1 <= i && node_data > 0) {
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
        while (this->values_.size() < this->digits_) {
            this->values_.push_back(0);
        }
    }

    void Tree::Node::set_values(const std::vector<int> values)
    {
        this->values_ = values;
        this->digits_ = values_.size();
    }

    int Tree::Node::left(const int count)
    {
        int data = 0;
        for (int i = 0; i < count; i++) {
            data += this->values_[this->values_.size() - 1 - i] * pow(10, count - 1 - i);
        }
        return data;
    }

    int Tree::Node::right(const int count)
    {
        int data = 0;
        for (int i = 0; i < count; i++) {
            data += this->values_[i] * pow(10, i);
        }
        return data;
    }

    Tree::Tree(const int data1, const int data2, const int digits)
    {
        this->digits_ = digits;
        this->value_[0].new_node(data1, digits_);
        this->value_[1].new_node(data2, digits_);
    }

    std::vector<int> Tree::get_result()
    {
        std::vector<int> result_values;

        for (int i = 0; i < this->result_.digits(); i++) {
            result_values.push_back(this->result_.get_value(i));
        }
        return result_values;
    }

    // 演算結果を格納する処理
    void Tree::set_result(const int data, const int count)
    {
        this->result_.new_node(data, count);
    }

    // 演算結果を配列ごと格納する処理
    void Tree::set_result(const std::vector<int> values)
    {
        this->result_.set_values(values);
    }

    int Tree::get_value(int index_value, int index)
    {
        if (index < 0 || index >= this->digits_) {
            return 0;
        }
        return this->value_[index_value].get_value(index);
    }

    // nodeのvaluesのインデックスが大きい方のN個の要素を返す
    int Tree::left(const int index, const int count)
    {
        return this->value_[index].left(count);
    }

    // nodeのvaluesのインデックスが小さい方のN個の要素を返す
    int Tree::right(const int index, const int count)
    {
        return this->value_[index].right(count);
    }

    // left() + right()の結果を返す
    int Tree::lradd(const int index, const int count)
    {
        return left(index, count) + right(index, count);
    }
}