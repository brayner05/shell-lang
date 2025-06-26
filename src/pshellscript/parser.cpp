#include <sstream>
#include "parser.hpp"

namespace pshellscript::parser::ast {
    std::string NumberNode::to_string() const {
        std::stringstream stream;
        stream <<this->value;
        return stream.str();
    }


    std::string StringNode::to_string() const {
        std::stringstream stream;
        stream << "\"" << this->value << "\"";
        return stream.str();
    }


    std::string BooleanNode::to_string() const {
        std::stringstream stream;
        stream << (this->value ? "true" : "false");
        return stream.str();
    }


    std::string VariableNode::to_string() const {
        std::stringstream stream;
        stream << "$" << this->name;
        return stream.str();
    }


    std::string IdentifierNode::to_string() const {
        std::stringstream stream;
        stream << this->name;
        return stream.str();
    }


    std::string StatementListNode::to_string() const {
        std::stringstream stream;

        stream << '(';
        for (const auto& statement : this->statements) {
            stream << statement->to_string() << ' ';
        }
        stream << ')';

        return stream.str();
    }


    std::string ForLoopNode::to_string() const {
        std::stringstream stream;

        stream 
            << "(for [" 
            << this->initialization->to_string()
            << ','
            << this->condition->to_string()
            << ','
            << this->update->to_string()
            << ']'
            << this->body->to_string()
            << ')';

        return stream.str();
    }


    std::string IfStatementNode::to_string() const {
        std::stringstream stream;

        stream
            << "(if "
            << "["
            << this->condition->to_string()
            << "]"
            << this->body->to_string()
            << ")";

        return stream.str();
    }


    std::string ParamListNode::to_string() const {
        std::stringstream stream;

        for (const auto& param : this->parameters) {
            stream << param->name << ", ";
        }

        return stream.str();
    }


    std::string FunctionDefinitionNode::to_string() const {
        std::stringstream stream;

        stream 
            << "(function [" 
            << this->parameters->to_string()
            << "]"
            << this->body->to_string() 
            << ")";

        return stream.str();
    }


    std::string EchoStatementNode::to_string() const {
        return (
            std::stringstream() 
            << "(echo " 
            << this->argument->to_string() 
            << ")"
        ).str();
    }


    std::string ReturnStatementNode::to_string() const {
        return (
            std::stringstream() 
            << "(return " 
            << this->argument->to_string() 
            << ")"
        ).str();
    }


    std::string BinaryExpressionNode::to_string() const {
        std::stringstream stream;

        stream
            << "("
            << this->lexeme
            << ' '
            << this->left_argument->to_string()
            << " "
            << this->right_argument->to_string()
            << ")";

        return stream.str();
    }


    std::string UnaryExpressionNode::to_string() const {
        std::stringstream stream;

        stream
            << "("
            << this->lexeme
            << ' '
            << this->argument->to_string()
            << ")";

        return stream.str();
    }
}

namespace pshellscript::parser {
    std::vector<std::unique_ptr<ast::BaseNode>> Parser::parse() {
        std::vector<std::unique_ptr<ast::BaseNode>> program;

        while (this->has_next()) {
            auto statement = this->statement();
            program.push_back(std::move(statement));
        }

        return program;
    }


    inline static bool is_factor_operation(Token::Type type) {
        return (
            type == Token::Type::Asterisk ||
            type == Token::Type::Slash ||
            type == Token::Type::Modulo
        );
    }


    inline static bool is_term_operation(Token::Type type) {
        return (
            type == Token::Type::Plus ||
            type == Token::Type::Minus
        );
    }


    inline static bool is_comparison_operation(Token::Type type) {
        return (
            type == Token::Type::Less ||
            type == Token::Type::LessEqual ||
            type == Token::Type::Greater ||
            type == Token::Type::GreaterEqual
        );
    }


    inline static bool is_equality_operation(Token::Type type) {
        return (
            type == Token::Type::EqualEqual ||
            type == Token::Type::BangEqual
        );
    }


    static std::unique_ptr<ast::BaseNode> create_operator_node(
        Token::Type operation, 
        std::unique_ptr<ast::BaseNode> left_side,
        std::unique_ptr<ast::BaseNode> right_side
    ) {
        using Type = Token::Type;
        switch (operation) {
            case Type::Asterisk: {
                return std::make_unique<ast::MultiplicationNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::Slash: {
                return std::make_unique<ast::DivisionNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
                break;
            }

            case Type::Modulo: {
                return std::make_unique<ast::ModuloNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::Plus: {
                return std::make_unique<ast::AdditionNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::Minus: {
                return std::make_unique<ast::SubtractionNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::Less: {
                return std::make_unique<ast::LessNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::LessEqual: {
                return std::make_unique<ast::LessEqualNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::Greater: {
                return std::make_unique<ast::GreaterNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::GreaterEqual: {
                return std::make_unique<ast::GreaterEqualNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::EqualEqual: {
                return std::make_unique<ast::EqualityNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::BangEqual: {
                return std::make_unique<ast::InequalityNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            case Type::Equal: {
                return std::make_unique<ast::AssignmentNode>(
                    std::move(left_side), 
                    std::move(right_side)
                );
            }

            default: {
                return nullptr;
            }
        }
    }

    std::unique_ptr<ast::BaseNode> Parser::expression() {
        return this->assignment();
    }

    std::unique_ptr<ast::BaseNode> Parser::return_statement() {
        this->next();
        auto operand = this->expression();
        return std::make_unique<ast::ReturnStatementNode>(std::move(operand));
    }


    std::unique_ptr<ast::BaseNode> Parser::echo_statement() {
        this->next();
        auto operand = this->expression();
        return std::make_unique<ast::EchoStatementNode>(std::move(operand));
    }


    std::unique_ptr<ast::BaseNode> Parser::assignment() {
        std::unique_ptr<ast::BaseNode> left_side = this->variable();
        while (this->has_next() && this->peek_type() == Token::Type::Equal) {
            auto operation = this->next();
            auto right_side = this->disjunction();

            left_side = create_operator_node(
                operation.type, 
                std::move(left_side), 
                std::move(right_side)
            );
        }

        return left_side;
    }


    std::unique_ptr<ast::BaseNode> Parser::disjunction() {
        auto left_side = this->conjunction();
        while (this->has_next() && this->peek_type() == Token::Type::OrOr) {
            auto operation = this->next();
            auto right_side = this->conjunction();

            left_side = create_operator_node(
                operation.type, 
                std::move(left_side), 
                std::move(right_side)
            );
        }

        return left_side;
    }


    std::unique_ptr<ast::BaseNode> Parser::conjunction() {
        auto left_side = this->equality();
        while (this->has_next() && this->peek_type() == Token::Type::AndAnd) {
            auto operation = this->next();
            auto right_side = this->equality();

            left_side = create_operator_node(
                operation.type, 
                std::move(left_side), 
                std::move(right_side)
            );
        }

        return left_side;
    }


    std::unique_ptr<ast::BaseNode> Parser::equality() {
        auto left_side = this->comparison();
        while (this->has_next() && is_equality_operation(this->peek_type())) {
            auto operation = this->next();
            auto right_side = this->comparison();

            left_side = create_operator_node(
                operation.type, 
                std::move(left_side), 
                std::move(right_side)
            );
        }

        return left_side;
    }


    std::unique_ptr<ast::BaseNode> Parser::comparison() {
        auto left_side = this->term();
        while (this->has_next() && is_comparison_operation(this->peek_type())) {
            auto operation = this->next();
            auto right_side = this->term();

            left_side = create_operator_node(
                operation.type, 
                std::move(left_side), 
                std::move(right_side)
            );
        }

        return left_side;
    }


    std::unique_ptr<ast::BaseNode> Parser::term() {
        auto left_side = this->factor();
        while (this->has_next() && is_term_operation(this->peek_type())) {
            auto operation = this->next();
            auto right_side = this->factor();

            left_side = create_operator_node(
                operation.type, 
                std::move(left_side), 
                std::move(right_side)
            );
        }

        return left_side;
    }


    std::unique_ptr<ast::BaseNode> Parser::factor() {
        auto left_side = this->unary();
        while (this->has_next() && is_factor_operation(this->peek_type())) {
            auto operation = this->next();
            auto right_side = this->unary();

            left_side = create_operator_node(
                operation.type, 
                std::move(left_side), 
                std::move(right_side)
            );
        }

        return left_side;
    }


    std::unique_ptr<ast::BaseNode> Parser::unary() {
        using Type = Token::Type;
        auto token_type = this->next().type;

        auto argument = this->primary();
        switch (token_type) {
            case Type::Bang: {
                return std::make_unique<ast::NotExpressionNode>(std::move(argument));
            }

            case Type::Minus: {
                return std::make_unique<ast::NegationExpressionNode>(std::move(argument));
            }

            default: {
                return this->primary();
            }
        }
    }


    std::unique_ptr<ast::BaseNode> Parser::primary() {
        using Type = Token::Type;
        auto token_type = this->peek_type();

        switch (token_type) {
            case Type::True:
            case Type::False: {
                return this->boolean();
            }

            case Type::Number: {
                return this->number();
            }

            case Type::String: {
                return this->string();
            }

            case Type::Variable: {
                return this->variable();
            }

            case Type::Identifier: {
                return this->function_call();
            }

            case Type::LeftParen: {
                return this->parentheses();
            }

            default: {
                // Returns nullptr. For example, if a user calls a function that takes
                // one argument without passing the argument, null gets passed instead.
                return nullptr;
            }
        }
    }


    std::unique_ptr<ast::FunctionCallNode> Parser::function_call() {
        auto name = std::make_unique<ast::IdentifierNode>(
            this->next().lexeme
        );

        auto args = this->arg_list();

        return std::make_unique<ast::FunctionCallNode>(
            std::move(name), 
            std::move(args)
        );
    }



    std::unique_ptr<ast::ArgListNode> Parser::arg_list() {
        std::vector<std::unique_ptr<ast::BaseNode>> arguments;

        // Skip the initial parenthesis.
        this->next();

        while (this->has_next() && this->peek_type() != Token::Type::RightParen) {
            auto argument = this->expression();
            arguments.push_back(std::move(argument));

            // Skip comma separator
            if (this->peek_type() == Token::Type::Comma) {
                this->next();
            }
        }

        return std::make_unique<ast::ArgListNode>(std::move(arguments));
    }


    std::unique_ptr<ast::BaseNode> Parser::parentheses() {
        this->next();
        auto inner_expression = this->expression();
        this->next();
        return inner_expression;
    }


    std::unique_ptr<ast::VariableNode> Parser::variable() {
        auto& token = this->next();
        auto prefixed_name = token.lexeme;
        return std::make_unique<ast::VariableNode>(prefixed_name);
    }


    std::unique_ptr<ast::StringNode> Parser::string() {
        auto& token = this->next();
        auto length = token.lexeme.length();
        auto value = token.lexeme.substr(1, length - 1);
        return std::make_unique<ast::StringNode>(value);
    }


    std::unique_ptr<ast::NumberNode> Parser::number() {
        auto& token = this->next();
        auto numeric_value = std::stod(token.lexeme);
        return std::make_unique<ast::NumberNode>(numeric_value);
    }


    /**
     * Create a boolean terminal node.
     */
    std::unique_ptr<ast::BooleanNode> Parser::boolean() {
        auto& token = this->next();
        if (token.lexeme == "true") {
            return std::make_unique<ast::BooleanNode>(true);
        } else {
            return std::make_unique<ast::BooleanNode>(false);
        }
    }
}