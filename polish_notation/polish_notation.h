#pragma once

#include <string>
#include "operation.h"
#include "tokenize.h"

class UnknownSymbolError : public std::runtime_error {
public:
    UnknownSymbolError() : std::runtime_error("UnknownSymbolError") {
    }
};

class WrongExpressionError : public std::runtime_error {
public:
    WrongExpressionError() : std::runtime_error("WrongExpressionError") {
    }
};

int ParsePolishNotation(const std::string& input);
