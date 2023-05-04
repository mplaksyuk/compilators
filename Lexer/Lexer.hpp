#include <fstream>
#include <string>

#include "Token.hpp"

// class Token;

class Lexer {
    public:
        Lexer(std::string);
        ~Lexer();

        Token next();

        char peek();
        char get();

        int line() { return line_; }
        int column() {return column_; }


    private:
        std::fstream input;

        int line_ = 1;
        int column_ = 0;

        bool is_space(char);
        bool is_letter(char);
        bool is_number(char);

        Token number();
        Token character();
        Token string();
        Token left_paren_or_comment();
        Token identifier();

        Token token_if_next(char, const Token::Kind&, const Token::Kind&);
};