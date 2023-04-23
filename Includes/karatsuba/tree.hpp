#ifndef   KARATSUBA_TREE_HPP
#define   KARATSUBA_TREE_HPP

#include <vector>
#include "karatsuba/utils.hpp"

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
            int digits() const { return digits_; };
            int get_value(int index) const { return values_[index]; };
            int left(int);
            int right(int);
        };

        Node value_[2];
        Node result_;
        int digits_ = 0;
    
    public:
        Tree() = default;
        Tree(int, int, int);
        void set_result(int, int);
        void set_result(const std::vector<int>);
        std::vector<int> get_result();
        int get_value(int, int);
        int left(int, int);
        int right(int, int);
        int lradd(int, int);
        int digits() const { return digits_; };
    };
}

#endif