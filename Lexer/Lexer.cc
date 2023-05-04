#include "Lexer.hpp"
#include <regex>
#include <cctype>

enum class Kind;

Lexer::Lexer(std::string filename)
{
    input.open(filename);
}

Lexer::~Lexer()
{
    input.close();
}

char Lexer::peek() 
{
    return input.peek();
}

char Lexer::get() 
{
    char c = input.get();
    
    column_++;
    if(c == '\n') 
    {
        line_++;
        column_ = 0;
    }

    return c;
}

bool Lexer::is_space(char c)
{
    return std::isspace(static_cast<unsigned char>(c));
}

bool Lexer::is_letter(char c)
{
    return std::isalpha(static_cast<unsigned char>(c));
}

bool Lexer::is_number(char c) 
{
    return std::isalnum(static_cast<unsigned char>(c)) && !is_letter(c);
}

Token Lexer::number()
{
    std::string lex;

    bool point_touched = false;

    while (is_number( peek() ) || peek() == '_' || peek() == '.')
    {
        if(peek() == '_') {
            get();
            continue;
        }

        if(peek() == '.') {
            if(!point_touched) {
                lex += get();
            }
            else {
                return Token(Token::Kind::UNEXPECTED_SYMBOL, lex);
            }
            point_touched = true;
        }

        lex += get();
    }
    if(point_touched) {
        return Token(Token::Kind::FLOAT, lex);
    }

    return Token(Token::Kind::INT, lex);
}
Token Lexer::character() 
{
    std::string lex{ get() }; // get ' char

    if(peek() == '\\') {
        lex += get();
        switch (peek()) {
            case 'n':
            case 't':
                lex += get();
                break;

            case 'x':
            case 'e': {
                int h = peek() == 'x' ? 2 : 3;

                lex += get();
                for(int i = 0; i < h; i++) {
                    if(isxdigit(peek())) {
                        lex += get();
                    }
                    else {
                        return Token(Token::Kind::UNEXPECTED_SYMBOL, lex);
                    }
                }
                break;
            }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7': {
                for(int i = 0; i < 3; i++) {
                    if(peek() >= '0' && peek() <= '7') {
                        lex += get();
                    }
                    else {
                        return Token(Token::Kind::UNEXPECTED_SYMBOL, lex);
                    }
                }

                break;
            }
            default: 
                lex += get();
                break;
        }
    }
    else {
        lex += get();   
    }

    if(peek() != '\'') {
        return Token(Token::Kind::UNEXPECTED_SYMBOL, lex);
    }
    lex += get();

    return Token(Token::Kind::CHARACTER, lex);

}

Token Lexer::string()
{
    char string_quote = get();

    std::string lex{string_quote};

    char prev_char = peek();
    
    for (char curr_char = get(); curr_char != string_quote || prev_char == '\\'; curr_char = get())
    {
        if(curr_char == '\xff') {
            return Token(Token::Kind::UNEXPECTED_SYMBOL, lex);
        }

        lex += curr_char;
        prev_char = curr_char;
    }

    lex += string_quote;

    return Token(Token::Kind::STRING, lex);
}

Token Lexer::left_paren_or_comment() {
    std::string lex{ get() };

    if(peek() == '*') {
        int nested_comment = 1;

        char prev_char = peek();
        for(char curr_char = get(); nested_comment > 0; curr_char = get()) {
            if(prev_char == '(' && curr_char == '*') nested_comment++;
            if(prev_char == '*' && curr_char == ')') nested_comment--;

            if(curr_char == '\xff') {
                return Token(Token::Kind::UNEXPECTED_SYMBOL, lex);
            }

            lex += curr_char;
            prev_char = curr_char;
        }

        return Token(Token::Kind::COMMENT, lex);
    }
    else {
        return Token(Token::Kind::LEFT_PAREN, lex);
    }
}

Token Lexer::identifier() 
{
    std::string lex;

    for(char c = peek(); is_number(c) || is_letter(c) || c == '_' || c == '\''; c = peek() )
    {
        lex += get();
    } 

    return Token(Token::Kind::IDENTIFIER, lex);
}
// template <typename TK>
Token Lexer::token_if_next(char c, const Token::Kind &k1, const Token::Kind &k2) 
{
    std::string lex{ get() };

    if(peek() == c) 
    {
        lex += get();
        return Token(k1, lex);
    }
    else
    {
        return Token(k2, lex);
    }
}

Token Lexer::next()
{
    while (is_space( peek() )) get();

    char c = peek();

    if (is_number(c)) 
    {
        return number();
    }
    else if (is_letter(c) || c == '_')
    {
        return identifier();
    }

    switch (c) {
        case '\xff':
            return Token(Token::Kind::END, std::string{ get() }); 
        case '\'':
            return character();
        case '\"':
            return string();
        case ';':
            return token_if_next(';', Token::Kind::DOUBLE_SEMICOLON, Token::Kind::SEMICOLON);
        case '(':
            return left_paren_or_comment();
        case '-':
            return token_if_next('>', Token::Kind::ARROW, Token::Kind::MINUS);
        case '|': // | or ||
            return token_if_next('|', Token::Kind::OR, Token::Kind::PIPE);
        case '&': // & or &&
            return token_if_next('&', Token::Kind::AND, Token::Kind::UNEXPECTED_TOKEN);
        case '=': // = or ==
            return token_if_next('=', Token::Kind::DOUBLE_EQUAL, Token::Kind::EQUAL);
        case ')':
            return Token(Token::Kind::RIGHT_PAREN, std::string{ get() });
        case '[':
            return Token(Token::Kind::LEFT_SQUARE, std::string{ get() });
        case ']':
            return Token(Token::Kind::RIGHT_SQUARE, std::string{ get() });
        case '{':
            return Token(Token::Kind::LEFT_CURLY, std::string{ get() });
        case '}':
            return Token(Token::Kind::RIGHT_CURLY, std::string{ get() });
        case '<':
            return Token(Token::Kind::LESS_THEN, std::string{ get() });
        case '>':
            return Token(Token::Kind::GREATER_THEN, std::string{ get() });
        case '!': //!=
            return Token(Token::Kind::NOT_EQUAL, std::string{ get() });
        case '+':
            return Token(Token::Kind::PLUS, std::string{ get() });
        case '*':
            return Token(Token::Kind::ASTERISK, std::string{ get() });
        case '/':
            return Token(Token::Kind::SLASH, std::string{ get() });
        case '%':
            return Token(Token::Kind::PERCENT, std::string{ get() });
        case '#':
            return Token(Token::Kind::HASH, std::string{ get() });
        case '.':
            return Token(Token::Kind::DOT, std::string{ get() });
        case ',':
            return Token(Token::Kind::COMMA, std::string{ get() });
        case ':':
            return Token(Token::Kind::COLON, std::string{ get() });
        case '~':
            return Token(Token::Kind::TILDE, std::string{ get() });
        case '^':
            return Token(Token::Kind::CARET, std::string{ get() });
        default:
            return Token(Token::Kind::UNEXPECTED_SYMBOL, std::string{ get() });
    } 

    return Token(Token::Kind::END, std::string{ get() });
}