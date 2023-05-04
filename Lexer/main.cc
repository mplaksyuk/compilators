#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
// #include "Token.hpp"
#include "Lexer.hpp"

int main() {
    std::string filename = "./files/input.ml";

    Lexer lex(filename);
    
    for (auto token = lex.next(); !token.is(Token::Kind::END); token = lex.next())
    {
        if(token.is(Token::Kind::UNEXPECTED)) {
            std::cerr << std::setw(20) <<  token.kind() << "\t| " << token.lexeme() << "<-- ERROR |\n";
            std::cout << "line: " << lex.line() << " column: " << lex.column() << " - " << lex.column() + 1 << std::endl;
            break;
        }
        else {
            std::cout << std::setw(20) <<  token.kind() << "\t| " << token.lexeme() << " |\n";
        }
    }

    return 0;
}