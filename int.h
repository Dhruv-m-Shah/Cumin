#pragma once
#ifndef INTERPRETER_H_INCLUDED
#define INTERPRETER_H_INCLUDED
#include "parser.h"
#include <string>
#include <vector>


class vars {
public:
    std::string name;
    std::string sVal;
    long long val;
};

class outputStr {
public:
    std::vector<mpz_t> integer_output;
    std::vector<std::string> string_output;
    std::vector<mpf_t> float_output;
};

void CompoundStatement(std::vector<functionDetails>);



#endif // INTERPRETER_H_INCLUDED
