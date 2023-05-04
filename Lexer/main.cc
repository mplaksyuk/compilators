#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include "Lexer.hpp"

std::map<std::string, std::list<Token>>  groups {
    { "NUMERICS",    std::list<Token>{} },
    { "IDENTIFIERS", std::list<Token>() },
    { "KEYWORDS",    std::list<Token>() },
    { "COMMENTS",    std::list<Token>() },
    { "STRINGS",     std::list<Token>() },
    { "CHARACTERS",  std::list<Token>() },
    { "OPERATORS",   std::list<Token>() },
    { "DELIMITERS",  std::list<Token>() },
    { "OTHERS",      std::list<Token>() },
};

std::map<Token::Kind, std::string > tokens_group {
    { Token::Kind::INT,              "NUMERICS" },
    { Token::Kind::FLOAT,            "NUMERICS" },

    { Token::Kind::STRING,           "STRINGS" },

    { Token::Kind::CHARACTER,        "CHARACTERS" },

    { Token::Kind::IDENTIFIER,       "IDENTIFIERS" },

    { Token::Kind::LEFT_PAREN,       "DELIMITERS" },
    { Token::Kind::RIGHT_PAREN,      "DELIMITERS" },
    { Token::Kind::LEFT_SQUARE,      "DELIMITERS" },
    { Token::Kind::RIGHT_SQUARE,     "DELIMITERS" },
    { Token::Kind::LEFT_CURLY,       "DELIMITERS" },
    { Token::Kind::RIGHT_CURLY,      "DELIMITERS" },

    { Token::Kind::LESS_THEN,        "OPERATORS" },
    { Token::Kind::GREATER_THEN,     "OPERATORS" },
    { Token::Kind::EQUAL,            "OPERATORS" },
    { Token::Kind::NOT_EQUAL,        "OPERATORS" },
    { Token::Kind::PLUS,             "OPERATORS" },
    { Token::Kind::MINUS,            "OPERATORS" },
    { Token::Kind::ASTERISK,         "OPERATORS" },
    { Token::Kind::SLASH,            "OPERATORS" },
    { Token::Kind::PERCENT,          "OPERATORS" },
    { Token::Kind::HASH,             "OTHERS" },
    { Token::Kind::DOT,              "DELIMITERS" },
    { Token::Kind::COMMA,            "DELIMITERS" },
    { Token::Kind::COLON,            "DELIMITERS" },
    { Token::Kind::SEMICOLON,        "DELIMITERS" },
    { Token::Kind::DOUBLE_SEMICOLON, "DELIMITERS" },
    { Token::Kind::SINGLE_QUOTE,     "OTHERS" },
    { Token::Kind::DOUBLE_QUOTE,     "OTHERS" },
    { Token::Kind::PIPE,             "DELIMITERS" },
    { Token::Kind::TILDE,            "OTHERS" },
    { Token::Kind::CARET,            "OPERATORS" },
    { Token::Kind::ARROW,            "OPERATORS" },
    { Token::Kind::DOUBLE_EQUAL,     "OPERATORS" },
    { Token::Kind::OR,               "OPERATORS" },
    { Token::Kind::AND,              "OPERATORS" },

    { Token::Kind::COMMENT,          "COMMENTS" },

    { Token::Kind::KW_AND,           "KEYWORDS" },
    { Token::Kind::KW_AS,            "KEYWORDS" },
    { Token::Kind::KW_ASSERT,        "KEYWORDS" },
    { Token::Kind::KW_ASR,           "KEYWORDS" },
    { Token::Kind::KW_BEGIN,         "KEYWORDS" },
    { Token::Kind::KW_CLASS,         "KEYWORDS" },
    { Token::Kind::KW_CONSTRAINT,    "KEYWORDS" },
    { Token::Kind::KW_DO,            "KEYWORDS" },
    { Token::Kind::KW_DONE,          "KEYWORDS" },
    { Token::Kind::KW_DOWNTO,        "KEYWORDS" },
    { Token::Kind::KW_ELSE,          "KEYWORDS" },
    { Token::Kind::KW_END,           "KEYWORDS" },
    { Token::Kind::KW_EXCEPTION,     "KEYWORDS" },
    { Token::Kind::KW_EXTERNAL,      "KEYWORDS" },
    { Token::Kind::KW_FALSE,         "KEYWORDS" },
    { Token::Kind::KW_FOR,           "KEYWORDS" },
    { Token::Kind::KW_FUN,           "KEYWORDS" },
    { Token::Kind::KW_FUNCTION,      "KEYWORDS" },
    { Token::Kind::KW_FUNCTOR,       "KEYWORDS" },
    { Token::Kind::KW_IF,            "KEYWORDS" },
    { Token::Kind::KW_IN,            "KEYWORDS" },
    { Token::Kind::KW_INCLUDE,       "KEYWORDS" },
    { Token::Kind::KW_INHERIT,       "KEYWORDS" },
    { Token::Kind::KW_INITIALIZER,   "KEYWORDS" },
    { Token::Kind::KW_LAZY,          "KEYWORDS" },
    { Token::Kind::KW_LET,           "KEYWORDS" },
    { Token::Kind::KW_MATCH,         "KEYWORDS" },
    { Token::Kind::KW_METHOD,        "KEYWORDS" },
    { Token::Kind::KW_MOD,           "KEYWORDS" },
    { Token::Kind::KW_MODULE,        "KEYWORDS" },
    { Token::Kind::KW_MUTABLE,       "KEYWORDS" },
    { Token::Kind::KW_NEW,           "KEYWORDS" },
    { Token::Kind::KW_NONREC,        "KEYWORDS" },
    { Token::Kind::KW_OBJECT,        "KEYWORDS" },
    { Token::Kind::KW_OF,            "KEYWORDS" },
    { Token::Kind::KW_OPEN,          "KEYWORDS" },
    { Token::Kind::KW_OR,            "KEYWORDS" },
    { Token::Kind::KW_PRIVATE,       "KEYWORDS" },
    { Token::Kind::KW_REC,           "KEYWORDS" },
    { Token::Kind::KW_SIG,           "KEYWORDS" },
    { Token::Kind::KW_STRUCT,        "KEYWORDS" },
    { Token::Kind::KW_THEN,          "KEYWORDS" },
    { Token::Kind::KW_TO,            "KEYWORDS" },
    { Token::Kind::KW_TRUE,          "KEYWORDS" },
    { Token::Kind::KW_TRY,           "KEYWORDS" },
    { Token::Kind::KW_TYPE,          "KEYWORDS" },
    { Token::Kind::KW_VAL,           "KEYWORDS" },
    { Token::Kind::KW_VIRTUAL,       "KEYWORDS" },
    { Token::Kind::KW_WHEN,          "KEYWORDS" },
    { Token::Kind::KW_WHILE,         "KEYWORDS" },
    { Token::Kind::KW_WITH,          "KEYWORDS" },
};

void clear_console()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

void print_groups() 
{
    for (auto groups_iter = groups.begin(); groups_iter != groups.end(); ++groups_iter) {
        std::string group = groups_iter->first;
        std::cout << group << ":\n";

        for(auto group_iter = groups[group].begin(); group_iter != groups[group].end(); ++group_iter) {
            std::cout << std::setw(20) <<  group_iter->kind_toString() << "\t| " << group_iter->lexeme() << " |\n";
        }
    }
}

int main() {
    std::string filename = "./files/input.ml";

    Lexer lex(filename);

    char ans;
    while(ans != 'n' && ans != 'y') {
        std::cout << "Output Tokens group by type? (y/n): ";
        std::cin >> ans;
        clear_console();
    }

    bool groups_printed = false;

    for (auto token = lex.next(); !token.is(Token::Kind::END); token = lex.next())
    {
        if(token.is(Token::Kind::UNEXPECTED_SYMBOL) || token.is(Token::Kind::UNEXPECTED_TOKEN)) {
            if(ans == 'y') {
                groups_printed = true;
                print_groups();
            }

            std::cerr << std::endl << std::setw(20) <<  token.kind_toString() << "\t| " << token.lexeme() << "<-- ERROR |\n";
            std::cout << "line: " << lex.line() << " column: " << lex.column() << " - " << lex.column() + 1 << std::endl;
            break;
        }
        else {
            if(ans == 'y') {
                std::string group = tokens_group[token.kind()];
                groups[group].push_back(token);
            }
            else
                std::cout << std::setw(20) <<  token.kind_toString() << "\t| " << token.lexeme() << " |\n";
        }
    }
    if(ans == 'y' && !groups_printed) {
        print_groups();
    }

    return 0;
}