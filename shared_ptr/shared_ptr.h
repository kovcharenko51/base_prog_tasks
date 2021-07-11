#pragma once

#include <algorithm>
#include <iostream>

class BadWeakPtr : public std::runtime_error {
public:
    BadWeakPtr() : std::runtime_error("BadWeakPtr") {
    }
};

struct Counter {
    size_t use_count = 0;
    size_t weak_count = 0;
};

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
private:
    T* ptr_;
    Counter* counter_ptr_;

public:
    SharedPtr();
    explicit SharedPtr(T*);
    SharedPtr(std::nullptr_t);  //  NOLINT
    void DeletePtr();
    ~SharedPtr();
    SharedPtr(const SharedPtr<T>&);
    SharedPtr<T>& operator=(const SharedPtr<T>&);
    SharedPtr(SharedPtr<T>&&) noexcept;
    SharedPtr<T>& operator=(SharedPtr<T>&&) noexcept;
    explicit SharedPtr(const WeakPtr<T>&);
    void Reset(T* = nullptr);
    void Swap(SharedPtr<T>&);
    T* Get();
    size_t UseCount() const;
    T& operator*();
    T* operator->();
    explicit operator bool() const;
    friend class WeakPtr<T>;
};

template <class T>
class WeakPtr {
private:
    T* ptr_;
    Counter* counter_ptr_;

public:
    WeakPtr();
    explicit WeakPtr(T*);
    WeakPtr(std::nullptr_t);  //  NOLINT
    void DeletePtr();
    ~WeakPtr();
    WeakPtr(const WeakPtr<T>&);
    WeakPtr<T>& operator=(const WeakPtr<T>&);
    WeakPtr(WeakPtr<T>&&) noexcept;
    WeakPtr<T>& operator=(WeakPtr<T>&&) noexcept;
    WeakPtr(const SharedPtr<T>&);  //  NOLINT
    void Swap(WeakPtr<T>&);
    void Reset();
    size_t UseCount() const;
    bool Expired() const;
    SharedPtr<T> Lock() const;
    friend class SharedPtr<T>;
};

template <class T>
SharedPtr<T>::SharedPtr() {
    ptr_ = nullptr;
    counter_ptr_ = nullptr;
}

template <class T>
SharedPtr<T>::SharedPtr(T* ptr) {
    ptr_ = ptr;
    counter_ptr_ = new Counter();
    counter_ptr_->use_count++;
}

template <class T>
SharedPtr<T>::SharedPtr(std::nullptr_t) {  //  NOLINT
    ptr_ = nullptr;
    counter_ptr_ = new Counter();
    counter_ptr_->use_count++;
}

template <class T>
void SharedPtr<T>::DeletePtr() {
    if (counter_ptr_ == nullptr) {
        return;
    }
    counter_ptr_->use_count--;
    if (counter_ptr_->use_count == 0) {
        delete ptr_;
        if (counter_ptr_->weak_count == 0) {
            delete counter_ptr_;
        }
    }
}

template <class T>
SharedPtr<T>::~SharedPtr() {
    DeletePtr();
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) {
    ptr_ = other.ptr_;
    counter_ptr_ = other.counter_ptr_;
    if (counter_ptr_ != nullptr) {
        counter_ptr_->use_count++;
    }
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    if (this != &other) {
        DeletePtr();
        ptr_ = other.ptr_;
        counter_ptr_ = other.counter_ptr_;
        counter_ptr_->use_count++;
    }
    return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    counter_ptr_ = other.counter_ptr_;
    other.ptr_ = nullptr;
    other.counter_ptr_ = nullptr;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
    if (this != &other) {
        DeletePtr();
        ptr_ = other.ptr_;
        counter_ptr_ = other.counter_ptr_;
        other.ptr_ = nullptr;
        other.counter_ptr_ = nullptr;
    }
    return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T>& weak_ptr) {
    if (weak_ptr.Expired()) {
        throw BadWeakPtr{};
    }
    ptr_ = weak_ptr.ptr_;
    counter_ptr_ = weak_ptr.counter_ptr_;
    counter_ptr_->use_count++;
}

template <class T>
void SharedPtr<T>::Reset(T* ptr) {
    if (ptr_ != ptr) {
        DeletePtr();
        ptr_ = ptr;
        counter_ptr_ = new Counter();
        counter_ptr_->use_count++;
    }
}

template <class T>
void SharedPtr<T>::Swap(SharedPtr<T>& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(counter_ptr_, other.counter_ptr_);
}

template <class T>
T* SharedPtr<T>::Get() {
    return ptr_;
}

template <class T>
size_t SharedPtr<T>::UseCount() const {
    if (ptr_ == nullptr) {
        return 0;
    }
    return counter_ptr_->use_count;
}

template <class T>
T& SharedPtr<T>::operator*() {
    return *ptr_;
}

template <class T>
T* SharedPtr<T>::operator->() {
    return ptr_;
}

template <class T>
SharedPtr<T>::operator bool() const {
    return ptr_ != nullptr;
}

template <class T>
WeakPtr<T>::WeakPtr() {
    ptr_ = nullptr;
    counter_ptr_ = nullptr;
}

template <class T>
WeakPtr<T>::WeakPtr(T* ptr) {
    ptr_ = ptr;
    counter_ptr_ = new Counter();
    counter_ptr_->weak_count++;
}

template <class T>
WeakPtr<T>::WeakPtr(std::nullptr_t) {
    ptr_ = nullptr;
    counter_ptr_ = new Counter();
    counter_ptr_->weak_count++;
}

template <class T>
void WeakPtr<T>::DeletePtr() {
    if (counter_ptr_ == nullptr) {
        return;
    }
    counter_ptr_->weak_count--;
    if ((counter_ptr_->weak_count == 0) && (counter_ptr_->use_count == 0)) {
        delete counter_ptr_;
    }
}

template <class T>
WeakPtr<T>::~WeakPtr() {
    DeletePtr();
}

template <class T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& other) {
    ptr_ = other.ptr_;
    counter_ptr_ = other.counter_ptr_;
    if (counter_ptr_ != nullptr) {
        counter_ptr_->weak_count++;
    }
}

template <class T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& other) {
    if (this != &other) {
        DeletePtr();
        ptr_ = other.ptr_;
        counter_ptr_ = other.counter_ptr_;
        counter_ptr_->weak_count++;
    }
    return *this;
}

template <class T>
WeakPtr<T>::WeakPtr(WeakPtr<T>&& other) noexcept {
    ptr_ = other.ptr_;
    counter_ptr_ = other.counter_ptr_;
    other.ptr_ = nullptr;
    other.counter_ptr_ = nullptr;
}

template <class T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& other) noexcept {
    if (this != &other) {
        DeletePtr();
        ptr_ = other.ptr_;
        counter_ptr_ = other.counter_ptr_;
        other.ptr_ = nullptr;
        other.counter_ptr_ = nullptr;
    }
    return *this;
}

template <class T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& shared_ptr) {
    ptr_ = shared_ptr.ptr_;
    counter_ptr_ = shared_ptr.counter_ptr_;
    if (ptr_ != nullptr) {
        counter_ptr_->weak_count++;
    }
}

template <class T>
void WeakPtr<T>::Swap(WeakPtr<T>& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(counter_ptr_, other.counter_ptr_);
}

template <class T>
void WeakPtr<T>::Reset() {
    DeletePtr();
    ptr_ = nullptr;
    counter_ptr_ = nullptr;
}

template <class T>
size_t WeakPtr<T>::UseCount() const {
    if (ptr_ == nullptr) {
        return 0;
    }
    return counter_ptr_->use_count;
}

template <class T>
bool WeakPtr<T>::Expired() const {
    return UseCount() == 0;
}

template <class T>
SharedPtr<T> WeakPtr<T>::Lock() const {
    if (Expired()) {
        return SharedPtr<T>();
    }
    return SharedPtr<T>(*this);
}