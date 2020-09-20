#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include "int.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
using boost::multiprecision::cpp_int;
using boost::multiprecision::cpp_dec_float_50;
cpp_int i("123456789012345678901234567890");
cpp_int test1123("123123123123");
using namespace std;

std::vector<vars> v;
map<string, cpp_int> numbers;
map<string, string> strings;
map<string, cpp_dec_float_50> decimals;
std::vector<int> test;

void deleteAST(node* AST) {
    if (AST == NULL) {
        return;
    }
    if (AST->left == NULL && AST->right == NULL) {
        delete AST;
        return;
    }
    if (AST->left != NULL) {
        deleteAST(AST->left);
    }
    if (AST->right != NULL) {
        deleteAST(AST->right);
    }
    delete AST;
}

long long ConvertToInt(string integer) {
    long long ans = 0;
    for (int i = 0; i < integer.size(); i++) {
        if (integer[i] == '1') {
            ans += 1 * pow(10, integer.size() - 1 - i);
        }
        if (integer[i] == '2') {
            ans += 2 * pow(10, integer.size() - 1 - i);
        }
        if (integer[i] == '3') {
            ans += 3 * pow(10, integer.size() - 1 - i);
        }
        if (integer[i] == '4') {
            ans += 4 * pow(10, integer.size() - 1 - i);
        }
        if (integer[i] == '5') {
            ans += 5 * pow(10, integer.size() - 1 - i);
        }
        if (integer[i] == '6') {
            ans += 6 * pow(10, integer.size() - 1 - i);
        }
        if (integer[i] == '7') {
            ans += 7 * pow(10, integer.size() - 1 - i);
        }
        if (integer[i] == '8') {
            ans += 8 * pow(10, integer.size() - 1 - i);
        }
        if (integer[i] == '9') {
            ans += 9 * pow(10, integer.size() - 1 - i);
        }
    }
    return ans;
}


bool varExist(string id) {
    if (numbers.count(id) != 0) {
        return true;
    }
    else if (decimals.count(id) != 0) {
        return true;
    }
    else if (strings.count(id) != 0) {
        return true;
    }
    return false;
}

string FindType(string id) {
    if (numbers.count(id) != 0) {
        return "num";
    }
    else if (decimals.count(id) != 0) {
        return "flo";
    }
    else if (strings.count(id) != 0) {
        return "strings";
    }
    string temp = id.substr(0, 3);
    if (temp != "flo" && temp != "str" && temp != "num") {
        cerr << "Variable " + id + " was not declared\n" << endl;
        exit(EXIT_FAILURE);
    }

    return temp;
}

string FindName(string id) {
    if (id.size() < 3) {
        if (!varExist(id)) {
            cerr << "Variable " + id + " was not declared\n" << endl;
            exit(EXIT_FAILURE);
        }
        return id;
    }
    string possibleName = id.substr(0, 3);
    if (possibleName == "flo" || possibleName == "str" || possibleName == "num") {
        return id.substr(3, id.size());
    }
    else {
        if (!varExist(id)) {
            cerr << "Variable " + id + " was not declared\n" << endl;
            exit(EXIT_FAILURE);
        }
        return id;
    }
}

string interpreter_string(node* AST, functionDetails *statements) {
    if ((AST->val).type == "DECIMAL") {
        cerr << "DECIMAL type cannot be assigned or operated with STRING type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "NUM") {
        cerr << "NUM type cannot be assigned or operated with STRING type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "STRING") {
        return (AST->val).token;
    }
    if ((AST->val).type == "ID") {
        return statements->strings[(AST->val).token];
    }

    string leftVal = interpreter_string(AST->left, statements);
    string rightVal = interpreter_string(AST->right, statements);

    if ((AST->val).token == "+") {
        return leftVal + rightVal;
    }
}


cpp_dec_float_50 interpreter_floating(node* AST, functionDetails *statements) {
    if ((AST->val).type == "STRING") {
        cerr << "STRING type cannot be assigned or operated with DECIMAL type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "NUM") {
        cerr << "NUM type cannot be assigned or operated with DECIMAL type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "DECIMAL") {
        return cpp_dec_float_50((AST->val).token);
    }
    if (AST->unary) {
        if ((AST->val).token == "+") {
            return interpreter_floating(AST->left, statements);
        }
        else {
            return cpp_dec_float_50(-1) * interpreter_floating(AST->left, statements);
        }
    }
    if ((AST->val).type == "ID") {
        return statements->decimals[(AST->val).token];
    }
    if ((AST->val).token == "=") {
        if ((AST->right->val).type == "NUM") {
            // ENTER ERROR MESSAGE HERE.
        }
        if ((AST->right->val).type == "STRING") {
            statements->strings[(AST->left->val).token] = (AST->right->val).token; // Assignment for strings.
            return -1;
        }
        else {
            statements->decimals[(AST->left->val).token] = interpreter_floating(AST->right, statements);
            return  statements->decimals[(AST->left->val).token];
        }
    }

    cpp_dec_float_50 leftVal = interpreter_floating(AST->left, statements);
    cpp_dec_float_50 rightVal = interpreter_floating(AST->right, statements);

    if ((AST->val).token == "+") {
        return leftVal + rightVal;
    }
    if ((AST->val).token == "-") {
        return leftVal - rightVal;
    }
    if ((AST->val).token == "*") {
        return leftVal * rightVal;
    }
    if ((AST->val).token == "/") {
        return leftVal / rightVal;
    }
}

cpp_int interpreter(node* AST, functionDetails *statements) {
    if ((AST->val).type == "STRING") {
        cerr << "string type cannot be assigned or operated with NUM type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "DECIMAL") {
        cerr << "decimal type cannot be assigned or operated with NUM type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "PRINT") {
        auto toPrint = interpreter(AST->right, statements);
        cout << toPrint << endl; // cout here for testing purposes, there needs to be a cout stream, to store outputs.
        return cpp_int(-1); // Return nothing, invalid value.
    }
    if ((AST->val).type == "NUM") {
        return cpp_int((AST->val).token);
    }
    if (AST->unary) {
        if ((AST->val).token == "+") {
            return interpreter(AST->left, statements);
        }
        else {
            return cpp_int(-1) * interpreter(AST->left, statements);
        }
    }
    if ((AST->val).type == "ID") {
        if (statements->numbers.count((AST->val).token) == 0) {
            cerr << "Variable " + (AST->val).token + " was not declared\n" << endl;
            exit(EXIT_FAILURE);
        }
        return statements->numbers[(AST->val).token];
    }
    if ((AST->val).token == "=") {
        string whatType = FindType((AST->left->val).token);
        string varName = FindName((AST->left->val).token);
        if (whatType == "flo") {
            statements->decimals[varName] = interpreter_floating(AST->right, statements);
            return cpp_int(-1);
        }
        if (whatType == "str") {
            statements->strings[varName] = interpreter_string(AST->right, statements); // Assignment for strings.
            return cpp_int(-1);
        }
        else { // Otherwise its a number.
            statements->numbers[varName] = interpreter(AST->right, statements);
            return  statements->numbers[varName];
        }
    }

    cpp_int leftVal = interpreter(AST->left, statements);
    cpp_int rightVal = interpreter(AST->right, statements);

    if ((AST->val).token == "+") {
        return leftVal + rightVal;
    }
    if ((AST->val).token == "-") {
        return leftVal - rightVal;
    }
    if ((AST->val).token == "*") {
        return leftVal * rightVal;
    }
    if ((AST->val).token == "/") {
        return leftVal / rightVal;
    }
}

void CompoundStatement(vector<functionDetails> statement_list) {
    cout << "TEST" << endl;
    for (long long j = 0; j < statement_list.size(); j++) {
        for (long long i = 0; i < statement_list[j].statements.size(); i++) {
            interpreter(statement_list[j].statements[i], &statement_list[j]);
        }
    }
    for (long long i = 0; i < statement_list[0].statements.size(); i++) {
        deleteAST(statement_list[0].statements[i]);
    }
    
}
