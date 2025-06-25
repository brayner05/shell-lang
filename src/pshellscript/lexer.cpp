#include <map>
#include "lexer.hpp"

#define CREATE_KEYWORD(lexeme, token_type) \
    { (lexeme), (token_type) }

namespace pshellscript::lexer {
    struct LexerState {
        const std::string& source;
        long current_position = 0;
        long start_position = 0;
        std::vector<Result<Token>> tokens;


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
        void scan_keyword();
        void scan_string();
    };


    static std::map<std::string, Token::Type> keywords = {
        CREATE_KEYWORD("function", Token::Type::Function),
        CREATE_KEYWORD("If", Token::Type::If),
        CREATE_KEYWORD("Else", Token::Type::Else),
        CREATE_KEYWORD("For", Token::Type::For),
        CREATE_KEYWORD("return", Token::Type::Return),
        CREATE_KEYWORD("echo", Token::Type::Echo)
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

            case '=': {
                if (this->peek() == '=') {
                    this->append_token(Token::Type::EqualEqual);
                    break;
                }
                this->append_token(Token::Type::Equal);
                break;
            }
            
            case '!': {
                if (this->peek() == '=') {
                    this->append_token(Token::Type::BangEqual);
                    break;
                }
                this->append_token(Token::Type::Bang);
                break;
            }

            case '<': {
                if (this->peek() == '=') {
                    this->append_token(Token::Type::LessEqual);
                    break;
                }
                this->append_token(Token::Type::Less);
                break;
            }

            case '>': {
                if (this->peek() == '=') {
                    this->append_token(Token::Type::GreaterEqual);
                    break;
                }
                this->append_token(Token::Type::GreaterEqual);
                break;
            }

            case '(': {
                this->append_token(Token::Type::LeftParen);
                break;
            }

            case ')': {
                this->append_token(Token::Type::RightParen);
                break;
            }

            case '{': {
                this->append_token(Token::Type::LeftBrace);
                break;
            }

            case '}': {
                this->append_token(Token::Type::RightBrace);
                break;
            }

            case '[': {
                this->append_token(Token::Type::LeftBracket);
                break;
            }

            case ']': {
                this->append_token(Token::Type::RightBracket);
                break;
            }

            case '"': {
                this->scan_string();
                break;
            }

            default: {
                if (std::isdigit(int(character))) {
                    this->scan_number();
                    break;
                }

                if (std::isalpha(int(character))) {
                    this->scan_keyword();
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


    void LexerState::scan_string() {
        while (this->has_next() && this->peek() != '"') {
            this->next();
        }

        if (this->has_next()) {
            this->next();
            this->append_token(Token::Type::String);
            return;
        }

        this->tokens.push_back(Error("Unterminated string"));
    }


    void LexerState::scan_keyword() {
        while (this->has_next() && std::isalpha(int(this->peek()))) {
            this->next();
        }

        auto lexeme_length = this->current_position - this->start_position;
        auto keyword = this->source.substr(this->start_position, lexeme_length);

        if (!keywords.count(keyword)) {
            this->append_token(Token::Type::Identifier);
            return;
        }

        auto keyword_type = keywords[keyword];
        this->append_token(keyword_type);
    }


    std::vector<Result<Token>> scan_tokens(const std::string& source) {
        LexerState state(source);

        while (state.has_next()) {
            state.scan_token();
            state.start_position = state.current_position;
        }

        return state.tokens;
    }

};