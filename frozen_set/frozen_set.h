#pragma once

#include <iterator>
#include <optional>
#include "universal_hash.h"
#include <vector>

template <class T, class Hash>
class FrozenSet {
private:
    Hash hash_;
    std::vector<std::pair<std::vector<std::optional<T>>, Hash>> set_;
    size_t size_;

public:
    FrozenSet();
    template <class Iterator, class Generator>
    FrozenSet(Iterator, Iterator, Generator);
    template <class Iterator, class Generator>
    void Assign(Iterator, Iterator, Generator);
    size_t Size() const;
    bool Empty() const;
    void Clear();
    bool Find(T) const;
};

template <class T, class Hash>
FrozenSet<T, Hash>::FrozenSet() {
    size_ = 0;
}

template <class T, class Hash>
template <class Iterator, class Generator>
FrozenSet<T, Hash>::FrozenSet(Iterator begin, Iterator end, Generator generator) {
    size_ = std::distance(begin, end);
    set_.resize(size_);
    bool has_no_collisions = true;
    do {
        hash_ = Hash::GenerateHash(generator);
        Iterator begin_copy = begin;
        has_no_collisions = true;
        auto counts = std::vector<int>(size_, 0);
        while (begin_copy != end) {
            counts[hash_(*begin_copy) % size_]++;
            begin_copy++;
        }
        size_t cur_size = 0;
        for (size_t i = 0; i < size_; ++i) {
            set_[i] =
                std::make_pair(std::vector<std::optional<T>>(counts[i] * counts[i]), Hash::GenerateHash(generator));
            cur_size += counts[i] * counts[i];
            if (cur_size > 4 * size_) {
                has_no_collisions = false;
                break;
            }
        }
    } while (!has_no_collisions);
    while (begin != end) {
        auto& inner_table = set_[hash_(*begin) % size_];
        if (inner_table.first[inner_table.second(*begin) % inner_table.first.size()].has_value()) {
            do {
                has_no_collisions = true;
                Hash new_func = Hash::GenerateHash(generator);
                std::vector<std::optional<T>> new_inner;
                for (size_t i = 0; i < inner_table.first.size(); ++i) {
                    if (new_inner[new_func(inner_table.first[i].value()) % inner_table.first.size()].has_value()) {
                        has_no_collisions = false;
                        break;
                    }
                    new_inner[new_func(inner_table.first[i].value()) % inner_table.first.size()] = inner_table.first[i];
                }
                set_[hash_(*begin) % size_] = std::make_pair(new_inner, new_func);
            } while (!has_no_collisions);
        }
        begin++;
    }
}

template <class T, class Hash>
template <class Iterator, class Generator>
void FrozenSet<T, Hash>::Assign(Iterator begin, Iterator end, Generator generator) {
    size_ = std::distance(begin, end);
    set_.resize(size_);
    bool has_no_collisions = true;
    do {
        hash_ = Hash::GenerateHash(generator);
        Iterator begin_copy = begin;
        has_no_collisions = true;
        auto counts = std::vector<int>(size_, 0);
        while (begin_copy != end) {
            counts[hash_(*begin_copy) % size_]++;
            begin_copy++;
        }
        size_t cur_size = 0;
        for (size_t i = 0; i < size_; ++i) {
            set_[i] =
                std::make_pair(std::vector<std::optional<T>>(counts[i] * counts[i]), Hash::GenerateHash(generator));
            cur_size += counts[i] * counts[i];
            if (cur_size > 4 * size_) {
                has_no_collisions = false;
                break;
            }
        }
    } while (!has_no_collisions);
    while (begin != end) {
        auto& inner_table = set_[hash_(*begin) % size_];
        if (inner_table.first[inner_table.second(*begin) % inner_table.first.size()].has_value()) {
            do {
                has_no_collisions = true;
                Hash new_func = Hash::GenerateHash(generator);
                std::vector<std::optional<T>> new_inner;
                for (size_t i = 0; i < inner_table.first.size(); ++i) {
                    if (new_inner[new_func(inner_table.first[i].value()) % inner_table.first.size()].has_value()) {
                        has_no_collisions = false;
                        break;
                    }
                    new_inner[new_func(inner_table.first[i].value()) % inner_table.first.size()] = inner_table.first[i];
                }
                set_[hash_(*begin) % size_] = std::make_pair(new_inner, new_func);
            } while (!has_no_collisions);
        }
        begin++;
    }
}

template <class T, class Hash>
size_t FrozenSet<T, Hash>::Size() const {
    return size_;
}

template <class T, class Hash>
bool FrozenSet<T, Hash>::Empty() const {
    return size_ == 0;
}

template <class T, class Hash>
void FrozenSet<T, Hash>::Clear() {
    set_.clear();
}

template <class T, class Hash>
bool FrozenSet<T, Hash>::Find(T key) const {
    if (Empty()) {
        return false;
    }
    auto& inner_table = set_[hash_(key) % size_];
    if (inner_table.first.empty()) {
        return false;
    }
    return inner_table.first[inner_table.second(key) % inner_table.first.size()].has_value();
}