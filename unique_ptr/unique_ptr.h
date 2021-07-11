#pragma once

#define MAKE_UNIQUE_IMPLEMENTED

template <class T>
class UniquePtr {
private:
    T* ptr_;

public:
    UniquePtr();
    explicit UniquePtr(T*);
    UniquePtr(const UniquePtr<T>&) = delete;
    UniquePtr(UniquePtr<T>&&) noexcept;
    ~UniquePtr();
    UniquePtr<T>& operator=(const UniquePtr<T>&) = delete;
    UniquePtr<T>& operator=(UniquePtr<T>&&) noexcept;
    T* Release();
    void Reset(T* = nullptr);
    void Swap(UniquePtr<T>&);
    T* Get();
    T& operator*();
    T* operator->();
    explicit operator bool() const;
};

template <class T>
UniquePtr<T>::UniquePtr() {
    ptr_ = nullptr;
}

template <class T>
UniquePtr<T>::UniquePtr(T* ptr) {
    ptr_ = ptr;
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

template <class T>
UniquePtr<T>::~UniquePtr() {
    delete ptr_;
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
    if (this != &other) {
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}

template <class T>
T* UniquePtr<T>::Release() {
    auto old_ptr = ptr_;
    ptr_ = nullptr;
    return old_ptr;
}

template <class T>
void UniquePtr<T>::Reset(T* ptr) {
    delete ptr_;
    ptr_ = ptr;
}

template <class T>
void UniquePtr<T>::Swap(UniquePtr<T>& other) {
    auto temp_ptr = ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = temp_ptr;
}

template <class T>
T* UniquePtr<T>::Get() {
    return ptr_;
}

template <class T>
T& UniquePtr<T>::operator*() {
    return *ptr_;
}

template <class T>
T* UniquePtr<T>::operator->() {
    return ptr_;
}

template <class T>
UniquePtr<T>::operator bool() const {
    return ptr_ != nullptr;
}

template <class T, class... Args>
UniquePtr<T> MakeUnique(Args... args) {
    return UniquePtr<T>(new T(args...));
}