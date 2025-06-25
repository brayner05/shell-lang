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
    return 0;
}


int main() {
    using namespace pshellscript::parser;
    std::string path = std::getenv("PATH");

    auto l1 = std::make_unique<ast::NumberNode>(2.0);
    auto r1 = std::make_unique<ast::NumberNode>(3.0);
    auto r2 = std::make_unique<ast::NumberNode>(1.0);
    auto l2 = std::make_unique<ast::SubtractionNode>(
        std::move(l1),
        std::move(r1)
    );
    auto expr = std::make_unique<ast::AdditionNode>(
        std::move(l2),
        std::move(r2)
    );
    std::cout << expr->to_string() << '\n';
    exit(0);

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