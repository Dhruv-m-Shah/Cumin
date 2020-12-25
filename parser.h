#pragma once
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <map>
#include "lexer.h"
#include <string>
#include <vector>
#include "../../../gmp-6.1.2/gmp.h"

struct node {
    bool unary;
    node* left;
    node* right;
    TOKEN val;
};
struct gmpWrapper {
	mpz_t integer;
	mpf_t floatingPoint;
};
struct functionDetails {
    std::vector<node*> statements;
    std::map<std::string, gmpWrapper> numbers;
    std::map<std::string, std::string> strings;
    std::map<std::string, gmpWrapper> decimals;
};

std::vector<functionDetails> program(std::vector<TOKEN>tokened, std::vector<functionDetails> functions);

#endif // PARSER_H_INCLUDED
