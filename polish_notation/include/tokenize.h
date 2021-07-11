#include <string>
#include <variant>
#include <vector>

struct PlusToken {
    bool operator==(const PlusToken&) const noexcept;
};

struct MinusToken {
    bool operator==(const MinusToken&) const noexcept;
};

struct MultiplyToken {
    bool operator==(const MultiplyToken&) const noexcept;
};

struct DivideToken {
    bool operator==(const DivideToken&) const noexcept;
};

struct ResidualToken {
    bool operator==(const ResidualToken&) const noexcept;
};

struct OpeningBracketToken {
    bool operator==(const OpeningBracketToken&) const noexcept;
};

struct ClosingBracketToken {
    bool operator==(const ClosingBracketToken&) const noexcept;
};

struct SqrToken {
    bool operator==(const SqrToken&) const noexcept;
};

struct MaxToken {
    bool operator==(const MaxToken&) const noexcept;
};

struct MinToken {
    bool operator==(const MinToken&) const noexcept;
};

struct AbsToken {
    bool operator==(const AbsToken&) const noexcept;
};

struct NumberToken {
    int64_t value;
    bool operator==(const NumberToken&) const noexcept;
};

struct UnknownToken {
    std::string value;
    bool operator==(const UnknownToken&) const noexcept;
};

using Token = std::variant<PlusToken, MinusToken, MultiplyToken, DivideToken, ResidualToken, OpeningBracketToken,
                           ClosingBracketToken, SqrToken, MaxToken, MinToken, AbsToken, NumberToken, UnknownToken>;

std::vector<Token> Tokenize(const std::string&);