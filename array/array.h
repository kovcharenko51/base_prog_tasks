#pragma once

#define ARRAY_ARRAY_TRAITS_IMPLEMENTED

#include <iostream>

class ArrayOutOfRange : public std::out_of_range {
public:
    ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
    }
};

template <class T, size_t N>
class Array {
public:
    T data[N];
    const T& operator[](size_t) const;
    T& operator[](size_t);
    const T& At(size_t) const;
    T& At(size_t);
    const T& Front() const;
    T& Front();
    const T& Back() const;
    T& Back();
    const T* Data() const;
    T* Data();
    size_t Size() const;
    bool Empty() const;
    void Fill(const T&);
    void Swap(Array<T, N>&);
    void swap(T&, T&);  // NOLINT
    bool operator>(const Array<T, N>&) const;
    bool operator<(const Array<T, N>&) const;
    bool operator>=(const Array<T, N>&) const;
    bool operator<=(const Array<T, N>&) const;
    bool operator==(const Array<T, N>&) const;
    bool operator!=(const Array<T, N>&) const;
};

template <class T, size_t N>
const T& Array<T, N>::operator[](size_t ind) const {
    return data[ind];
}

template <class T, size_t N>
T& Array<T, N>::operator[](size_t ind) {
    return data[ind];
}

template <class T, size_t N>
const T& Array<T, N>::At(size_t index) const {
    if (index >= N) {
        throw ArrayOutOfRange{};
    }
    return data[index];
}

template <class T, size_t N>
T& Array<T, N>::At(size_t index) {
    if (index >= N) {
        throw ArrayOutOfRange{};
    }
    return data[index];
}

template <class T, size_t N>
const T& Array<T, N>::Front() const {
    return data[0];
}

template <class T, size_t N>
T& Array<T, N>::Front() {
    return data[0];
}

template <class T, size_t N>
const T& Array<T, N>::Back() const {
    return data[N - 1];
}

template <class T, size_t N>
T& Array<T, N>::Back() {
    return data[N - 1];
}

template <class T, size_t N>
const T* Array<T, N>::Data() const {
    return data;
}

template <class T, size_t N>
T* Array<T, N>::Data() {
    return data;
}

template <class T, size_t N>
size_t Array<T, N>::Size() const {
    return N;
}

template <class T, size_t N>
bool Array<T, N>::Empty() const {
    return N == 0;
}

template <class T, size_t N>
void Array<T, N>::Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
        data[i] = value;
    }
}

template <class T, size_t N>
void Array<T, N>::Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
        T temp = data[i];
        data[i] = other[i];
        other[i] = temp;
    }
}

template <class T, size_t N>
void Array<T, N>::swap(T& first_el, T& second_el) {  // NOLINT
    T temp = first_el;
    first_el = second_el;
    second_el = temp;
}

template <class T, size_t N>
bool Array<T, N>::operator>(const Array<T, N>& other) const {
    for (size_t i = 0; i < N; ++i) {
        if (data[i] > other.data[i]) {
            return true;
        }
        if (data[i] < other.data[i]) {
            return false;
        }
    }
    return false;
}

template <class T, size_t N>
bool Array<T, N>::operator<(const Array<T, N>& other) const {
    if (*this == other) {
        return false;
    }
    return !(*this > other);
}

template <class T, size_t N>
bool Array<T, N>::operator>=(const Array<T, N>& other) const {
    return !(*this < other);
}

template <class T, size_t N>
bool Array<T, N>::operator<=(const Array<T, N>& other) const {
    return !(*this > other);
}

template <class T, size_t N>
bool Array<T, N>::operator==(const Array<T, N>& other) const {
    for (size_t i = 0; i < N; ++i) {
        if (data[i] != other.data[i]) {
            return false;
        }
    }
    return true;
}

template <class T, size_t N>
bool Array<T, N>::operator!=(const Array<T, N>& other) const {
    return !(*this == other);
}

template <class T>
size_t GetSize(const T&) {
    return 0;
}

template <class T, size_t N>
size_t GetSize(const T (&)[N]) {
    return N;
}

template <class T>
size_t GetRank(const T&) {
    return 0;
}

template <class T, size_t N>
size_t GetRank(const T (&arr)[N]) {
    return 1 + GetRank(arr[0]);
}

template <class T>
size_t GetNumElements(const T&) {
    return 1;
}

template <class T, size_t N>
size_t GetNumElements(const T (&arr)[N]) {
    return N * GetNumElements(arr[0]);
}