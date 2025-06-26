#ifndef VM_HPP
#define VM_HPP

#include <map>
#include <set>
#include <string>
#include <variant>
#include "parser.hpp"

namespace pshellscript::vm {
    using namespace parser;

    constexpr auto undefined = nullptr;
    using undefined_t = std::nullptr_t;
    using Value = std::variant<double, std::string, bool, undefined_t>;

    class Registry {
    private:
        std::map<std::string, Value> global_variables;

    public:
        void set_global(const std::string& name, Value value);
        Value get_global(const std::string& name) const;
    };

    int execute_program(std::unique_ptr<ast::StatementListNode> program);
}

#endif