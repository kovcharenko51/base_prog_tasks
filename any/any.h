#include <memory>

class BadAnyCast : public std::runtime_error {
public:
    BadAnyCast() : std::runtime_error("BadAnyCast") {
    }
};

class IBase {
public:
    virtual std::unique_ptr<IBase> Clone() = 0;
    virtual ~IBase() = default;
};

template <class T>
class Derived : public IBase {
private:
    T value_;

public:
    explicit Derived(T);
    std::unique_ptr<IBase> Clone() override;
    T GetValue();
};

class Any {
private:
    std::unique_ptr<IBase> ptr_;

public:
    Any();
    Any(const Any&);
    template <class T>
    Any(T);  //  NOLINT
    Any& operator=(const Any&);
    Any& operator=(Any&&) noexcept;
    void Swap(Any& other);
    void Reset();
    bool HasValue();
    const std::unique_ptr<IBase>& GetPtr() const;
};

inline Any::Any() {
    ptr_ = nullptr;
}

inline Any::Any(const Any& other) {
    ptr_ = other.ptr_->Clone();
}

inline Any& Any::operator=(const Any& other) {
    ptr_ = other.ptr_->Clone();
    return *this;
}

template <class T>
inline Any::Any(T value) {
    ptr_ = std::make_unique<Derived<T>>(value);
}

inline Any& Any::operator=(Any&& other) noexcept {
    ptr_ = std::move(other.ptr_);
    return *this;
}

inline void Any::Swap(Any& other) {
    std::swap(ptr_, other.ptr_);
}

inline void Any::Reset() {
    ptr_ = nullptr;
}

inline bool Any::HasValue() {
    return ptr_ != nullptr;
}

template <class T>
Derived<T>::Derived(T value) {
    value_ = value;
}

template <class T>
std::unique_ptr<IBase> Derived<T>::Clone() {
    return std::make_unique<Derived<T>>(value_);
}

template <class T>
T Derived<T>::GetValue() {
    return value_;
}

inline const std::unique_ptr<IBase>& Any::GetPtr() const {
    return ptr_;
}

template <class T>
T AnyCast(const Any& value) {
    if (value.GetPtr() == nullptr) {
        throw BadAnyCast{};
    }
    auto ptr = dynamic_cast<Derived<T>*>(value.GetPtr().get());
    if (ptr == nullptr) {
        throw BadAnyCast{};
    }
    return ptr->GetValue();
}