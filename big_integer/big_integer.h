#pragma once

#define BIG_INTEGER_DIVISION_IMPLEMENTED

#include <cstring>
#include <iostream>

class BigIntegerOverflow : public std::runtime_error {
public:
    BigIntegerOverflow() : std::runtime_error("BigIntegerOverflow") {
    }
};

class BigIntegerDivisionByZero : public std::runtime_error {
public:
    BigIntegerDivisionByZero() : std::runtime_error("BigIntegerDivisionByZero") {
    }
};

template <size_t N>
class BigInteger {
private:
    bool is_negative_;
    const static int kBase;
    const static int kMaxDigitSize;
    unsigned int digit_array_[(N - 1) / kMaxDigitSize + 1];

public:
    BigInteger();              //  NOLINT
    BigInteger(int);           //  NOLINT
    BigInteger(unsigned int);  //  NOLINT
    BigInteger(uint64_t);      //  NOLINT
    BigInteger(int64_t);       //  NOLINT
    BigInteger(const char*);   //  NOLINT
    BigInteger(const BigInteger<N>&);
    bool IsNegative() const {
        return is_negative_;
    }
    BigInteger<N> operator+() const {
        return *this;
    }
    BigInteger<N> operator-() const;
    bool CheckOverflow(unsigned int digit) const;
    bool operator==(const BigInteger<N>&) const;
    bool operator!=(const BigInteger<N>&) const;
    bool operator>(const BigInteger<N>&) const;
    bool operator<(const BigInteger<N>&) const;
    bool operator>=(const BigInteger<N>&) const;
    bool operator<=(const BigInteger<N>&) const;
    BigInteger<N> operator+(const BigInteger<N>&) const;
    BigInteger<N> operator-(const BigInteger<N>&) const;
    BigInteger<N> operator*(const BigInteger<N>&) const;
    BigInteger<N>& operator+=(const BigInteger<N>&);
    BigInteger<N>& operator-=(const BigInteger<N>&);
    BigInteger<N>& operator*=(const BigInteger<N>&);
    explicit operator bool() const;
    BigInteger<N> operator+(int64_t) const;
    BigInteger<N> operator-(int64_t) const;
    BigInteger<N> operator*(int64_t) const;
    BigInteger<N>& operator+=(int64_t);
    BigInteger<N>& operator-=(int64_t);
    BigInteger<N>& operator*=(int64_t);
    BigInteger<N> operator+(uint64_t) const;
    BigInteger<N> operator-(uint64_t) const;
    BigInteger<N> operator*(uint64_t) const;
    BigInteger<N>& operator+=(uint64_t);
    BigInteger<N>& operator-=(uint64_t);
    BigInteger<N>& operator*=(uint64_t);
    BigInteger<N> operator++(int);
    BigInteger<N> operator--(int);
    BigInteger<N>& operator++();
    BigInteger<N>& operator--();
    BigInteger<N> operator/(const BigInteger<N>&) const;
    BigInteger<N> operator%(const BigInteger<N>&) const;
    BigInteger<N>& operator/=(const BigInteger<N>&);
    BigInteger<N>& operator%=(const BigInteger<N>&);
    BigInteger<N> operator/(int64_t) const;
    BigInteger<N> operator/(uint64_t) const;
    BigInteger<N> operator%(int64_t) const;
    BigInteger<N> operator%(uint64_t) const;
    BigInteger<N>& operator/=(int64_t int_number);
    BigInteger<N>& operator/=(uint64_t int_number);
    BigInteger<N>& operator%=(int64_t int_number);
    BigInteger<N>& operator%=(uint64_t int_number);
    template <size_t M>
    friend std::istream& operator>>(std::istream&, BigInteger<M>&);
    template <size_t M>
    friend std::ostream& operator<<(std::ostream&, const BigInteger<M>&);
    BigInteger<N>& operator=(const BigInteger<N>&);
};

template <size_t N>
const int BigInteger<N>::kBase = 1000000000;
template <size_t N>
const int BigInteger<N>::kMaxDigitSize = 9;

template <size_t N>
BigInteger<N>::BigInteger() {
    for (size_t i = 0; i < (N - 1) / kMaxDigitSize + 1; ++i) {
        digit_array_[i] = 0;
    }
    is_negative_ = false;
}

template <size_t N>
BigInteger<N>::BigInteger(int int_number) {
    is_negative_ = int_number < 0;
    int_number = (int_number > 0) ? int_number : -int_number;
    size_t i = 0;
    while (i < (N - 1) / kMaxDigitSize) {
        digit_array_[i] = int_number % kBase;
        int_number /= kBase;
        i++;
    }
    if (CheckOverflow(int_number)) {
        throw BigIntegerOverflow{};
    }
    digit_array_[i] = int_number;
}

template <size_t N>
BigInteger<N>::BigInteger(unsigned int int_number) {
    is_negative_ = false;
    size_t i = 0;
    while (i < (N - 1) / kMaxDigitSize) {
        digit_array_[i] = int_number % kBase;
        int_number /= kBase;
        i++;
    }
    if (CheckOverflow(int_number)) {
        throw BigIntegerOverflow{};
    }
    digit_array_[i] = int_number;
}

template <size_t N>
BigInteger<N>::BigInteger(uint64_t int_number) {
    is_negative_ = false;
    size_t i = 0;
    while (i < (N - 1) / kMaxDigitSize) {
        digit_array_[i] = int_number % kBase;
        int_number /= kBase;
        i++;
    }
    if (CheckOverflow(int_number)) {
        throw BigIntegerOverflow{};
    }
    digit_array_[i] = int_number;
}

template <size_t N>
BigInteger<N>::BigInteger(int64_t int_number) {
    is_negative_ = int_number < 0;
    int_number = (int_number > 0) ? int_number : -int_number;
    size_t i = 0;
    while (i < (N - 1) / kMaxDigitSize) {
        digit_array_[i] = int_number % kBase;
        int_number /= kBase;
        i++;
    }
    if (CheckOverflow(int_number)) {
        throw BigIntegerOverflow{};
    }
    digit_array_[i] = int_number;
}

template <size_t N>
BigInteger<N>::BigInteger(const char* string_number) {
    size_t start = 0;
    is_negative_ = string_number[0] == '-';
    if ((string_number[0] == '-') || (string_number[0] == '+')) {
        start++;
    }
    size_t num_len = strlen(string_number);
    if (num_len - start > N) {
        throw BigIntegerOverflow{};
    }
    size_t digit_count = 0;
    size_t i = num_len - 1;
    while (i >= start) {
        unsigned int digit = 0;
        if (i < kMaxDigitSize) {
            for (size_t j = start; j <= i; ++j) {
                unsigned int temp_digit = string_number[j] - '0';
                for (size_t k = j; k < i; ++k) {
                    temp_digit *= 10;
                }
                digit += temp_digit;
            }
            digit_array_[digit_count] = digit;
            digit_count++;
            break;
        }
        for (size_t j = i - kMaxDigitSize + 1; j <= i; ++j) {
            unsigned int temp_digit = string_number[j] - '0';
            for (size_t k = j; k < i; ++k) {
                temp_digit *= 10;
            }
            digit += temp_digit;
        }
        digit_array_[digit_count] = digit;
        digit_count++;
        i -= kMaxDigitSize;
    }
    for (size_t i = digit_count; i < (N - 1) / kMaxDigitSize + 1; ++i) {
        digit_array_[i] = 0;
    }
}

template <size_t N>
BigInteger<N>::BigInteger(const BigInteger<N>& other) {
    is_negative_ = other.IsNegative();
    for (size_t i = 0; i < (N - 1) / kMaxDigitSize + 1; ++i) {
        digit_array_[i] = other.digit_array_[i];
    }
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator-() const {
    BigInteger<N> result_num = *this;
    bool is_zero = true;
    for (size_t i = 0; i < (N - 1) / kMaxDigitSize + 1; ++i) {
        if (result_num.digit_array_[i] != 0) {
            is_zero = false;
        }
    }
    if (!is_zero) {
        result_num.is_negative_ = !result_num.is_negative_;
    }
    return result_num;
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator+(const BigInteger<N>& right_number) const {
    if (this == &right_number) {
        BigInteger<N> num_copy = *this;
        return *this + num_copy;
    }
    size_t num_len = (N - 1) / kMaxDigitSize + 1;
    BigInteger<N> result_number;
    BigInteger<N> right_number_copy = right_number;
    size_t i = 0;
    if (is_negative_ == right_number_copy.IsNegative()) {
        while (i < num_len - 1) {
            unsigned int result_digit = digit_array_[i] + right_number_copy.digit_array_[i];
            result_number.digit_array_[i] += result_digit % kBase;
            right_number_copy.digit_array_[i + 1] += result_digit / kBase;
            i++;
        }
        int result_digit = digit_array_[i] + right_number_copy.digit_array_[i];
        result_number.digit_array_[i] += result_digit;
        if (is_negative_) {
            return -result_number;
        }
        return result_number;
    }
    BigInteger<N> left_number_copy = *this;
    if (is_negative_) {
        if (-(*this) >= right_number) {
            while (i < num_len) {
                if (left_number_copy.digit_array_[i] < right_number.digit_array_[i]) {
                    size_t j = i + 1;
                    while (left_number_copy.digit_array_[j] == 0) {
                        j++;
                    }
                    left_number_copy.digit_array_[j]--;
                    for (size_t k = i + 1; k < j; ++k) {
                        left_number_copy.digit_array_[k] += BigInteger<N>::kBase - 1;
                    }
                    left_number_copy.digit_array_[i] += BigInteger<N>::kBase;
                }
                int result_digit = left_number_copy.digit_array_[i] - right_number.digit_array_[i];
                result_number.digit_array_[i] += result_digit;
                i++;
            }
            return -result_number;
        }
        while (i < num_len) {
            if (right_number_copy.digit_array_[i] < left_number_copy.digit_array_[i]) {
                size_t j = i + 1;
                while (right_number_copy.digit_array_[j] == 0) {
                    j++;
                }
                right_number_copy.digit_array_[j]--;
                for (size_t k = i + 1; k < j; ++k) {
                    right_number_copy.digit_array_[k] += BigInteger<N>::kBase - 1;
                }
                right_number_copy.digit_array_[i] += BigInteger<N>::kBase;
            }
            int result_digit = right_number_copy.digit_array_[i] - left_number_copy.digit_array_[i];
            result_number.digit_array_[i] += result_digit;
            i++;
        }
        return result_number;
    }
    return right_number + *this;
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator*(const BigInteger<N>& right_number) const {
    if (this == &right_number) {
        BigInteger<N> num_copy = *this;
        return *this * num_copy;
    }
    size_t num_len = (N - 1) / kMaxDigitSize + 1;
    BigInteger<N> result_number;
    for (size_t i = 0; i < num_len; ++i) {
        BigInteger<N> left_num_copy = *this;
        BigInteger<N> temp_result;
        size_t j = 0;
        while (j < num_len - 1) {
            uint64_t result_digit = uint64_t(left_num_copy.digit_array_[j]) * uint64_t(right_number.digit_array_[i]);
            temp_result.digit_array_[j] += result_digit % kBase;
            temp_result.digit_array_[j + 1] += result_digit / kBase;
            j++;
        }
        uint64_t result_digit = uint64_t(left_num_copy.digit_array_[j]) * uint64_t(right_number.digit_array_[i]);
        if (CheckOverflow(result_digit + temp_result.digit_array_[j])) {
            throw BigIntegerOverflow{};
        }
        temp_result.digit_array_[j] += result_digit;
        j++;
        BigInteger<N> moved_temp_result;
        for (size_t k = 0; k < j - i; ++k) {
            moved_temp_result.digit_array_[k + i] = temp_result.digit_array_[k];
        }
        result_number += moved_temp_result;
    }
    if (is_negative_ == right_number.IsNegative()) {
        return result_number;
    }
    return -result_number;
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator-(const BigInteger<N>& right_number) const {
    return *this + (-right_number);
}

template <size_t N>
bool BigInteger<N>::CheckOverflow(unsigned int digit) const {
    size_t max_size = N - ((N - 1) / kMaxDigitSize) * kMaxDigitSize;
    while (max_size > 0) {
        digit /= 10;
        max_size--;
    }
    return digit > 0;
}

template <size_t N>
bool BigInteger<N>::operator==(const BigInteger<N>& right_number) const {
    if (is_negative_ != right_number.IsNegative()) {
        return false;
    }
    size_t num_len = (N - 1) / kMaxDigitSize + 1;
    for (size_t i = 0; i < num_len; ++i) {
        if (digit_array_[i] != right_number.digit_array_[i]) {
            return false;
        }
    }
    return true;
}

template <size_t N>
bool BigInteger<N>::operator!=(const BigInteger<N>& right_number) const {
    return !(*this == right_number);
}

template <size_t N>
bool BigInteger<N>::operator>(const BigInteger<N>& right_number) const {
    if (is_negative_ != right_number.IsNegative()) {
        return is_negative_ < right_number.IsNegative();
    }
    size_t num_len = (N - 1) / BigInteger<N>::kMaxDigitSize;
    while (num_len >= 0) {
        if (digit_array_[num_len] > right_number.digit_array_[num_len]) {
            return true;
        }
        if (digit_array_[num_len] < right_number.digit_array_[num_len]) {
            return false;
        }
        if (num_len == 0) {
            break;
        }
        num_len--;
    }
    return false;
}

template <size_t N>
bool BigInteger<N>::operator<=(const BigInteger<N>& right_number) const {
    return !(*this > right_number);
}

template <size_t N>
bool BigInteger<N>::operator<(const BigInteger<N>& right_number) const {
    if (*this == right_number) {
        return false;
    }
    return !(*this > right_number);
}

template <size_t N>
bool BigInteger<N>::operator>=(const BigInteger<N>& right_number) const {
    return !(*this < right_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator+=(const BigInteger<N>& right_number) {
    BigInteger<N> result_number = *this + right_number;
    *this = result_number;
    return *this;
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator-=(const BigInteger<N>& right_number) {
    BigInteger<N> result_number = *this - right_number;
    *this = result_number;
    return *this;
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator*=(const BigInteger<N>& right_number) {
    BigInteger<N> result_number = *this * right_number;
    *this = result_number;
    return *this;
}

template <size_t N>
BigInteger<N>::operator bool() const {
    size_t num_len = (N - 1) / kMaxDigitSize + 1;
    for (size_t i = 0; i < num_len; ++i) {
        if (digit_array_[i] != 0) {
            return true;
        }
    }
    return false;
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator+(int64_t int_number) const {
    return *this + BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator-(int64_t int_number) const {
    return *this - BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator*(int64_t int_number) const {
    return *this * BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator+=(int64_t int_number) {
    return *this += BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator-=(int64_t int_number) {
    return *this -= BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator*=(int64_t int_number) {
    return *this *= BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator+(uint64_t int_number) const {
    return *this + BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator-(uint64_t int_number) const {
    return *this - BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator*(uint64_t int_number) const {
    return *this * BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator+=(uint64_t int_number) {
    return *this += BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator-=(uint64_t int_number) {
    return *this -= BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator*=(uint64_t int_number) {
    return *this *= BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator++(int) {
    BigInteger<N> left_number = *this;
    *this += BigInteger<N>(1);
    return left_number;
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator--(int) {
    BigInteger<N> right_number = BigInteger<N>(1);
    BigInteger<N> left_number = *this;
    *this -= right_number;
    return left_number;
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator++() {
    BigInteger<N> right_number = BigInteger<N>(1);
    return *this += right_number;
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator--() {
    BigInteger<N> right_number = BigInteger<N>(1);
    return *this -= right_number;
}

template <size_t N>
std::istream& operator>>(std::istream& in, BigInteger<N>& number) {
    char string_num[N + 2];
    in >> string_num;
    number = BigInteger<N>(string_num);
    return in;
}

template <size_t N>
std::ostream& operator<<(std::ostream& out, const BigInteger<N>& number) {
    if (number.IsNegative()) {
        out << '-';
    }
    char string_num[N + 1];
    string_num[N] = 0;
    size_t ind = N - 1;
    for (size_t i = 0; i < (N - 1) / BigInteger<N>::kMaxDigitSize + 1; ++i) {
        unsigned int digit = number.digit_array_[i];
        if (ind < BigInteger<N>::kMaxDigitSize) {
            while (ind >= 0) {
                string_num[ind] = '0' + digit % 10;
                digit /= 10;
                if (ind == 0) {
                    break;
                }
                ind--;
            }
        } else {
            for (size_t j = ind; j >= ind - BigInteger<N>::kMaxDigitSize + 1; --j) {
                string_num[j] = '0' + digit % 10;
                digit /= 10;
            }
            ind -= BigInteger<N>::kMaxDigitSize;
        }
    }
    bool has_first_digit = false;
    for (size_t i = 0; i < N; ++i) {
        if (string_num[i] != '0') {
            has_first_digit = true;
        }
        if (has_first_digit) {
            out << string_num[i];
        }
    }
    if (!has_first_digit) {
        out << 0;
    }
    return out;
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator=(const BigInteger<N>& right_number) {
    is_negative_ = right_number.IsNegative();
    for (size_t i = 0; i < (N - 1) / kMaxDigitSize + 1; ++i) {
        digit_array_[i] = right_number.digit_array_[i];
    }
    return *this;
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator/(const BigInteger<N>& right_number) const {
    size_t right_num_len = 0;
    size_t left_num_len = 0;
    for (size_t i = 0; i < (N - 1) / kMaxDigitSize + 1; ++i) {
        if (right_number.digit_array_[i] != 0) {
            right_num_len = i;
        }
        if (digit_array_[i] != 0) {
            left_num_len = i;
        }
    }
    if (right_number.digit_array_[right_num_len] == 0) {
        throw BigIntegerDivisionByZero{};
    }
    size_t i = left_num_len;
    unsigned int result[(N - 1) / kMaxDigitSize + 1];
    for (size_t j = 0; j < (N - 1) / kMaxDigitSize + 1; ++j) {
        result[j] = 0;
    }
    size_t k = 0;
    BigInteger<N> left_num_copy = *this;
    while (i >= 0) {
        BigInteger<N> temp_num;
        if (i <= right_num_len) {
            while (i >= 0) {
                temp_num.digit_array_[i] = left_num_copy.digit_array_[i];
                if (i == 0) {
                    break;
                }
                i--;
            }
        } else {
            for (size_t j = 0; j <= right_num_len; ++j) {
                temp_num.digit_array_[right_num_len - j] = left_num_copy.digit_array_[i - j];
            }
            if (temp_num < *this) {
                for (size_t j = right_num_len; j >= 0; --j) {
                    temp_num.digit_array_[j + 1] = temp_num.digit_array_[j];
                    if (j == 0) {
                        break;
                    }
                }
                temp_num.digit_array_[0] = left_num_copy.digit_array_[i - right_num_len - 1];
                i -= right_num_len + 1;
            } else {
                i -= right_num_len;
            }
        }
        uint64_t count = 0;
        BigInteger<N> right_abs = right_number;
        right_abs.is_negative_ = false;
        while (temp_num > 0) {
            temp_num -= right_abs;
            count++;
        }
        if (temp_num < 0) {
            count--;
            temp_num += right_abs;
            for (size_t j = right_num_len; j >= 0; --j) {
                left_num_copy.digit_array_[i + j] = temp_num.digit_array_[j];
                if (j == 0) {
                    break;
                }
            }
        }
        result[k] = count;
        k++;
        if (i == 0) {
            break;
        }
        i--;
    }
    k--;
    BigInteger<N> result_number;
    for (size_t j = 0; j <= k; ++j) {
        result_number.digit_array_[j] = result[k - j];
    }
    bool is_zero = true;
    for (size_t i = 0; i < (N - 1) / kMaxDigitSize + 1; ++i) {
        if (result_number.digit_array_[i] != 0) {
            is_zero = false;
        }
    }
    if (!is_zero) {
        result_number.is_negative_ = (is_negative_ != right_number.is_negative_);
    }
    return result_number;
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator%(const BigInteger<N>& right_number) const {
    return *this - (*this / right_number) * right_number;
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator/=(const BigInteger<N>& right_number) {
    *this = *this / right_number;
    return *this;
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator%=(const BigInteger<N>& right_number) {
    *this = *this % right_number;
    return *this;
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator/(int64_t int_number) const {
    return *this / BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator/(uint64_t int_number) const {
    return *this / BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator%(int64_t int_number) const {
    return *this % BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N> BigInteger<N>::operator%(uint64_t int_number) const {
    return *this % BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator/=(int64_t int_number) {
    return *this /= BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator/=(uint64_t int_number) {
    return *this /= BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator%=(int64_t int_number) {
    return *this %= BigInteger<N>(int_number);
}

template <size_t N>
BigInteger<N>& BigInteger<N>::operator%=(uint64_t int_number) {
    return *this %= BigInteger<N>(int_number);
}