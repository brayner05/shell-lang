#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <memory>
#include <vector>

namespace pshellscript::parser {}

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
        FunctionCall,
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

        inline StatementListNode(std::vector<std::unique_ptr<BaseNode>> statements)
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


    struct FunctionDefinitionNode : public BaseNode {
        std::string name;
        std::vector<VariableNode> parameters;
        std::unique_ptr<StatementListNode> body;

        inline FunctionDefinitionNode(
            const std::string& name,
            const std::vector<VariableNode>& parameters,
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


    struct AdditionNode : public BaseNode {
        std::unique_ptr<BaseNode> left_argument;
        std::unique_ptr<BaseNode> right_argument;

        inline AdditionNode(
            std::unique_ptr<BaseNode> left_argument,
            std::unique_ptr<BaseNode> right_argument
        ) : BaseNode(NodeType::AddExpression),
            left_argument(std::move(left_argument)),
            right_argument(std::move(right_argument)) {}
        
        std::string to_string() const override;
    };
}

#endif