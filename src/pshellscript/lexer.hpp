#ifndef LEXER_HPP
#define LEXER_HPP

#include <vector>
#include <string>
#include <memory>
#include "tokens.hpp"
#include "../result.hpp"

namespace pshellscript::lexer {
    std::vector<Token> scan_tokens(const std::string& source);
}

#endif