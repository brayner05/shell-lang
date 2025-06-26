#include <string>
#include <sstream>
#include "tokens.hpp"

namespace pshellscript {
    std::string Token::to_string() const {
        using Type = Token::Type;
    
        auto stream = std::stringstream();
        stream << "Token ( ";
    
        switch (this->type) {
            case Type::Plus: {
                stream << "Plus";
                break;
            }

            case Type::SemiColon: {
                stream << "SemiColon";
                break;
            }

            case Type::Comma: {
                stream << "Comma";
                break;
            }

            case Type::True: {
                stream << "Boolean(true)";
                break;
            }

            case Type::False: {
                stream << "Boolean(false)";
                break;
            }

            case Type::Modulo: {
                stream << "Modulo";
                break;
            }

            case Type::ModuloEqual: {
                stream << "ModuloEqual";
                break;
            }

            case Type::PlusEqual: {
                stream << "PlusEqual";
                break;
            }
    
            case Type::Minus: {
                stream << "Minus";
                break;
            }

            case Type::MinusEqual: {
                stream << "MinusEqual";
                break;
            }
    
            case Type::Asterisk: {
                stream << "Asterisk";
                break;
            }

            case Type::AsteriskEqual: {
                stream << "AsteriskEqual";
                break;
            }
    
            case Type::Slash: {
                stream << "Slash";
                break;
            }

            case Type::SlashEqual: {
                stream << "SlashEqual";
                break;
            }
    
            case Type::Number: {
                stream << "Number";
                break;
            }

            case Type::String: {
                stream << "String";
                break;
            }

            case Type::Equal: {
                stream << "Equal";
                break;
            }

            case Type::EqualEqual: {
                stream << "EqualEqual";
                break;
            }

            case Type::Bang: {
                stream << "BangEqual";
                break;
            }

            case Type::Eof: {
                stream << "Eof";
                break;
            }

            case Type::BangEqual: {
                stream << "BangEqual";
                break;
            }

            case Type::Less: {
                stream << "Less";
                break;
            }

            case Type::LessEqual: {
                stream << "LessEqual";
                break;
            }

            case Type::Greater: {
                stream << "Plus";
                break;
            }

            case Type::GreaterEqual: {
                stream << "Plus";
                break;
            }

            case Type::Function: {
                stream << "Function";
                break;
            }

            case Type::If: {
                stream << "If";
                break;
            }

            case Type::Echo: {
                stream << "Echo";
                break;
            }

            case Type::Else: {
                stream << "Else";
                break;
            }

            case Type::For: {
                stream << "For";
                break;
            }

            case Type::Variable: {
                stream << "Variable";
                break;
            }

            case Type::Identifier: {
                stream << "Identifier";
                break;
            }

            case Type::Return: {
                stream << "Return";
                break;
            }
            
            case Type::LeftParen: {
                stream << "LeftParen";
                break;
            }

            case Type::RightParen: {
                stream << "RightParen";
                break;
            }

            case Type::LeftBrace: {
                stream << "LeftBrace";
                break;
            }

            case Type::RightBrace: {
                stream << "RightBrace";
                break;
            }

            case Type::LeftBracket: {
                stream << "LeftBracket";
                break;
            }

            case Type::RightBracket: {
                stream << "RightBracket";
                break;
            }

            case Type::AndAnd: {
                stream << "AndAnd";
                break;
            }

            case Type::OrOr: {
                stream << "OrOr";
                break;
            }
        }
    
        stream << ", \'" << this->lexeme << "\' )";
        return stream.str();
    }
}