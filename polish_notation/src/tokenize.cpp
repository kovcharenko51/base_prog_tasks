#include "tokenize.h"

bool PlusToken::operator==(const PlusToken&) const noexcept {
    return true;
}

bool MinusToken::operator==(const MinusToken&) const noexcept {
    return true;
}

bool MultiplyToken::operator==(const MultiplyToken&) const noexcept {
    return true;
}

bool DivideToken::operator==(const DivideToken&) const noexcept {
    return true;
}

bool ResidualToken::operator==(const ResidualToken&) const noexcept {
    return true;
}

bool OpeningBracketToken::operator==(const OpeningBracketToken&) const noexcept {
    return true;
}

bool ClosingBracketToken::operator==(const ClosingBracketToken&) const noexcept {
    return true;
}

bool SqrToken::operator==(const SqrToken&) const noexcept {
    return true;
}

bool MaxToken::operator==(const MaxToken&) const noexcept {
    return true;
}

bool MinToken::operator==(const MinToken&) const noexcept {
    return true;
}

bool AbsToken::operator==(const AbsToken&) const noexcept {
    return true;
}

bool NumberToken::operator==(const NumberToken& other) const noexcept {
    return value == other.value;
}

bool UnknownToken::operator==(const UnknownToken& other) const noexcept {
    return value == other.value;
}

std::vector<Token> Tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < expression.length()) {
        if (expression[i] == ' ') {
            i++;
            continue;
        }
        std::string str_token;
        while ((i < expression.length()) && (expression[i] != ' ')) {
            str_token += expression[i];
            i++;
        }
        Token token;
        if (str_token == "+") {
            token = PlusToken();
        } else if (str_token == "-") {
            token = MinusToken();
        } else if (str_token == "*") {
            token = MultiplyToken();
        } else if (str_token == "/") {
            token = DivideToken();
        } else if (str_token == "%") {
            token = ResidualToken();
        } else if (str_token == "(") {
            token = OpeningBracketToken();
        } else if (str_token == ")") {
            token = ClosingBracketToken();
        } else if (str_token == "sqr") {
            token = SqrToken();
        } else if (str_token == "max") {
            token = MaxToken();
        } else if (str_token == "min") {
            token = MinToken();
        } else if (str_token == "abs") {
            token = AbsToken();
        } else {
            int64_t num = strtoll(str_token.c_str(), nullptr, 10);
            if ((std::to_string(num) == str_token) || ((num == 0) && ((str_token == "+0") || (str_token == "-0"))) ||
                ((num > 0) && ("+" + std::to_string(num) == str_token))) {
                token = NumberToken{num};
            } else {
                token = UnknownToken{str_token};
            }
        }
        tokens.emplace_back(token);
    }
    return tokens;
}