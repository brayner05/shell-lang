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
    
            case Type::Minus: {
                stream << "Minus";
                break;
            }
    
            case Type::Asterisk: {
                stream << "Asterisk";
                break;
            }
    
            case Type::Slash: {
                stream << "Slash";
                break;
            }
    
            case Type::Number: {
                stream << "Number";
                break;
            }
        }
    
        stream << ", \'" << this->lexeme << "\' )";
        return stream.str();
    }
}