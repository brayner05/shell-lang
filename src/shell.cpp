#include <iostream>
#include <string>
#include "pshellscript/lexer.hpp"
#include "pshellscript/tokens.hpp"

namespace config {
    static std::string prompt = "$ ";
}

static int process_line(const std::string& line) {
    using namespace pshellscript;
    auto tokens = lexer::scan_tokens(line);
    for (auto& token : tokens) {
        std::cout << token.to_string() << '\n';
    }
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