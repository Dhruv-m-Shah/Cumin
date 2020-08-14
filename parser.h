#pragma once
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include "lexer.h"
#include <vector>


struct node {
    bool unary;
    node* left;
    node* right;
    TOKEN val;
};

std::vector<std::vector<node*>> program(std::vector<TOKEN>tokened, std::vector<std::vector<node*>> functions);

#endif // PARSER_H_INCLUDED
