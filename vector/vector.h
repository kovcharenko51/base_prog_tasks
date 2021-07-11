#pragma once

#include <iostream>
#include <vector>

class VectorOutOfRange : public std::out_of_range {
public:
    VectorOutOfRange() : std::out_of_range("VectorOutOfRange") {
    }
};

template <class T>
class Vector {
private:
    T *array_;
    size_t size_;
    size_t capacity_;

public:
    Vector();
    explicit Vector<T>(size_t size);
    Vector<T>(size_t, T);
    Vector(const Vector<T> &);
    Vector<T> &operator=(const Vector<T> &);
    ~Vector();
    void Clear();
    void PushBack(T);
    void PopBack();
    void Resize(size_t);
    void Resize(size_t, T);
    void Reserve(size_t);
    void ShrinkToFit();
    void Swap(Vector<T> &);
    T operator[](size_t) const;
    T &operator[](size_t);
    T At(size_t) const;
    T &At(size_t);
    T Front() const;
    T &Front();
    T Back() const;
    T &Back();
    bool Empty() const;
    size_t Size() const;
    size_t Capacity() const;
    T *Data() const;
    bool operator<(const Vector<T> &) const;
    bool operator>(const Vector<T> &) const;
    bool operator<=(const Vector<T> &) const;
    bool operator>=(const Vector<T> &) const;
    bool operator==(const Vector<T> &) const;
    bool operator!=(const Vector<T> &) const;
};

template <class T>
Vector<T>::Vector() {
    array_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template <class T>
Vector<T>::Vector(size_t size) {
    array_ = nullptr;
    if (size > 0) {
        array_ = new T[size];
    }
    size_ = size;
    capacity_ = size;
}

template <class T>
Vector<T>::Vector(size_t size, T value) {
    array_ = nullptr;
    if (size > 0) {
        array_ = new T[size];
    }
    size_ = size;
    capacity_ = size;
    for (size_t i = 0; i < size; ++i) {
        array_[i] = value;
    }
}

template <class T>
Vector<T>::Vector(const Vector<T> &other) {
    array_ = nullptr;
    if (other.capacity_ != 0) {
        array_ = new T[other.capacity_];
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
    for (size_t i = 0; i < size_; ++i) {
        array_[i] = other.array_[i];
    }
}

template <class T>
Vector<T>::~Vector() {
    delete[] array_;
}

template <class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
    if (this != &other) {
        T *old_array = array_;
        array_ = nullptr;
        if (other.capacity_ > 0) {
            array_ = new T[other.capacity_];
        }
        delete[] old_array;
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (size_t i = 0; i < size_; ++i) {
            array_[i] = other.array_[i];
        }
    }
    return *this;
}

template <class T>
void Vector<T>::Clear() {
    size_ = 0;
}

template <class T>
void Vector<T>::PushBack(T value) {
    T *old_array = array_;
    if (capacity_ == 0) {
        array_ = new T[1];
        capacity_ = 1;
        delete[] old_array;
    } else if (size_ == capacity_) {
        capacity_ *= 2;
        array_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            array_[i] = old_array[i];
        }
        delete[] old_array;
    }
    array_[size_] = value;
    size_++;
}

template <class T>
void Vector<T>::PopBack() {
    size_--;
}

template <class T>
void Vector<T>::Resize(size_t new_size) {
    if (new_size > capacity_) {
        T *old_array = array_;
        array_ = new T[new_size];
        for (size_t i = 0; i < size_; ++i) {
            array_[i] = old_array[i];
        }
        capacity_ = new_size;
        delete[] old_array;
    }
    size_ = new_size;
}

template <class T>
void Vector<T>::Resize(size_t new_size, T value) {
    if (new_size > capacity_) {
        T *old_array = array_;
        array_ = new T[new_size];
        for (size_t i = 0; i < size_; ++i) {
            array_[i] = old_array[i];
        }
        capacity_ = new_size;
        delete[] old_array;
    }
    if (new_size > size_) {
        for (size_t i = size_; i < new_size; ++i) {
            array_[i] = value;
        }
    }
    size_ = new_size;
}

template <class T>
void Vector<T>::Reserve(size_t new_cap) {
    if (new_cap > capacity_) {
        T *old_array = array_;
        array_ = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) {
            array_[i] = old_array[i];
        }
        capacity_ = new_cap;
        delete[] old_array;
    }
}

template <class T>
void Vector<T>::ShrinkToFit() {
    if (capacity_ > size_) {
        T *old_array = array_;
        array_ = new T[size_];
        for (size_t i = 0; i < size_; ++i) {
            array_[i] = old_array[i];
        }
        capacity_ = size_;
        delete[] old_array;
    }
}

template <class T>
void Vector<T>::Swap(Vector<T> &other) {
    T *temp_array = array_;
    size_t temp_size = size_;
    size_t temp_cap = capacity_;
    array_ = other.array_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.array_ = temp_array;
    other.size_ = temp_size;
    other.capacity_ = temp_cap;
}

template <class T>
T Vector<T>::operator[](size_t index) const {
    return array_[index];
}

template <class T>
T &Vector<T>::operator[](size_t index) {
    return array_[index];
}

template <class T>
T Vector<T>::At(size_t index) const {
    if (index >= size_) {
        throw VectorOutOfRange{};
    }
    return array_[index];
}

template <class T>
T &Vector<T>::At(size_t index) {
    if (index >= size_) {
        throw VectorOutOfRange{};
    }
    return array_[index];
}

template <class T>
T Vector<T>::Front() const {
    return array_[0];
}

template <class T>
T &Vector<T>::Front() {
    return array_[0];
}

template <class T>
T Vector<T>::Back() const {
    return array_[size_ - 1];
}

template <class T>
T &Vector<T>::Back() {
    return array_[size_ - 1];
}

template <class T>
bool Vector<T>::Empty() const {
    return size_ == 0;
}

template <class T>
size_t Vector<T>::Size() const {
    return size_;
}

template <class T>
size_t Vector<T>::Capacity() const {
    return capacity_;
}

template <class T>
T *Vector<T>::Data() const {
    return array_;
}

template <class T>
bool Vector<T>::operator<(const Vector<T> &other) const {
    size_t min_size = ((size_ < other.size_) ? size_ : other.size_);
    for (size_t i = 0; i < min_size; ++i) {
        if (array_[i] < other.array_[i]) {
            return true;
        }
        if (array_[i] > other.array_[i]) {
            return false;
        }
    }
    return size_ < other.size_;
}

template <class T>
bool Vector<T>::operator>(const Vector<T> &other) const {
    return !(*this <= other);
}

template <class T>
bool Vector<T>::operator<=(const Vector<T> &other) const {
    size_t min_size = ((size_ < other.size_) ? size_ : other.size_);
    for (size_t i = 0; i < min_size; ++i) {
        if (array_[i] < other.array_[i]) {
            return true;
        }
        if (array_[i] > other.array_[i]) {
            return false;
        }
    }
    return size_ <= other.size_;
}

template <class T>
bool Vector<T>::operator>=(const Vector<T> &other) const {
    return !(*this < other);
}

template <class T>
bool Vector<T>::operator==(const Vector<T> &other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (array_[i] != other.array_[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool Vector<T>::operator!=(const Vector<T> &other) const {
    return !(*this == other);
}