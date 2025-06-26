#include <iostream>
#include <string>
#include <cstdlib>
#include "pshellscript/lexer.hpp"
#include "pshellscript/tokens.hpp"
#include "pshellscript/parser.hpp"
#include "debug.hpp"

namespace config {
    static std::string prompt = "$ ";
}

static int process_line(const std::string& line) {
    using namespace pshellscript;
    auto tokens = lexer::scan_tokens(line);
    debug::dump_tokens(tokens);
    auto parser = parser::Parser(tokens);
    auto program = parser.parse();
    std::cout << program->to_string() << "\n";
    return 0;
}


int main() {
    using namespace pshellscript::parser;
    std::string path = std::getenv("PATH");
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