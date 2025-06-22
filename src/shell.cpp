#include <iostream>
#include <string>
#include "pshellscript/lexer.hpp"
#include "pshellscript/tokens.hpp"
#include "debug.hpp"

namespace config {
    static std::string prompt = "$ ";
}

static int process_line(const std::string& line) {
    using namespace pshellscript;
    auto tokens = lexer::scan_tokens(line);
    debug::dump_tokens(tokens);
    return 0;
}


int main() {
    std::string line;
    while (1) {
        std::cout << config::prompt;
        std::getline(std::cin, line);

        if (line == "exit") {
            break;
        }

        process_line(line);
    }
}