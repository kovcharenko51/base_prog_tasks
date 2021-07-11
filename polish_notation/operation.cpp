#include "operation.h"

Constant::Constant(int value) {
    this->value = value;
}

int Constant::Value() const {
    return value;
}

void Constant::Calculate(std::stack<std::unique_ptr<IOperation>>* calc_stack) const {
    calc_stack->push(std::make_unique<Constant>(Constant(Value())));
}

int IUnaryOperation::GetOperand(std::stack<std::unique_ptr<IOperation>>* calc_stack) const {
    if (calc_stack->empty()) {
        throw WrongOperandsNumberError{};
    }
    std::unique_ptr<IOperation> operand = std::move(calc_stack->top());
    calc_stack->pop();
    operand->Calculate(calc_stack);
    operand = std::move(calc_stack->top());
    calc_stack->pop();
    return dynamic_cast<Constant*>(operand.get())->Value();
}

void IUnaryOperation::Calculate(std::stack<std::unique_ptr<IOperation>>* calc_stack) const {
    int result = PerformOperation(GetOperand(calc_stack));
    calc_stack->push(std::make_unique<Constant>(Constant(result)));
}

std::pair<int, int> IBinaryOperation::GetOperands(std::stack<std::unique_ptr<IOperation>>* calc_stack) const {
    if (calc_stack->empty()) {
        throw WrongOperandsNumberError{};
    }
    std::unique_ptr<IOperation> first_operand = std::move(calc_stack->top());
    calc_stack->pop();
    first_operand->Calculate(calc_stack);
    first_operand = std::move(calc_stack->top());
    calc_stack->pop();
    int first_value = dynamic_cast<Constant*>(first_operand.get())->Value();
    if (calc_stack->empty()) {
        throw WrongOperandsNumberError{};
    }
    std::unique_ptr<IOperation> sec_operand = std::move(calc_stack->top());
    calc_stack->pop();
    sec_operand->Calculate(calc_stack);
    sec_operand = std::move(calc_stack->top());
    calc_stack->pop();
    int sec_value = dynamic_cast<Constant*>(sec_operand.get())->Value();
    return std::pair(first_value, sec_value);
}

void IBinaryOperation::Calculate(std::stack<std::unique_ptr<IOperation>>* calc_stack) const {
    std::pair operands = GetOperands(calc_stack);
    int result = PerformOperation(operands.first, operands.second);
    calc_stack->push(std::make_unique<Constant>(Constant(result)));
}

int Sum::PerformOperation(int first_op, int sec_op) const {
    return first_op + sec_op;
}

int Subtract::PerformOperation(int first_op, int sec_op) const {
    return first_op - sec_op;
}

int Multiply::PerformOperation(int first_op, int sec_op) const {
    return first_op * sec_op;
}

int Divide::PerformOperation(int first_op, int sec_op) const {
    return first_op / sec_op;
}

int Residual::PerformOperation(int first_op, int sec_op) const {
    return first_op % sec_op;
}

int Minimum::PerformOperation(int first_op, int sec_op) const {
    return (first_op < sec_op) ? first_op : sec_op;
}

int Maximum::PerformOperation(int first_op, int sec_op) const {
    return (first_op > sec_op) ? first_op : sec_op;
}

int AbsoluteValue::PerformOperation(int value) const {
    return (value > 0) ? value : -value;
}

int Square::PerformOperation(int value) const {
    return value * value;
}