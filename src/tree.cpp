#include "karatsuba/tree.hpp"

namespace karatsuba
{
    // 受け取った値を元にノードを作成する
    void Tree::Node::new_node(int node_data, const int digits)
    {
        this->digits_ = digits;

        // 1桁の場合は、直接格納する
        if (this->digits() == 1) {
            this->values_.push_back(node_data);
            return;
        }
        
        // 値を繰り下げて格納する
        if (this->digits() < NumberHelper::get_digits(node_data)) {
            for (int i = 0; node_data > 0; i++) {
                this->values_.push_back(node_data % 10);
                node_data = node_data / 10;

                // 繰り下がり処理
                if (node_data != 0) {
                    this->values_[i] += 10;
                    node_data--;
                }

                // 配列に格納しきれない桁を、さらに繰り下げて格納する
                if (this->digits() - 1 <= i && node_data > 0) {
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
        while (this->values_.size() < this->digits()) {
            this->values_.push_back(0);
        }
    }

    void Tree::Node::set_values(const std::vector<int> values)
    {
        this->values_ = values;
        this->digits_ = values_.size();
    }

    void Tree::Node::set_values(const std::vector<int> values, int digits)
    {
        this->set_values(values);
        this->digits_ = digits;

        // 値を繰り下げて格納する
        while (this->get_values().size() > this->digits()) {
            for (int i = 0; i < this->get_values().size() - 1; i++) {
                this->values_[i] += 10;
                this->values_[i + 1]--;
            }
            this->values_.pop_back();
        }

        // 上位桁の0埋め処理
        while (this->get_values().size() < this->digits()) {
            this->values_.push_back(0);
        }
    }

    Tree::Tree(const std::vector<int> data1, const std::vector<int> data2, const int digits)
    {
        this->digits_ = digits;
        this->value_[0].set_values(data1, this->digits());
        this->value_[1].set_values(data2, this->digits());
    }

    // 演算結果を格納する処理
    void Tree::set_result(const int data, const int digits)
    {
        this->result_.new_node(data, digits);
    }

    // 演算結果を配列ごと格納する処理
    void Tree::set_result(const std::vector<int> values)
    {
        this->result_.set_values(values);
    }

    std::vector<int> Tree::get_result()
    {
        std::vector<int> result_values;

        for (int i = 0; i < this->result_.digits(); i++) {
            result_values.push_back(this->result_.get_value(i));
        }
        return result_values;
    }

    int Tree::get_value(int values_index, int index)
    {
        if (index < 0 || index >= this->digits()) {
            return 0;
        }
        return this->value_[values_index].get_value(index);
    }
}