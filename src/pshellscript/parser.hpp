#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <memory>
#include <vector>
#include "../result.hpp"
#include "tokens.hpp"


namespace pshellscript::parser::ast {
    enum class NodeType {
        StatementList,

        Number, String, Boolean, Variable,
        Identifier,

        ForLoop, IfStatement, ElseClause,
        FunctionDefinition,
        EchoStatement, ReturnStatement,

        AndExpression, OrExpression, EqualityExpression,
        ComparisonExpression, AddExpression, SubtractExpression,
        MultiplyExpression, DivideExpression, ModuloExpression,
        LogicalNegationExpression, ArithmeticNegationExpression,
        FunctionCall, ParamList, ArgList,
        LessExpression, LessEqualExpression, 
        GreaterExpression, GreaterEqualExpression,
        PlusEqualExpression, MinusEqualExpression,
        TimesEqualExpression, DivideEqualExpression,
        ModuloEqualExpression,
        InequalityExpression,
        AssignmentExpression
    };


    // Base struct for AST nodes.
    struct BaseNode {
        const NodeType type;
        virtual std::string to_string() const = 0;
    protected:
        inline BaseNode(NodeType type) : type(type) {}
    };


    struct StatementListNode : public BaseNode {
        std::vector<std::unique_ptr<BaseNode>> statements;

        inline StatementListNode(std::vector<std::unique_ptr<BaseNode>>&& statements)
            : BaseNode(NodeType::StatementList), statements(std::move(statements)) {}

        std::string to_string() const override;
    };


    struct NumberNode : public BaseNode {
        double value;

        inline NumberNode(double value)
            : BaseNode(NodeType::Number), value(value) {}
        
        std::string to_string() const override;
    };


    struct StringNode : public BaseNode {
        std::string value;

        inline StringNode(const std::string& value)
            : BaseNode(NodeType::String), value(value) {}

        std::string to_string() const override;
    };


    struct BooleanNode : public BaseNode {
        bool value;

        inline BooleanNode(bool value)
            : BaseNode(NodeType::String), value(value) {}

        std::string to_string() const override;
    };


    struct VariableNode : public BaseNode {
        std::string name;

        inline VariableNode(const std::string& name)
            : BaseNode(NodeType::String), name(name) {}

        std::string to_string() const override;
    };


    struct IdentifierNode : public BaseNode {
        std::string name;

        inline IdentifierNode(const std::string& name)
            : BaseNode(NodeType::String), name(name) {}

        std::string to_string() const override;
    };


    struct ForLoopNode : public BaseNode {
        std::unique_ptr<BaseNode> initialization;
        std::unique_ptr<BaseNode> condition;
        std::unique_ptr<BaseNode> update;
        std::unique_ptr<StatementListNode> body;

        inline ForLoopNode(
            std::unique_ptr<BaseNode> initialization,
            std::unique_ptr<BaseNode> condition,
            std::unique_ptr<BaseNode> update,
            std::unique_ptr<StatementListNode> body
        ) : BaseNode(NodeType::ForLoop),
            initialization(std::move(initialization)),
            condition(std::move(condition)),
            update(std::move(update)),
            body(std::move(body)) {}

        std::string to_string() const override;
    };


    struct IfStatementNode : public BaseNode {
        std::unique_ptr<BaseNode> condition;
        std::unique_ptr<StatementListNode> body;
        std::unique_ptr<BaseNode> else_clause;

        inline IfStatementNode(
            std::unique_ptr<BaseNode> condition,
            std::unique_ptr<StatementListNode> body,
            std::unique_ptr<BaseNode> else_clause
        ) : BaseNode(NodeType::IfStatement),
            condition(std::move(condition)),
            body(std::move(body)),
            else_clause(std::move(else_clause)) {}

        std::string to_string() const override;
    };


    struct ParamListNode : public BaseNode {
        std::vector<std::unique_ptr<VariableNode>> parameters;

        inline ParamListNode(
            std::vector<std::unique_ptr<VariableNode>>&& parameters
        ) : BaseNode(NodeType::ParamList), parameters(std::move(parameters)) {}

        std::string to_string() const override;
    };


    struct FunctionDefinitionNode : public BaseNode {
        std::string name;
        std::unique_ptr<ParamListNode> parameters;
        std::unique_ptr<StatementListNode> body;

        inline FunctionDefinitionNode(
            const std::string& name,
            std::unique_ptr<ParamListNode> parameters,
            std::unique_ptr<StatementListNode> body
        ) : BaseNode(NodeType::FunctionDefinition),
            name(name),
            parameters(std::move(parameters)),
            body(std::move(body)) {}

        std::string to_string() const override;
    };


    struct EchoStatementNode : public BaseNode {
        std::unique_ptr<BaseNode> argument;

        inline EchoStatementNode(std::unique_ptr<BaseNode> argument)
            : BaseNode(NodeType::EchoStatement), argument(std::move(argument)) {}

        std::string to_string() const override;
    };


    struct ReturnStatementNode : public BaseNode {
        std::unique_ptr<BaseNode> argument;

        inline ReturnStatementNode(std::unique_ptr<BaseNode> argument)
            : BaseNode(NodeType::EchoStatement), argument(std::move(argument)) {}

        std::string to_string() const override;
    };


    struct BinaryExpressionNode : public BaseNode {
        std::unique_ptr<BaseNode> left_argument;
        std::unique_ptr<BaseNode> right_argument;
        std::string lexeme;

        inline BinaryExpressionNode(
            NodeType type,
            const std::string& lexeme,
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BaseNode(type),
            left_argument(std::move(left_argument)),
            right_argument(std::move(right_argument)),
            lexeme(lexeme) {}
        
        std::string to_string() const override;
    };


    struct AdditionNode : public BinaryExpressionNode {
        inline AdditionNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::AddExpression,
            "+",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct SubtractionNode : public BinaryExpressionNode {
        inline SubtractionNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::SubtractExpression,
            "-",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct MultiplicationNode : public BinaryExpressionNode {
        inline MultiplicationNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::MultiplyExpression,
            "*",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct DivisionNode : public BinaryExpressionNode {
        inline DivisionNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::DivideExpression,
            "/",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct ModuloNode : public BinaryExpressionNode {
        inline ModuloNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::ModuloExpression,
            "%",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct AndNode : public BinaryExpressionNode {
        inline AndNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::AndExpression,
            "&&",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct OrNode : public BinaryExpressionNode {
        inline OrNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::OrExpression,
            "||",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct LessNode : public BinaryExpressionNode {
        inline LessNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::LessExpression,
            "<",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct LessEqualNode : public BinaryExpressionNode {
        inline LessEqualNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::LessEqualExpression,
            "<=",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct GreaterNode : public BinaryExpressionNode {
        inline GreaterNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::GreaterExpression,
            ">",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct GreaterEqualNode : public BinaryExpressionNode {
        inline GreaterEqualNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::GreaterEqualExpression,
            ">=",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct EqualityNode : public BinaryExpressionNode {
        inline EqualityNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::EqualityExpression,
            "==",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct InequalityNode : public BinaryExpressionNode {
        inline InequalityNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::InequalityExpression,
            "!=",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct AssignmentNode : public BinaryExpressionNode {
        inline AssignmentNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BinaryExpressionNode(
            NodeType::AssignmentExpression,
            "=",
            std::move(left_argument),
            std::move(right_argument)
        ) {}
    };


    struct UnaryExpressionNode : public BaseNode {
        std::unique_ptr<BaseNode> argument;
        std::string lexeme;

        inline UnaryExpressionNode(
            NodeType type,
            std::unique_ptr<BaseNode> argument,
            const std::string& lexeme
        ) : BaseNode(type),
            argument(std::move(argument)),
            lexeme(lexeme) {}

        std::string to_string() const override;
    };


    struct NotExpressionNode : public UnaryExpressionNode {
        inline NotExpressionNode(
            std::unique_ptr<BaseNode> argument
        ) : UnaryExpressionNode(
            NodeType::AndExpression, 
            std::move(argument), 
            "!"
        ) {}
    };


    struct NegationExpressionNode : public UnaryExpressionNode {
        inline NegationExpressionNode(
            std::unique_ptr<BaseNode> argument
        ) : UnaryExpressionNode(
            NodeType::ArithmeticNegationExpression, 
            std::move(argument), 
            "-"
        ) {}
    };


    struct ArgListNode : public BaseNode {
        std::vector<std::unique_ptr<BaseNode>> arguments;

        inline ArgListNode(std::vector<std::unique_ptr<BaseNode>>&& arguments)
            : BaseNode(NodeType::ArgList), arguments(std::move(arguments)) {}

        std::string to_string() const override;
    };


    struct FunctionCallNode : public BaseNode {
        std::unique_ptr<IdentifierNode> name;
        std::unique_ptr<ArgListNode> arguments;

        inline FunctionCallNode(
            std::unique_ptr<IdentifierNode> name,
            std::unique_ptr<ArgListNode> arguments
        ) : BaseNode(NodeType::FunctionCall),
            name(std::move(name)),
            arguments(std::move(arguments)) {}

        std::string to_string() const override;
    };
}


namespace pshellscript::parser {
    class Parser {
    private:
        std::vector<Token> token_stream;
        std::vector<Error> errors;
        long token_number = 0;


        inline std::unique_ptr<ast::BaseNode> error(const std::string& message) {
            this->errors.push_back(message);
            return nullptr;
        }
        

        inline Token& next() {
            return this->token_stream[this->token_number++];
        }


        inline bool has_next() {
            return size_t(this->token_number) < this->token_stream.size();
        }


        inline Token::Type peek_type() {
            if (!this->has_next()) {
                return Token::Type::Eof;
            } else {
                auto token = this->token_stream[this->token_number];
                return token.type;
            }
        }


        std::unique_ptr<ast::BaseNode> statement();
        std::unique_ptr<ast::ForLoopNode> for_loop();
        std::unique_ptr<ast::IfStatementNode> if_statement();
        std::unique_ptr<ast::BaseNode> else_clause();
        std::unique_ptr<ast::FunctionDefinitionNode> function_definition();
        std::unique_ptr<ast::ParamListNode> param_list();
        std::unique_ptr<ast::BaseNode> echo_statement();
        std::unique_ptr<ast::BaseNode> return_statement();
        std::unique_ptr<ast::BaseNode> expression();
        std::unique_ptr<ast::BaseNode> assignment();
        std::unique_ptr<ast::BaseNode> disjunction();
        std::unique_ptr<ast::BaseNode> conjunction();
        std::unique_ptr<ast::BaseNode> equality();
        std::unique_ptr<ast::BaseNode> comparison();
        std::unique_ptr<ast::BaseNode> term();
        std::unique_ptr<ast::BaseNode> factor();
        std::unique_ptr<ast::BaseNode> unary();
        std::unique_ptr<ast::BaseNode> primary();
        std::unique_ptr<ast::NumberNode> number();
        std::unique_ptr<ast::StringNode> string();
        std::unique_ptr<ast::VariableNode> variable();
        std::unique_ptr<ast::ArgListNode> arg_list();
        std::unique_ptr<ast::FunctionCallNode> function_call();
        std::unique_ptr<ast::BaseNode> parentheses();
        std::unique_ptr<ast::BooleanNode> boolean();

    public:
        inline Parser(const std::vector<Token>& token_stream)
                : token_stream(token_stream) {}

        std::unique_ptr<ast::StatementListNode> parse();
    };
}


#endif