#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
#include <vector>
#include <iostream>


class TOKEN {
public:
    std::string type;  // TYPE OF TOKEN (NUM, OPERATOR, ...)
    std::string token; // The string value of the token ("123", "+", ... etc)
};

void tokenize(std::string input);

#endif // LEXER_H_INCLUDED
