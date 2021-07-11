#pragma once

#include <iostream>

template <class T>
class CircularBuffer {
private:
    T* buffer_;
    size_t start_;
    size_t end_;
    size_t capacity_;
    size_t size_;

public:
    CircularBuffer();
    explicit CircularBuffer(size_t);
    CircularBuffer(const CircularBuffer<T>&);
    CircularBuffer<T>& operator=(const CircularBuffer<T>&);
    ~CircularBuffer();
    T operator[](size_t) const;
    T& operator[](size_t);
    T Front() const;
    T& Front();
    T Back() const;
    T& Back();
    bool Empty() const;
    size_t Size() const;
    size_t Capacity() const;
    void PushBack(T);
    void PushFront(T);
    void PopBack();
    void PopFront();
    void Clear();
    void Reserve(size_t);
    void Swap(CircularBuffer<T>&);
    T* CopyOldBuffer();
};

template <class T>
CircularBuffer<T>::CircularBuffer() {
    buffer_ = nullptr;
    start_ = 0;
    end_ = 0;
    size_ = 0;
    capacity_ = 0;
}

template <class T>
CircularBuffer<T>::CircularBuffer(size_t cap) {
    buffer_ = nullptr;
    start_ = 0;
    end_ = 0;
    size_ = 0;
    capacity_ = 0;
    if (cap > 0) {
        buffer_ = new T[cap];
        start_ = 0;
        end_ = 0;
        capacity_ = cap;
    }
}

template <class T>
void CopyBuffer(T* first_buffer, T* second_buffer, size_t start_ind, size_t end_ind) {
    size_t min_ind = (start_ind < end_ind) ? start_ind : end_ind;
    size_t max_ind = (start_ind > end_ind) ? start_ind : end_ind;
    for (size_t i = min_ind; i <= max_ind; ++i) {
        first_buffer[i] = second_buffer[i];
    }
}

template <class T>
T* CircularBuffer<T>::CopyOldBuffer() {
    T* new_buffer = new T[2 * capacity_];
    for (size_t i = 0; i < size_; ++i) {
        new_buffer[i] = (*this)[i];
    }
    return new_buffer;
}

template <class T>
CircularBuffer<T>::CircularBuffer(const CircularBuffer<T>& other) {
    buffer_ = nullptr;
    start_ = 0;
    end_ = 0;
    size_ = 0;
    capacity_ = 0;
    if (other.capacity_ > 0) {
        buffer_ = new T[other.capacity_];
        start_ = other.start_;
        end_ = other.end_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        CopyBuffer(buffer_, other.buffer_, start_, end_);
    }
}

template <class T>
CircularBuffer<T>& CircularBuffer<T>::operator=(const CircularBuffer<T>& other) {
    if (this != &other) {
        T* old_buffer = buffer_;
        buffer_ = nullptr;
        start_ = 0;
        end_ = 0;
        size_ = 0;
        capacity_ = 0;
        if (other.capacity_ > 0) {
            buffer_ = new T[other.capacity_];
            start_ = other.start_;
            end_ = other.end_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            CopyBuffer(buffer_, other.buffer_, start_, end_);
            delete[] old_buffer;
        }
    }
    return *this;
}

template <class T>
CircularBuffer<T>::~CircularBuffer() {
    delete[] buffer_;
}

template <class T>
T CircularBuffer<T>::operator[](size_t index) const {
    return buffer_[(start_ + index) % capacity_];
}

template <class T>
T& CircularBuffer<T>::operator[](size_t index) {
    return buffer_[(start_ + index) % capacity_];
}

template <class T>
T CircularBuffer<T>::Front() const {
    return buffer_[start_];
}

template <class T>
T& CircularBuffer<T>::Front() {
    return buffer_[start_];
}

template <class T>
T CircularBuffer<T>::Back() const {
    return buffer_[end_];
}

template <class T>
T& CircularBuffer<T>::Back() {
    return buffer_[end_];
}

template <class T>
bool CircularBuffer<T>::Empty() const {
    return size_ == 0;
}

template <class T>
size_t CircularBuffer<T>::Size() const {
    return size_;
}

template <class T>
size_t CircularBuffer<T>::Capacity() const {
    return capacity_;
}

template <class T>
void CircularBuffer<T>::PushBack(T value) {
    if (capacity_ == 0) {
        buffer_ = new T[1];
        capacity_ = 1;
        start_ = 0;
        end_ = 0;
    } else if (size_ == capacity_) {
        T* old_buffer = buffer_;
        T* new_buffer = CopyOldBuffer();
        buffer_ = new_buffer;
        delete[] old_buffer;
        capacity_ *= 2;
        start_ = 0;
        end_ = size_;
    } else if (end_ == capacity_ - 1) {
        end_ = 0;
    } else if (size_ == 0) {
        end_ = start_;
    } else {
        end_++;
    }
    buffer_[end_] = value;
    size_++;
}

template <class T>
void CircularBuffer<T>::PushFront(T value) {
    if (capacity_ == 0) {
        buffer_ = new T[1];
        capacity_ = 1;
        start_ = 0;
        end_ = 0;
    } else if (size_ == capacity_) {
        T* old_buffer = buffer_;
        T* new_buffer = CopyOldBuffer();
        buffer_ = new_buffer;
        delete[] old_buffer;
        capacity_ *= 2;
        start_ = capacity_ - 1;
        end_ = size_ - 1;
    } else if (start_ == 0) {
        start_ = capacity_ - 1;
    } else if (size_ == 0) {
        start_ = 0;
    } else {
        start_--;
    }
    buffer_[start_] = value;
    size_++;
}

template <class T>
void CircularBuffer<T>::PopBack() {
    if (end_ == 0) {
        end_ = capacity_ - 1;
    } else {
        end_--;
    }
    size_--;
}

template <class T>
void CircularBuffer<T>::PopFront() {
    if (start_ == capacity_ - 1) {
        start_ = 0;
    } else {
        start_++;
    }
    size_--;
}

template <class T>
void CircularBuffer<T>::Clear() {
    size_ = 0;
    start_ = 0;
    end_ = 0;
}

template <class T>
void CircularBuffer<T>::Reserve(size_t cap) {
    T* old_buffer = buffer_;
    buffer_ = nullptr;
    start_ = 0;
    end_ = 0;
    if (cap > 0) {
        buffer_ = new T[cap];
        if (size_ != 0) {
            buffer_ = CopyOldBuffer();
            start_ = 0;
            end_ = size_ - 1;
        }
    }
    capacity_ = cap;
    delete[] old_buffer;
}

template <class T>
void SwapValues(T& first_val, T& sec_val) {
    T temp = first_val;
    first_val = sec_val;
    sec_val = temp;
}

template <class T>
void CircularBuffer<T>::Swap(CircularBuffer<T>& other) {
    if (this == &other) {
        return;
    }
    SwapValues(buffer_, other.buffer_);
    SwapValues(capacity_, other.capacity_);
    SwapValues(size_, other.size_);
    SwapValues(start_, other.start_);
    SwapValues(end_, other.end_);
}