#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

namespace pshellscript {
    struct Token {
        enum class Type {
            Plus, PlusEqual, Minus, MinusEqual, 
            Slash, SlashEqual, Asterisk, AsteriskEqual,

            Equal, EqualEqual, Bang, BangEqual,
            Less, LessEqual, Greater, GreaterEqual,

            Function, If, Else, For, Variable, Identifier,
            Return, Echo,

            LeftParen, RightParen, LeftBrace, RightBrace, 
            LeftBracket, RightBracket,

            String, Number
        };
    
        // Member declarations
        Type type;
        std::string lexeme;
    
        // Method declarations
        inline Token(const Type type, const std::string& lexeme)
            : type(type), lexeme(lexeme) { }
    
        std::string to_string() const;
    };  
}

#endif