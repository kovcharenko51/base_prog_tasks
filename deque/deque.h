#pragma once

#include <iostream>
#include "circular_buffer.h"
#include "page.h"

template <class T>
class Deque {
private:
    const static int kPageSize = 100;
    CircularBuffer<Page<T, kPageSize>*> buffer_;
    size_t size_;

public:
    Deque();
    Deque(const Deque<T>&);
    Deque<T>& operator=(const Deque<T>&);
    ~Deque();
    void Swap(Deque<T>&);
    T& operator[](size_t);
    T operator[](size_t) const;
    size_t Size() const;
    void PushBack(T);
    void PopBack();
    void PushFront(T);
    void PopFront();
    void Clear();
};

template <class T>
Deque<T>::Deque() {
    buffer_ = CircularBuffer<Page<T, kPageSize>*>();
    size_ = 0;
}

template <class T>
Deque<T>::Deque(const Deque<T>& other) {
    for (size_t i = 0; i < other.buffer_.Size(); ++i) {
        auto page = new Page<T, kPageSize>;
        *page = *(other.buffer_[i]);
        buffer_.PushBack(page);
    }
    size_ = other.size_;
}

template <class T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other) {
    if (this != &other) {
        size_t buff_size = buffer_.Size();
        for (size_t i = 0; i < buff_size; ++i) {
            delete buffer_.Back();
            buffer_.PopBack();
        }
        for (size_t i = 0; i < other.buffer_.Size(); ++i) {
            auto page = new Page<T, kPageSize>;
            *page = *(other.buffer_[i]);
            buffer_.PushBack(page);
        }
        size_ = other.size_;
    }
    return *this;
}

template <class T>
Deque<T>::~Deque() {
    size_t buff_size = buffer_.Size();
    for (size_t i = 0; i < buff_size; ++i) {
        delete buffer_.Back();
        buffer_.PopBack();
    }
}

template <class T>
void Deque<T>::Swap(Deque<T>& other) {
    buffer_.Swap(other.buffer_);
    size_t temp_size = size_;
    size_ = other.size_;
    other.size_ = temp_size;
}

template <class T>
T& Deque<T>::operator[](size_t index) {
    if ((buffer_.Front()->Full()) || (index < buffer_.Front()->Size())) {
        return (*(buffer_[index / kPageSize]))[index % kPageSize];
    }
    index -= buffer_.Front()->Size();
    return (*(buffer_[1 + index / kPageSize]))[index % kPageSize];
}

template <class T>
T Deque<T>::operator[](size_t index) const {
    if ((buffer_.Front()->Full()) || (index < buffer_.Front()->Size())) {
        return (*(buffer_[index / kPageSize]))[index % kPageSize];
    }
    index -= buffer_.Front()->Size();
    return (*(buffer_[1 + index / kPageSize]))[index % kPageSize];
}

template <class T>
size_t Deque<T>::Size() const {
    return size_;
}

template <class T>
void Deque<T>::PushBack(T value) {
    if ((buffer_.Size() == 0) || (buffer_.Back()->Full())) {
        auto page = new Page<T, kPageSize>;
        buffer_.PushBack(page);
    }
    buffer_.Back()->PushBack(value);
    size_++;
}

template <class T>
void Deque<T>::PopBack() {
    buffer_.Back()->PopBack();
    if (buffer_.Back()->Empty()) {
        delete buffer_.Back();
        buffer_.PopBack();
    }
    size_--;
}

template <class T>
void Deque<T>::PushFront(T value) {
    if ((buffer_.Size() == 0) || (buffer_.Front()->Full())) {
        auto page = new Page<T, kPageSize>;
        buffer_.PushFront(page);
    }
    buffer_.Front()->PushFront(value);
    size_++;
}

template <class T>
void Deque<T>::PopFront() {
    buffer_.Front()->PopFront();
    if (buffer_.Front()->Empty()) {
        delete buffer_.Front();
        buffer_.PopFront();
    }
    size_--;
}

template <class T>
void Deque<T>::Clear() {
    size_t buff_size = buffer_.Size();
    for (size_t i = 0; i < buff_size; ++i) {
        delete buffer_.Back();
        buffer_.PopBack();
    }
    size_ = 0;
}