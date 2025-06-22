#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <string>
#include <vector>
#include "pshellscript/lexer.hpp"
#include "pshellscript/tokens.hpp"

namespace debug {
    inline void dump_tokens(const std::vector<pshellscript::Token>& tokens) {
        for (const auto& token : tokens) {
            std::cout << token.to_string() << '\n';
        }
    }
}

#endif