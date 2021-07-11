#include "polish_notation.h"

int ParsePolishNotation(const std::string& input) {
    std::vector<Token> tokens = Tokenize(input);
    std::stack<std::unique_ptr<IOperation>> calc_stack;
    while (!tokens.empty()) {
        Token token = tokens.back();
        if (std::holds_alternative<PlusToken>(token)) {
            calc_stack.push(std::make_unique<Sum>(Sum()));
        } else if (std::holds_alternative<MinusToken>(token)) {
            calc_stack.push(std::make_unique<Subtract>(Subtract()));
        } else if (std::holds_alternative<MultiplyToken>(token)) {
            calc_stack.push(std::make_unique<Multiply>(Multiply()));
        } else if (std::holds_alternative<DivideToken>(token)) {
            calc_stack.push(std::make_unique<Divide>(Divide()));
        } else if (std::holds_alternative<ResidualToken>(token)) {
            calc_stack.push(std::make_unique<Residual>(Residual()));
        } else if (std::holds_alternative<MinToken>(token)) {
            calc_stack.push(std::make_unique<Minimum>(Minimum()));
        } else if (std::holds_alternative<MaxToken>(token)) {
            calc_stack.push(std::make_unique<Maximum>(Maximum()));
        } else if (std::holds_alternative<AbsToken>(token)) {
            calc_stack.push(std::make_unique<AbsoluteValue>(AbsoluteValue()));
        } else if (std::holds_alternative<SqrToken>(token)) {
            calc_stack.push(std::make_unique<Square>(Square()));
        } else if (std::holds_alternative<NumberToken>(token)) {
            calc_stack.push(std::make_unique<Constant>(Constant(std::get<NumberToken>(token).value)));
        } else {
            throw UnknownSymbolError{};
        }
        tokens.pop_back();
    }
    std::unique_ptr<IOperation> operation = std::move(calc_stack.top());
    calc_stack.pop();
    operation->Calculate(&calc_stack);
    if (calc_stack.size() != 1) {
        throw WrongExpressionError{};
    }
    return dynamic_cast<Constant*>(calc_stack.top().get())->Value();
}
