#include <math.h>
#include <vector>

#include "karatsuba/karatsuba.hpp"
#include "karatsuba/tree.hpp"

namespace karatsuba
{
    std::vector<int> multiplication(const int value1, const int value2)
    {
        if (value1 == 0 || value2 == 0) return std::vector<int>(1, 0);

        std::vector<Tree> elements(1);
        std::vector<int> layerTop(2);
        const int indexValue1 = 0, indexValue2 = 1;
        const int digits = pow(2, ceil(log2(std::max(Utils::getDigit(value1), Utils::getDigit(value2)))));
        const int t_depth = log2(digits) + 1;
        
        // treeの各層の、elements配列上でのインデックスを算出。
        layerTop[indexValue1] = 0;
        layerTop[indexValue2] = 1;
        for (int i = 1; i <= t_depth - 1; i++) {
            layerTop.push_back(layerTop[i] + pow(3, i - 1));
        }

        // treeを構築
        elements.push_back(Tree(value1, value2, digits));
        for (int dp = 1; dp <= t_depth - 1; dp++) {
            for (int i = 1; i <= pow(3, dp - 1); i++) {
                // 親ノードの要素を取得
                Tree parent = elements[layerTop[dp] + i - 1];

                // 子ノードの桁数を算出
                int cn = parent.getDigits() / 2;

                // 子ノードの追加
                elements.push_back(Tree(parent.left(indexValue1, cn), parent.left(indexValue2, cn), cn));
                elements.push_back(Tree(parent.right(indexValue1, cn), parent.right(indexValue2, cn), cn));
                elements.push_back(Tree(parent.lradd(indexValue1, cn), parent.lradd(indexValue2, cn), cn));
            }
        }

        // 最下層の計算
        for (int i = 1; i <= pow(3, t_depth - 1); i++) {
            Tree *element = &elements[layerTop[t_depth] + i - 1];
            int mul = element->getValue(indexValue1, 0) * element->getValue(indexValue2, 0);
            int value = (mul / 10 * 10) + (mul % 10);
            element->setResult(value, 2);
        }

        // 最下層以外の計算
        for (int dp = t_depth - 1; dp >= 1; dp--) { // 最下層より一つ上の層から順に処理
            for (int i = 1; i <= pow(3, dp - 1); i++) { // 各層の要素数だけ繰り返す
                Tree *parent = &elements[layerTop[dp] + i - 1];
                int cidx = layerTop[dp + 1] + (i - 1) * 3;

                // 「γ - α - β」の計算
                std::vector<int> s1 = Tree::sub(elements[cidx + 2].getResult(), elements[cidx].getResult());
                std::vector<int> s2 = Tree::sub(s1, elements[cidx + 1].getResult());

                // 「α * 10^k」の計算
                std::vector<int> p1 = Tree::shift(elements[cidx].getResult(), parent->getDigits());

                // 「(γ - α - β) * 10^(k/2)」の計算
                std::vector<int> p2 = Tree::shift(s2, parent->getDigits() / 2);

                // βを計算
                std::vector<int> p3 = elements[cidx + 1].getResult();

                parent->setResult(Tree::add(Tree::add(p1, p2), p3));
            }
        }

        return Tree::carry(elements[layerTop[1]].getResult());
    }
}