#include "rational.h"

void Rational::Reduce() {
    if (denominator_ == 0) {
        throw RationalDivisionByZero{};
    }
    int64_t frac_gcd = std::gcd(numerator_, denominator_);
    if (denominator_ < 0) {
        numerator_ *= -1;
        denominator_ *= -1;
    }
    numerator_ /= frac_gcd;
    denominator_ /= frac_gcd;
}

Rational::Rational() : numerator_(0), denominator_(1) {
}

Rational::Rational(int64_t numerator) : numerator_(numerator), denominator_(1) {  // NOLINT
}

Rational::Rational(int64_t numerator, int64_t denominator) : numerator_(numerator), denominator_(denominator) {
    Reduce();
}

int64_t Rational::GetNumerator() const {
    return numerator_;
}
int64_t Rational::GetDenominator() const {
    return denominator_;
}
void Rational::SetNumerator(int64_t numerator) {
    numerator_ = numerator;
    Reduce();
}
void Rational::SetDenominator(int64_t denominator) {
    denominator_ = denominator;
    Reduce();
}

Rational& Rational::operator++() {
    *this = *this + Rational(1);
    this->Reduce();
    return *this;
}

Rational Rational::operator++(int) {
    Rational result = *this;
    *this = *this + Rational(1);
    this->Reduce();
    return result;
}

Rational& Rational::operator--() {
    *this = *this - Rational(1);
    this->Reduce();
    return *this;
}

Rational Rational::operator--(int) {
    Rational result = *this;
    *this = *this - Rational(1);
    this->Reduce();
    return result;
}

Rational Rational::operator+() const {
    return *this;
}

Rational Rational::operator-() const {
    Rational result = *this;
    result.numerator_ *= -1;
    return result;
}

Rational Rational::operator+(const Rational& right_num) const {
    Rational result;
    result.SetNumerator(numerator_ * right_num.denominator_ + denominator_ * right_num.numerator_);
    result.SetDenominator(denominator_ * right_num.denominator_);
    result.Reduce();
    return result;
}

Rational Rational::operator-(const Rational& right_num) const {
    Rational result = *this + (-right_num);
    result.Reduce();
    return result;
}

Rational Rational::operator*(const Rational& right_num) const {
    Rational result;
    result.SetNumerator(numerator_ * right_num.numerator_);
    result.SetDenominator(denominator_ * right_num.denominator_);
    result.Reduce();
    return result;
}

Rational Rational::operator/(const Rational& right_num) const {
    Rational result;
    result.SetNumerator(numerator_ * right_num.denominator_);
    result.SetDenominator(denominator_ * right_num.numerator_);
    result.Reduce();
    return result;
}

Rational& Rational::operator+=(const Rational& right_num) {
    *this = *this + right_num;
    return *this;
}

Rational& Rational::operator-=(const Rational& right_num) {
    *this = *this - right_num;
    return *this;
}

Rational& Rational::operator*=(const Rational& right_num) {
    *this = *this * right_num;
    return *this;
}

Rational& Rational::operator/=(const Rational& right_num) {
    *this = *this / right_num;
    return *this;
}

bool Rational::operator>(const Rational& right_num) const {
    return (numerator_ * right_num.denominator_ > denominator_ * right_num.numerator_);
}

bool Rational::operator<(const Rational& right_num) const {
    return (numerator_ * right_num.denominator_ < denominator_ * right_num.numerator_);
}

bool Rational::operator>=(const Rational& right_num) const {
    return !(*this < right_num);
}

bool Rational::operator<=(const Rational& right_num) const {
    return !(*this > right_num);
}

bool Rational::operator==(const Rational& right_num) const {
    return (numerator_ * right_num.denominator_ == denominator_ * right_num.numerator_);
}

bool Rational::operator!=(const Rational& right_num) const {
    return !(*this == right_num);
}

std::istream& operator>>(std::istream& in, Rational& rt) {
    const int maxStringSize = 32;
    char str[maxStringSize];
    in >> str;
    char* endPtr;
    rt.SetDenominator(1);
    rt.SetNumerator(strtol(str, &endPtr, 10));
    if (*endPtr != 0) {
        ++endPtr;
        rt.SetDenominator(strtol(endPtr, &endPtr, 10));
    } else {
        rt.SetDenominator(1);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& rt) {
    out << rt.numerator_;
    if (rt.denominator_ != 1) {
        out << '/' << rt.denominator_;
    }
    return out;
}

bool operator>(const int64_t left_num, const Rational& right_num) {
    return Rational(left_num) > right_num;
}

bool operator<(const int64_t left_num, const Rational& right_num) {
    return Rational(left_num) < right_num;
}

bool operator>=(const int64_t left_num, const Rational& right_num) {
    return Rational(left_num) >= right_num;
}

bool operator<=(const int64_t left_num, const Rational& right_num) {
    return Rational(left_num) <= right_num;
}

bool operator==(const int64_t left_num, const Rational& right_num) {
    return Rational(left_num) == right_num;
}

bool operator!=(const int64_t left_num, const Rational& right_num) {
    return Rational(left_num) != right_num;
}