#ifndef   KARATSUBA_TREE_HPP
#define   KARATSUBA_TREE_HPP

#include <math.h>
#include <vector>

#include "karatsuba/number_helper.hpp"

namespace karatsuba
{
    class Tree
    {
    private:
        class Node
        {
        private:
            std::vector<int> values_;
            int digits_ = 0;
        
        public:
            void new_node(int, int);
            void set_values(std::vector<int>);
            void set_values(std::vector<int>, int);
            std::vector<int> get_values() const { return values_; };
            int get_value(int index) const { return values_[index]; };
            int digits() const { return digits_; };
        };

        Node value_[2];
        Node result_;
        int digits_ = 0;
    
    public:
        Tree() = default;
        Tree(std::vector<int>, std::vector<int>, int);
        void set_result(int, int);
        void set_result(const std::vector<int>);
        std::vector<int> get_result();
        std::vector<int> get_values(int index) const { return value_[index].get_values(); };
        int get_value(int, int);
        int digits() const { return digits_; };
    };
}

#endif