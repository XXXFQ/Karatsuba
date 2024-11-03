#ifndef  KARATSUBA_SIGNED_VECTOR_HPP
#define  KARATSUBA_SIGNED_VECTOR_HPP

#include <vector>

class SignedVector {
public:
    // 既定のコンストラクタ
    SignedVector() : values_(), is_negative_(false) {}

    // 引数付きコンストラクタ
    SignedVector(const std::vector<int>& values, bool is_negative = false)
        : values_(values), is_negative_(is_negative) {}

    // 符号の反転
    void negate() {
        is_negative_ = !is_negative_;
    }

    // ゼロかどうかをチェック
    bool isZero() const {
        return values_.size() == 1 && values_[0] == 0;
    }

    // 値の取得
    const std::vector<int>& getValues() const {
        return values_;
    }

    // 符号の取得
    bool isNegative() const {
        return is_negative_;
    }

    // 符号を設定
    void setNegative(bool is_negative) {
        is_negative_ = is_negative;
    }

private:
    std::vector<int> values_;
    bool is_negative_;
};

#endif