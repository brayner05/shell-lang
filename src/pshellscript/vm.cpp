#include <exception>
#include <iostream>
#include <algorithm>
#include <memory>
#include <sstream>
#include "vm.hpp"

namespace pshellscript::vm {
    void Registry::set_global(const std::string& name, Value value) {
        this->global_variables[name] = value;
    }


    Value Registry::get_global(const std::string& name) const {
        if (this->global_variables.count(name) == 0) {
            return undefined;
        } else {
            return this->global_variables.at(name);
        }
    }

    static Value execute(const ast::BaseNode& statement);
    static Value add(const ast::AdditionNode& node);
    static Value subtract(const ast::SubtractionNode& node);
    static Value multiply(const ast::MultiplicationNode& node);
    static Value divide(const ast::DivisionNode& node);
    static Value modulo(const ast::ModuloNode& node);
    static Value echo(const ast::EchoStatementNode& node);

    int execute_program(std::unique_ptr<ast::StatementListNode> program) {
        for (const auto& statement : program->statements) {
            auto result = execute(*statement);
        }
        return 0;
    }


    static Value execute(const ast::BaseNode& statement) {
        switch (statement.type) {
            case ast::NodeType::AddExpression: {
                return add(dynamic_cast<const ast::AdditionNode&>(statement));
            }

            case ast::NodeType::SubtractExpression: {
                return subtract(dynamic_cast<const ast::SubtractionNode&>(statement));
            }

            case ast::NodeType::MultiplyExpression: {
                return multiply(dynamic_cast<const ast::MultiplicationNode&>(statement));
            }

            case ast::NodeType::DivideExpression: {
                return divide(dynamic_cast<const ast::DivisionNode&>(statement));
            }

            case ast::NodeType::ModuloExpression: {
                return modulo(dynamic_cast<const ast::ModuloNode&>(statement));
            }

            case ast::NodeType::Number: {
                return Value(dynamic_cast<const ast::NumberNode&>(statement).value);
            }

            case ast::NodeType::EchoStatement: {
                return echo(dynamic_cast<const ast::EchoStatementNode&>(statement));
            }

            default: {
                return undefined;
            }
        }
    }


    static Value echo(const ast::EchoStatementNode& node) {
        auto argument = execute(*node.argument);
        
        if (std::holds_alternative<double>(argument)) {
            std::cout << std::get<double>(argument) << "\n";
            return Value(undefined);
        } 

        if (std::holds_alternative<std::string>(argument)) {
            std::cout << std::get<std::string>(argument) << "\n";
            return Value(undefined);
        }

        if (std::holds_alternative<undefined_t>(argument)) {
            std::cout << "undefined" << "\n";
            return Value(undefined);
        }

        return Value(undefined);
    }


    static Value add(const ast::AdditionNode& node) {
        auto left = execute(*node.left_argument);
        auto right = execute(*node.right_argument);

        if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
            return std::get<double>(left) + std::get<double>(right);
        }
        
        if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right)) {
            return Value(std::get<std::string>(left) + std::get<std::string>(right));
        }

        if (std::holds_alternative<std::string>(left) && std::holds_alternative<double>(right)) {
            std::stringstream stream;
            stream << std::get<std::string>(left) << std::get<double>(right);
            return Value(stream.str());
        }

        throw std::runtime_error("Invalid addition");
    }


    static Value subtract(const ast::SubtractionNode& node) {
        auto left = execute(*node.left_argument);
        auto right = execute(*node.right_argument);

        if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
            return std::get<double>(left) - std::get<double>(right);
        }

        throw std::runtime_error("Invalid subtraction");
    }


    static Value multiply(const ast::MultiplicationNode& node) {
        auto left = execute(*node.left_argument);
        auto right = execute(*node.right_argument);

        if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
            return std::get<double>(left) * std::get<double>(right);
        }

        throw std::runtime_error("Invalid multiplication");
    }


    static Value divide(const ast::DivisionNode& node) {
        auto left = execute(*node.left_argument);
        auto right = execute(*node.right_argument);

        if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
            if (std::get<double>(right) == 0) {
                throw std::runtime_error("DivideByZeroError");
            }
            return std::get<double>(left) / std::get<double>(right);
        }

        throw std::runtime_error("Invalid division");
    }


    static Value modulo(const ast::ModuloNode& node) {
        auto left = execute(*node.left_argument);
        auto right = execute(*node.right_argument);

        if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right)) {
            if (std::get<double>(right) == 0) {
                throw std::runtime_error("DivideByZeroError");
            }
            return double(int(std::get<double>(left)) % int(std::get<double>(right)));
        }

        throw std::runtime_error("Invalid modulo");
    }
}