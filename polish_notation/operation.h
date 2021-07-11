#pragma once

#include <memory>
#include <stack>

class WrongOperandsNumberError : public std::runtime_error {
public:
    WrongOperandsNumberError() : std::runtime_error("WrongOperandsNumberError") {
    }
};

class IOperation {
public:
    virtual void Calculate(std::stack<std::unique_ptr<IOperation>>*) const = 0;
    virtual ~IOperation() = default;
};

class Constant : public IOperation {
public:
    int value;
    explicit Constant(int);
    int Value() const;
    void Calculate(std::stack<std::unique_ptr<IOperation>>*) const override;
};

class IUnaryOperation : public IOperation {
public:
    int GetOperand(std::stack<std::unique_ptr<IOperation>>*) const;
    virtual int PerformOperation(int) const = 0;
    void Calculate(std::stack<std::unique_ptr<IOperation>>*) const override;
};

class IBinaryOperation : public IOperation {
public:
    std::pair<int, int> GetOperands(std::stack<std::unique_ptr<IOperation>>*) const;
    virtual int PerformOperation(int, int) const = 0;
    void Calculate(std::stack<std::unique_ptr<IOperation>>*) const override;
};

class Sum : public IBinaryOperation {
public:
    int PerformOperation(int, int) const override;
};

class Subtract : public IBinaryOperation {
public:
    int PerformOperation(int, int) const override;
};

class Multiply : public IBinaryOperation {
public:
    int PerformOperation(int, int) const override;
};

class Divide : public IBinaryOperation {
public:
    int PerformOperation(int, int) const override;
};

class Residual : public IBinaryOperation {
public:
    int PerformOperation(int, int) const override;
};

class Minimum : public IBinaryOperation {
public:
    int PerformOperation(int, int) const override;
};

class Maximum : public IBinaryOperation {
public:
    int PerformOperation(int, int) const override;
};

class AbsoluteValue : public IUnaryOperation {
public:
    int PerformOperation(int) const override;
};

class Square : public IUnaryOperation {
public:
    int PerformOperation(int) const override;
};
