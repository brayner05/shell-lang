#include <iostream>
#include <string>
#include <cstdlib>
#include <stack>
#include "pshellscript/lexer.hpp"
#include "pshellscript/tokens.hpp"
#include "pshellscript/parser.hpp"
#include "pshellscript/vm.hpp"
#include "debug.hpp"

namespace config {
    static std::string prompt = "$ ";
}

static int process_line(const std::string& line) {
    using namespace pshellscript;
    int exit_status = 0;
    try {
        auto tokens = lexer::scan_tokens(line);
        auto parser = parser::Parser(tokens);
        auto program = parser.parse();
        exit_status = vm::execute_program(std::move(program));
    } catch (std::runtime_error &error) {
        std::cerr << "\033[31merror\033[0m: " << error.what() << "\n";
        exit_status = 1;
    }

    return exit_status;
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

        auto exit_status = process_line(line);
        std::cout << "Exited with status " << exit_status << ".\n";
    }
}