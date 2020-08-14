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
int test1();
void CompoundStatement(std::vector<std::vector<node*>>);



#endif // INTERPRETER_H_INCLUDED
