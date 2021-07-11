#pragma once

#include <random>

class UniversalHash {
private:
    int64_t value_rate_;
    int64_t free_rate_;

public:
    static const int64_t kMaxValue = 1000000006;
    inline explicit UniversalHash(int64_t = 1, int64_t = 0);
    inline int64_t operator()(int64_t) const;
    template <class Generator>
    inline static UniversalHash GenerateHash(Generator);
};

UniversalHash::UniversalHash(int64_t value_rate, int64_t free_rate) : value_rate_(value_rate), free_rate_(free_rate) {
}

int64_t UniversalHash::operator()(int64_t value) const {
    return (value_rate_ * value + free_rate_) % (kMaxValue + 1);
}

template <class Generator>
UniversalHash UniversalHash::GenerateHash(Generator generator) {
    std::random_device rand_device;
    generator();
    Generator gen(rand_device());
    int64_t value_rate = gen() + 1;
    int64_t free_rate = gen();
    return UniversalHash(value_rate, free_rate);
}