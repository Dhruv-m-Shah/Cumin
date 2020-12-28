#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include "int.h"
#include "main.h"
#include "lexer.h"
using namespace std;

std::vector<vars> v;
map<string, mpz_t> numbers;
map<string, string> strings;
map<string, mpf_t> decimals;


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

string FindType(string id, functionDetails* statements) {
    if (statements->numbers.count(id) != 0) {
        return "num";
    }
    else if (statements->decimals.count(id) != 0) {
        return "flo";
    }
    else if (statements->strings.count(id) != 0) {
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

gmpWrapper interpreter_floating(node* AST, functionDetails *statements) {
    if ((AST->val).type == "STRING") {
        cerr << "STRING type cannot be assigned or operated with DECIMAL type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "NUM") {
        cerr << "NUM type cannot be assigned or operated with DECIMAL type" << endl;
        exit(EXIT_FAILURE);
    }

    if ((AST->val).type == "DECIMAL") {
	gmpWrapper temp;
	mpf_init(temp.floatingPoint);
	char char_array[(AST->val).token.length() + 1];
	strcpy(char_array, (AST->val).token.c_str());
        mpf_set_str(temp.floatingPoint, char_array, 10);
	return temp;
    }
    if (AST->unary) {
        if ((AST->val).token == "+") {
            return interpreter_floating(AST->left, statements);
        }
        else {
	    gmpWrapper temp;
	    mpf_init(temp.floatingPoint);
	    mpf_set_str(temp.floatingPoint, "-1", 10);
            mpf_mul(temp.floatingPoint, temp.floatingPoint, interpreter_floating(AST->left, statements).floatingPoint);
	    return temp;
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
            gmpWrapper temp;
	    mpf_init(temp.floatingPoint);
	    return temp;
        }
        else {
            statements->decimals[(AST->left->val).token] = interpreter_floating(AST->right, statements);
            return  statements->decimals[(AST->left->val).token];
        }
    }

    gmpWrapper leftVal = interpreter_floating(AST->left, statements);
    gmpWrapper rightVal = interpreter_floating(AST->right, statements);
    gmpWrapper temp;
    mpf_init(temp.floatingPoint);
    if ((AST->val).token == "+") {
        mpf_add(temp.floatingPoint, leftVal.floatingPoint, rightVal.floatingPoint);
    }
    if ((AST->val).token == "-") {
	mpf_sub(temp.floatingPoint, leftVal.floatingPoint, rightVal.floatingPoint);
    }
    if ((AST->val).token == "*") {
	mpf_mul(temp.floatingPoint, leftVal.floatingPoint, rightVal.floatingPoint);
    }
    if ((AST->val).token == "/") {
	mpf_div(temp.floatingPoint, leftVal.floatingPoint, rightVal.floatingPoint);
    }
    return temp;
}


gmpWrapper interpreter(node* AST, functionDetails *statements, outputStr * output_stream1) {
    if ((AST->val).type == "STRING") {
        cerr << "string type cannot be assigned or operated with NUM type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "DECIMAL") {
        cerr << "decimal type cannot be assigned or operated with NUM type" << endl;
        exit(EXIT_FAILURE);
    }
    if ((AST->val).type == "PRINT") {
        if ((AST->right)->val.type == "ID") {
            cout << (AST->right->val).token << endl;
            string whatType = FindType((AST->right->val).token, statements);
            if (whatType == "num") {
                gmpWrapper toPrint = interpreter(AST->right, statements, output_stream1);
		char * temp = new char[1025];
		mpz_get_str(temp, 10, toPrint.integer);
                string str = "";
		for(int i = 0;  i < 1025; i++){
                        if(temp[i] == '\0') break;
                        str = str + temp[i];
                }
                output_stream1->string_output.push_back(str);
		delete[] temp;
            }
            else if (whatType == "flo") {
                gmpWrapper toPrint = interpreter_floating(AST->right, statements);
		char * temp = new char[1025];
		mp_exp_t exp;
		mpf_get_str(temp, &exp, 10, 10, toPrint.floatingPoint);
                string str = "";
		for(int i = 0;  i < 1025; i++){
			if(temp[i] == '\0') break;
			str = str + temp[i];
		}
                output_stream1->string_output.push_back(str);
		delete[] temp;
            }
            else if (whatType == "str") {
                string toPrint = interpreter_string(AST->right, statements);
                output_stream1->string_output.push_back(toPrint);
            }
            else { // Unknown type, throw an error, implement when doing error coding.
            }
        }
        else if ((AST->right)->val.type == "NUM") {
            gmpWrapper toPrint = interpreter(AST->right, statements, output_stream1);
	    char * temp = new char[1025];
            mpz_get_str(temp, 10, toPrint.integer);
            string str = "";
	    for(int i = 0; i < 1025; i++){
	    	if(temp[i] == '\0') break;
		str = str + temp[i];
	    }
            output_stream1->string_output.push_back(str);
	    delete[] temp;
        }
        else if ((AST->right)->val.type == "DECIMAL") {
            gmpWrapper toPrint = interpreter_floating(AST->right, statements);
	    char * temp = new char[1025];
	    mp_exp_t exp;
	    mpf_get_str(temp, &exp, 10, 10, toPrint.floatingPoint);
            string str = "";
	    for(int i = 0; i < 1025; i++){
            	if(temp[i] == '\0') break;
            	str = str + temp[i];
            }
            delete[] temp;
            output_stream1->string_output.push_back(str);
        }
        else if ((AST->right)->val.type == "STRING") {
            string toPrint = interpreter_string(AST->right, statements);
            output_stream1->string_output.push_back(toPrint);
        }
        else { // Unknown type, throw an error, implement when doing error coding.
            
        }
	gmpWrapper n;
	mpz_init(n.integer);
	mpz_set_str(n.integer, "-1", 10);
        return n;
    }
    if ((AST->val).type == "NUM") {
	    gmpWrapper temp;
	    mpz_init(temp.integer);
	    char char_array[(AST->val).token.length() + 1];
	   // strcpy(char_array, (AST->val).token.c_str());
	    for(int i = 0; i < (AST->val).token.length(); i++) char_array[i] = ((AST->val).token[i]);
	    char_array[(AST->val).token.length()] = '\0';
	    mpz_set_str(temp.integer, char_array, 10);
            return temp;
    }
    if (AST->unary) {
        if ((AST->val).token == "+") {
            return interpreter(AST->left, statements, output_stream1);
        }
        else {
	    gmpWrapper temp;
	    mpz_init(temp.integer);
	    mpz_mul_ui(temp.integer, interpreter(AST->left, statements, output_stream1).integer, -1);
            return temp;
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
        string whatType = FindType((AST->left->val).token, statements);
        string varName = FindName((AST->left->val).token);
        if (whatType == "flo") {
            statements->decimals[varName] = interpreter_floating(AST->right, statements);
            gmpWrapper n;
	    mpz_init(n.integer);
            mpz_set_str(n.integer, "-1", 10);
	    return n;
        }
        if (whatType == "str") {
            statements->strings[varName] = interpreter_string(AST->right, statements); // Assignment for strings.
            gmpWrapper n;
	    mpz_init(n.integer);
            mpz_set_str(n.integer, "-1", 10);
            return n; 
        }
        else { // Otherwise its a number.
            statements->numbers[varName] = interpreter(AST->right, statements, output_stream1);
            return  statements->numbers[varName];
        }
    }

    gmpWrapper  leftVal = interpreter(AST->left, statements, output_stream1);
    gmpWrapper rightVal = interpreter(AST->right, statements, output_stream1);
    gmpWrapper temp;
    mpz_init(temp.integer);
    if ((AST->val).token == "+") {
        mpz_add(temp.integer, leftVal.integer, rightVal.integer);
    }
    if ((AST->val).token == "-") {
        mpz_sub(temp.integer, leftVal.integer, rightVal.integer);
    }
    if ((AST->val).token == "*") {
        mpz_mul(temp.integer, leftVal.integer, rightVal.integer);
    }
    if ((AST->val).token == "/") {
        mpz_tdiv_q(temp.integer, leftVal.integer, rightVal.integer);
    }
    return temp;
}

void CompoundStatement(vector<functionDetails> statement_list, outputStr *output_stream1) {
    for (long long j = 0; j < statement_list.size(); j++) {
        for (long long i = 0; i < statement_list[j].statements.size(); i++) {
            interpreter(statement_list[j].statements[i], &statement_list[j], output_stream1);
        }
    }
    for (long long i = 0; i < statement_list[0].statements.size(); i++) {
        deleteAST(statement_list[0].statements[i]);
    }
}
