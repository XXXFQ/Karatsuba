#ifndef KARATSUBA_TREE_HPP
#define KARATSUBA_TREE_HPP

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
            std::vector<int> values_;  ///< ノードの値を格納するベクトル
            int digits_ = 0;           ///< ノードの桁数

        public:
            /**
             * @brief ノードに新しい値を設定する。
             * @param node_data 新しい値。
             * @param digits 桁数。
             */
            void initializeNode(int node_data, int digits);

            /**
             * @brief ノードにベクトルの値を設定する。
             * @param values 設定するベクトル。
             */
            void setValues(const std::vector<int>& values);

            /**
             * @brief ノードにベクトルの値と桁数を設定する。
             * @param values 設定するベクトル。
             * @param digits 設定する桁数。
             */
            void setValues(const std::vector<int>& values, int digits);

            /**
             * @brief ノードの値を取得する。
             * @return ノードの値を格納したベクトル。
             */
            std::vector<int> getValues() const { return values_; }

            /**
             * @brief ノードの特定のインデックスの値を取得する。
             * @param index 取得する値のインデックス。
             * @return 指定されたインデックスの値。
             */
            int getValue(int index) const { return values_[index]; }

            /**
             * @brief ノードの桁数を取得する。
             * @return ノードの桁数。
             */
            int getDigitCount() const { return digits_; }
        };

        Node value_[2];  ///< 2つのノード
        Node result_;    ///< 結果ノード
        int digits_ = 0; ///< Treeの桁数

    public:
        Tree() = default;
        Tree(const std::vector<int>& data1, const std::vector<int>& data2, int digits);

        /**
         * @brief 計算結果を格納する。
         * @param data 結果データ。
         * @param digits 桁数。
         */
        void setResult(int data, int digits);

        /**
         * @brief 計算結果をベクトルごと格納する。
         * @param values 結果ベクトル。
         */
        void setResult(const std::vector<int>& values);

        /**
         * @brief 計算結果を取得する。
         * @return 結果ベクトル。
         */
        std::vector<int> getResult() const;

        /**
         * @brief 特定のノードの値を取得する。
         * @param index ノードのインデックス。
         * @return 指定されたノードの値を格納したベクトル。
         */
        std::vector<int> getValues(int index) const { return value_[index].getValues(); }

        /**
         * @brief 特定のインデックスの値を取得する。
         * @param node_index ノードのインデックス。
         * @param value_index 値のインデックス。
         * @return 指定されたインデックスの値。
         */
        int getValue(int node_index, int value_index) const;

        /**
         * @brief Treeの桁数を取得する。
         * @return Treeの桁数。
         */
        int getDigitCount() const { return digits_; }
    };
}

#endif