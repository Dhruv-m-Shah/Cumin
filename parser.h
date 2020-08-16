#pragma once
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <map>
#include "lexer.h"
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_dec_float_50;

struct node {
    bool unary;
    node* left;
    node* right;
    TOKEN val;
};
struct functionDetails {
    std::vector<node*> statements;
    std::map<std::string, cpp_int> numbers;
    std::map<std::string, std::string> strings;
    std::map<std::string, cpp_dec_float_50> decimals;
};

std::vector<functionDetails> program(std::vector<TOKEN>tokened, std::vector<functionDetails> functions);

#endif // PARSER_H_INCLUDED
