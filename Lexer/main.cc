#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
// #include "Token.hpp"
#include "Lexer.hpp"

int main() {
    std::string filename = "./files/input.ml";

    Lexer lex(filename);
    
    for (auto token = lex.next(); !token.is(Token::Kind::END) && !token.is(Token::Kind::UNEXPECTED); token = lex.next())
    {
        std::cout << std::setw(12) <<  token.kind() << "\t| " << token.lexeme() << " |\n";
    }
    std::cout << "line: " << lex.line() << " column: " << lex.column() << std::endl;

    return 0;
}