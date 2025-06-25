#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <iostream>
#include <string>
#include <vector>
#include "result.hpp"
#include "pshellscript/lexer.hpp"
#include "pshellscript/tokens.hpp"

namespace debug {
    inline void dump_tokens(const std::vector<Result<pshellscript::Token>>& tokens) {
        for (const auto& token : tokens) {
            if (!token.is_error()) {
                std::cout << token.get_value().to_string() << '\n';
            }
        }
    }
}

#endif