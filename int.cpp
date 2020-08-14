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

int test1() {
    return 1;
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

string interpreter_string(node* AST) {
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
        return strings[(AST->val).token];
    }

    string leftVal = interpreter_string(AST->left);
    string rightVal = interpreter_string(AST->right);

    if ((AST->val).token == "+") {
        return leftVal + rightVal;
    }
}


cpp_dec_float_50 interpreter_floating(node* AST) {
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
            return interpreter_floating(AST->left);
        }
        else {
            return cpp_dec_float_50(-1) * interpreter_floating(AST->left);
        }
    }
    if ((AST->val).type == "ID") {
        return decimals[(AST->val).token];
    }
    if ((AST->val).token == "=") {
        if ((AST->right->val).type == "NUM") {
            // ENTER ERROR MESSAGE HERE.
        }
        if ((AST->right->val).type == "STRING") {
            strings[(AST->left->val).token] = (AST->right->val).token; // Assignment for strings.
            return -1;
        }
        else {
            decimals[(AST->left->val).token] = interpreter_floating(AST->right);
            return decimals[(AST->left->val).token];
        }
    }

    cpp_dec_float_50 leftVal = interpreter_floating(AST->left);
    cpp_dec_float_50 rightVal = interpreter_floating(AST->right);

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

cpp_int interpreter(node* AST) {
    if ((AST->val).type == "STRING") {
        cerr << "string type cannot be assigned or operated with NUM type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "DECIMAL") {
        cerr << "decimal type cannot be assigned or operated with NUM type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "NUM") {
        return cpp_int((AST->val).token);
    }
    if (AST->unary) {
        if ((AST->val).token == "+") {
            return interpreter(AST->left);
        }
        else {
            return cpp_int(-1) * interpreter(AST->left);
        }
    }
    if ((AST->val).type == "ID") {
        if (numbers.count((AST->val).token) == 0) {
            cerr << "Variable " + (AST->val).token + " was not declared\n" << endl;
            exit(EXIT_FAILURE);
        }
        return numbers[(AST->val).token];
    }
    if ((AST->val).token == "=") {
        string whatType = FindType((AST->left->val).token);
        string varName = FindName((AST->left->val).token);
        if (whatType == "flo") {
            decimals[varName] = interpreter_floating(AST->right);
            return cpp_int(-1);
        }
        if (whatType == "str") {
            strings[varName] = interpreter_string(AST->right); // Assignment for strings.
            return cpp_int(-1);
        }
        else { // Otherwise its a number.
            numbers[varName] = interpreter(AST->right);
            return  numbers[varName];
        }
    }

    cpp_int leftVal = interpreter(AST->left);
    cpp_int rightVal = interpreter(AST->right);

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

void CompoundStatement(vector<vector<node*>> statement_list) {
    cout << (statement_list.size()) << "TEST" << endl;
    for (long long i = 0; i < statement_list[0].size(); i++) {
        interpreter(statement_list[0][i]);
    }
}


