#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

namespace pshellscript {
    struct Token {
        enum class Type {
            Plus, Minus, Slash, Asterisk,
            Number
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