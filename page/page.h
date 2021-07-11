#pragma once

#include <iostream>

template <class T, size_t N>
class Page {
private:
    T array_[N];
    size_t size_;
    bool is_front_;

public:
    Page();
    Page(const Page<T, N>&);
    Page<T, N>& operator=(const Page<T, N>&);
    T operator[](size_t) const;
    T& operator[](size_t);
    T Front() const;
    T& Front();
    T Back() const;
    T& Back();
    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    bool IsBack() const;
    bool IsFront() const;
    void PushBack(T);
    void PushFront(T);
    void PopBack();
    void PopFront();
    void Clear();
};

template <class T, size_t N>
Page<T, N>::Page() {
    size_ = 0;
}

template <class T, size_t N>
Page<T, N>::Page(const Page<T, N>& other) {
    is_front_ = other.is_front_;
    size_ = other.size_;
    for (size_t i = 0; i < size_; ++i) {
        array_[i] = other.array_[i];
    }
}

template <class T, size_t N>
Page<T, N>& Page<T, N>::operator=(const Page<T, N>& other) {
    if (this != &other) {
        is_front_ = other.is_front_;
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }
    }
    return *this;
}

template <class T, size_t N>
T Page<T, N>::operator[](size_t index) const {
    if (is_front_) {
        index = N - size_ + index;
    }
    return array_[index];
}

template <class T, size_t N>
T& Page<T, N>::operator[](size_t index) {
    if (is_front_) {
        index = N - size_ + index;
    }
    return array_[index];
}

template <class T, size_t N>
T Page<T, N>::Front() const {
    size_t index = 0;
    if (is_front_) {
        index = N - size_;
    }
    return array_[index];
}

template <class T, size_t N>
T& Page<T, N>::Front() {
    size_t index = 0;
    if (is_front_) {
        index = N - size_;
    }
    return array_[index];
}

template <class T, size_t N>
T Page<T, N>::Back() const {
    size_t index = size_ - 1;
    if (is_front_) {
        index = N - 1;
    }
    return array_[index];
}

template <class T, size_t N>
T& Page<T, N>::Back() {
    size_t index = size_ - 1;
    if (is_front_) {
        index = N - 1;
    }
    return array_[index];
}

template <class T, size_t N>
bool Page<T, N>::Empty() const {
    return size_ == 0;
}

template <class T, size_t N>
bool Page<T, N>::Full() const {
    return size_ == N;
}

template <class T, size_t N>
size_t Page<T, N>::Size() const {
    return size_;
}

template <class T, size_t N>
bool Page<T, N>::IsBack() const {
    if (size_ == 0) {
        return true;
    }
    if (size_ == N) {
        return false;
    }
    return !is_front_;
}

template <class T, size_t N>
bool Page<T, N>::IsFront() const {
    if (size_ == 0) {
        return true;
    }
    if (size_ == N) {
        return false;
    }
    return is_front_;
}

template <class T, size_t N>
void Page<T, N>::PushBack(T value) {
    if (size_ == 0) {
        is_front_ = false;
    }
    array_[size_] = value;
    size_++;
}

template <class T, size_t N>
void Page<T, N>::PushFront(T value) {
    if (size_ == 0) {
        is_front_ = true;
    }
    array_[N - size_ - 1] = value;
    size_++;
}

template <class T, size_t N>
void Page<T, N>::PopBack() {
    size_--;
}

template <class T, size_t N>
void Page<T, N>::PopFront() {
    size_--;
}

template <class T, size_t N>
void Page<T, N>::Clear() {
    size_ = 0;
}
