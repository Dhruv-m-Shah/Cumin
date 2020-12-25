#ifndef LEXER_H_INCLUDED
#define LEXER_H_INCLUDED
#include <vector>
#include <iostream>
#include "main.h"

class TOKEN {
public:
    std::string type;  // TYPE OF TOKEN (NUM, OPERATOR, ...)
    std::string token; // The string value of the token ("123", "+", ... etc)
    std::string scope; // What realm does this variable lie in? 
};

void tokenize(std::string input, std::vector<TOKEN> tokened, outputStr * output_stream1);

#endif // LEXER_H_INCLUDED
