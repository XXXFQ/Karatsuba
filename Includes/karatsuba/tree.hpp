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
            std::vector<int> values;
            int digits = 0;
        
        public:
            void newNode(int, int);
            void setValues(std::vector<int>);
            int getDigits() { return digits; };
            int getValue(int);
            int left(int);
            int right(int);
        };

        Node value[2];
        Node result;
        int digits = 0;
    
    public:
        Tree();
        Tree(int, int, int);
        void setResult(int, int);
        void setResult(const std::vector<int>);
        std::vector<int> getResult();
        int getValue(int, int);
        int left(int, int);
        int right(int, int);
        int lradd(int, int);
        int getDigits() { return digits; };
        static std::vector<int> add(std::vector<int>, std::vector<int>);
        static std::vector<int> sub(std::vector<int>, std::vector<int>);
        static std::vector<int> shift(std::vector<int>, int);
        static std::vector<int> carry(std::vector<int>);
    };
}

#endif