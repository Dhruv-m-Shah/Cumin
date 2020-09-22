#pragma once
#ifndef INTERPRETER_H_INCLUDED
#define INTERPRETER_H_INCLUDED
#include "parser.h"
#include <string>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>


using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_dec_float_50;

class vars {
public:
    std::string name;
    std::string sVal;
    long long val;
};
class output {
public:
    std::vector<cpp_int> integer_output;
    std::vector<std::string> string_output;
    std::vector<cpp_dec_float_50> float_output;
};
output* output_stream = new output();
void CompoundStatement(std::vector<functionDetails>);



#endif // INTERPRETER_H_INCLUDED
