#pragma once

#include <cstdlib>
#include <iostream>
#include <numeric>

class RationalDivisionByZero : public std::runtime_error {
public:
    RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
    }
};

class Rational {
private:
    int64_t numerator_;
    int64_t denominator_;
    void Reduce();

public:
    Rational();
    Rational(int64_t numerator);  //  NOLINT
    Rational(int64_t numerator, int64_t denominator);
    int64_t GetNumerator() const;
    int64_t GetDenominator() const;
    void SetNumerator(int64_t numerator);
    void SetDenominator(int64_t denominator);
    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);
    Rational operator+() const;
    Rational operator-() const;
    Rational operator+(const Rational&) const;
    Rational operator-(const Rational&) const;
    Rational operator*(const Rational&) const;
    Rational operator/(const Rational&) const;
    Rational& operator+=(const Rational&);
    Rational& operator-=(const Rational&);
    Rational& operator*=(const Rational&);
    Rational& operator/=(const Rational&);
    bool operator>(const Rational&) const;
    bool operator<(const Rational&) const;
    bool operator>=(const Rational&) const;
    bool operator<=(const Rational&) const;
    bool operator==(const Rational&) const;
    bool operator!=(const Rational&) const;
    friend std::istream& operator>>(std::istream&, Rational&);
    friend std::ostream& operator<<(std::ostream&, const Rational&);
    friend bool operator>(const int64_t, const Rational&);
    friend bool operator<(const int64_t, const Rational&);
    friend bool operator>=(const int64_t, const Rational&);
    friend bool operator<=(const int64_t, const Rational&);
    friend bool operator==(const int64_t, const Rational&);
    friend bool operator!=(const int64_t, const Rational&);
};
