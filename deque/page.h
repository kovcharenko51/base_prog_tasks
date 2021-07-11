#pragma once

#include <iostream>

template <class T, size_t N>
class Page {
private:
    T array_[N];
    size_t size_;
    size_t start_;
    size_t end_;

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
    start_ = 0;
    end_ = 0;
}

template <class T, size_t N>
Page<T, N>::Page(const Page<T, N>& other) {
    size_ = other.size_;
    for (size_t i = 0; i < size_; ++i) {
        array_[i] = other.array_[i];
    }
    start_ = other.start_;
    end_ = other.end_;
}

template <class T, size_t N>
Page<T, N>& Page<T, N>::operator=(const Page<T, N>& other) {
    if (this != &other) {
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }
        start_ = other.start_;
        end_ = other.end_;
    }
    return *this;
}

template <class T, size_t N>
T Page<T, N>::operator[](size_t index) const {
    return array_[(start_ + index) % N];
}

template <class T, size_t N>
T& Page<T, N>::operator[](size_t index) {
    return array_[(start_ + index) % N];
}

template <class T, size_t N>
T Page<T, N>::Front() const {
    return array_[start_];
}

template <class T, size_t N>
T& Page<T, N>::Front() {
    return array_[start_];
}

template <class T, size_t N>
T Page<T, N>::Back() const {
    return array_[end_];
}

template <class T, size_t N>
T& Page<T, N>::Back() {
    return array_[end_];
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
void Page<T, N>::PushBack(T value) {
    if (size_ == 0) {
        end_ = start_;
    } else if (end_ == N - 1) {
        end_ = 0;
    } else {
        end_++;
    }
    array_[end_] = value;
    size_++;
}

template <class T, size_t N>
void Page<T, N>::PushFront(T value) {
    if (size_ == 0) {
        start_ = end_ = 0;
    } else if (start_ == 0) {
        start_ = N - 1;
    } else {
        start_--;
    }
    array_[start_] = value;
    size_++;
}

template <class T, size_t N>
void Page<T, N>::PopBack() {
    if (end_ == 0) {
        end_ = N - 1;
    } else {
        end_--;
    }
    size_--;
}

template <class T, size_t N>
void Page<T, N>::PopFront() {
    if (start_ == N - 1) {
        start_ = 0;
    } else {
        start_++;
    }
    size_--;
}

template <class T, size_t N>
void Page<T, N>::Clear() {
    size_ = 0;
}