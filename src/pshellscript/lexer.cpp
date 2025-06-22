#include "lexer.hpp"

namespace pshellscript::lexer {
    struct LexerState {
        const std::string& source;
        long current_position = 0;
        long start_position = 0;
        std::vector<Token> tokens;


        inline LexerState(const std::string& source)
            : source(source), tokens() { }


        inline bool has_next() const {
            return std::size_t(this->current_position) < this->source.length();
        }


        inline char next() {
            return this->source[this->current_position++];
        }


        inline char peek() const {
            return !this->has_next() ? '\0'
                : this->source[this->current_position];
        }


        inline void append_token(Token::Type type) {
            auto lexeme_length = this->current_position - this->start_position;
            auto token = Token(
                type, 
                this->source.substr(this->start_position, lexeme_length)
            );
            this->tokens.push_back(token);
        }


        void scan_token();
        void scan_number();
    };


    void LexerState::scan_token() {
        auto character = this->next();

        switch (character) {
            case '+': {
                this->append_token(Token::Type::Plus);
                break;
            }

            case '-': {
                this->append_token(Token::Type::Minus);
                break;
            }


            case '*': {
                this->append_token(Token::Type::Asterisk);
                break;
            }


            case '/': {
                this->append_token(Token::Type::Slash);
                break;
            }
            

            default: {
                if (std::isdigit(int(character))) {
                    this->scan_number();
                    break;
                }
            }
        }
    }


    void LexerState::scan_number() {
        while (this->has_next() && std::isdigit(this->peek())) {
            this->next();
        }

        if (this->has_next() && this->peek() == '.') {
            this->next();
            while (this->has_next() && std::isdigit(this->peek())) {
                this->next();
            }
        }

        this->append_token(Token::Type::Number);
    }


    std::vector<Token> scan_tokens(const std::string& source) {
        LexerState state(source);

        while (state.has_next()) {
            state.scan_token();
            state.start_position = state.current_position;
        }

        return state.tokens;
    }

};