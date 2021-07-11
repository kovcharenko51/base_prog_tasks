#pragma once

#include <algorithm>

class BadOptionalAccess {
public:
    BadOptionalAccess() = default;
};

template <class T>
class Optional {
private:
    char memory_[sizeof(T)];
    bool has_value_;

public:
    Optional();
    Optional(const Optional<T>&);
    Optional(Optional<T>&&) noexcept;
    explicit Optional(const T&);
    explicit Optional(T&&);
    ~Optional();
    Optional<T>& operator=(const Optional<T>&);
    Optional<T>& operator=(Optional<T>&&) noexcept;
    Optional<T>& operator=(const T&);
    Optional<T>& operator=(T&&) noexcept;
    bool HasValue() const;
    explicit operator bool() const;
    const T& Value() const;
    T& Value();
    T ValueOr(T) const;
    T& operator*();
    T operator*() const;
    T* operator->();
    const T* operator->() const;
    template <class... Args>
    T& Emplace(Args...);
    void Reset();
    void Swap(Optional<T>&);
};

template <class T>
Optional<T>::Optional() {
    has_value_ = false;
}

template <class T>
Optional<T>::Optional(const Optional<T>& other) {
    has_value_ = other.has_value_;
    if (has_value_) {
        new (memory_) T(*reinterpret_cast<const T*>(other.memory_));
    }
}

template <class T>
Optional<T>::Optional(Optional<T>&& other) noexcept {
    has_value_ = other.has_value_;
    if (has_value_) {
        new (memory_) T(std::move(*reinterpret_cast<T*>(other.memory_)));
    }
}

template <class T>
Optional<T>::Optional(const T& obj) {
    has_value_ = true;
    new (memory_) T(obj);
}

template <class T>
Optional<T>::Optional(T&& obj) {
    has_value_ = true;
    new (memory_) T(std::move(obj));
}

template <class T>
Optional<T>::~Optional() {
    if (has_value_) {
        reinterpret_cast<T*>(memory_)->~T();
    }
}

template <class T>
Optional<T>& Optional<T>::operator=(const Optional<T>& other) {
    if (this != &other) {
        if (has_value_) {
            reinterpret_cast<T*>(memory_)->~T();
        }
        has_value_ = other.has_value_;
        if (has_value_) {
            new (memory_) T(*reinterpret_cast<const T*>(other.memory_));
        }
    }
    return *this;
}

template <class T>
Optional<T>& Optional<T>::operator=(Optional<T>&& other) noexcept {
    if (this != &other) {
        if (has_value_) {
            reinterpret_cast<T*>(memory_)->~T();
        }
        has_value_ = other.has_value_;
        if (has_value_) {
            new (memory_) T(std::move(*reinterpret_cast<T*>(other.memory_)));
        }
    }
    return *this;
}

template <class T>
Optional<T>& Optional<T>::operator=(const T& obj) {
    if (has_value_) {
        reinterpret_cast<T*>(memory_)->~T();
    }
    has_value_ = true;
    new (memory_) T(obj);
    return *this;
}

template <class T>
Optional<T>& Optional<T>::operator=(T&& obj) noexcept {
    if (has_value_) {
        reinterpret_cast<T*>(memory_)->~T();
    }
    has_value_ = true;
    new (memory_) T(std::move(obj));
    return *this;
}

template <class T>
bool Optional<T>::HasValue() const {
    return has_value_;
}

template <class T>
Optional<T>::operator bool() const {
    return has_value_;
}

template <class T>
const T& Optional<T>::Value() const {
    if (!has_value_) {
        throw BadOptionalAccess{};
    }
    return *reinterpret_cast<const T*>(memory_);
}

template <class T>
T& Optional<T>::Value() {
    if (!has_value_) {
        throw BadOptionalAccess{};
    }
    return *reinterpret_cast<T*>(memory_);
}

template <class T>
T Optional<T>::ValueOr(T alternative) const {
    if (!has_value_) {
        return alternative;
    }
    return *reinterpret_cast<const T*>(memory_);
}

template <class T>
T Optional<T>::operator*() const {
    return *reinterpret_cast<const T*>(memory_);
}

template <class T>
T& Optional<T>::operator*() {
    return *reinterpret_cast<T*>(memory_);
}

template <class T>
T* Optional<T>::operator->() {
    return reinterpret_cast<T*>(memory_);
}

template <class T>
const T* Optional<T>::operator->() const {
    return reinterpret_cast<const T*>(memory_);
}

template <class T>
template <class... Args>
T& Optional<T>::Emplace(Args... args) {
    if (has_value_) {
        reinterpret_cast<T*>(memory_)->~T();
    }
    has_value_ = true;
    new (memory_) T(args...);
    return *reinterpret_cast<T*>(memory_);
}

template <class T>
void Optional<T>::Reset() {
    if (has_value_) {
        reinterpret_cast<T*>(memory_)->~T();
    }
    has_value_ = false;
}

template <class T>
void Optional<T>::Swap(Optional<T>& other) {
    std::swap(memory_, other.memory_);
    std::swap(has_value_, other.has_value_);
}
