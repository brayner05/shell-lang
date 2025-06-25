#include <sstream>
#include "parser.hpp"

namespace pshellscript::parser::ast {
    std::string NumberNode::to_string() const {
        std::stringstream stream;
        stream << '(' << this->value << ')';
        return stream.str();
    }


    std::string StringNode::to_string() const {
        std::stringstream stream;
        stream << "(\"" << this->value << "\")";
        return stream.str();
    }


    std::string BooleanNode::to_string() const {
        std::stringstream stream;
        stream << '(' << (this->value ? "true" : "false") << ')';
        return stream.str();
    }


    std::string VariableNode::to_string() const {
        std::stringstream stream;
        stream << "($" << this->name << ")";
        return stream.str();
    }


    std::string IdentifierNode::to_string() const {
        std::stringstream stream;
        stream << '(' << this->name << ')';
        return stream.str();
    }


    std::string StatementListNode::to_string() const {
        std::stringstream stream;

        stream << '(';
        for (const auto& statement : this->statements) {
            stream << statement->to_string() << ',';
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


    std::string FunctionDefinitionNode::to_string() const {
        std::stringstream stream;

        stream << "(function [";
        for (const auto& param : this->parameters) {
            stream << param.to_string() << ',';
        }
        stream << "]";
        stream << this->body->to_string() << ")";

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


    std::string AdditionNode::to_string() const {
        std::stringstream stream;
        
        return stream.str();
    }
}