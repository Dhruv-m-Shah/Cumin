#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "int.h"


using namespace std;
#define ARRAY_COUNT(x) (sizeof(x)/sizeof((x)[0]))


char DIGITS[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
string operators[12] = { "-", "+", "*", "/", ">>", "<<", "%", "^", "<", ">" };
string KEYWORDS[2] = { "start", "end" };
string TYPES[3] = { "num", "flo", "str" };
string STANDARD_VARIABLE_CHARS[54] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "A", "B", "C" , "D", "E" , "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "_", "-" };

void DisplayToken(vector<TOKEN> tokened) {
    for (int i = 0; i < tokened.size(); i++) {
        if (i == tokened.size() - 1) {
            cout << "[" + tokened[i].type + "," + tokened[i].token + "]";
            break;
        }
        cout << "[" + tokened[i].type + "," + tokened[i].token + "],";
    }

}

bool IsStandard(string character) {
    for (int i = 0; i < ARRAY_COUNT(STANDARD_VARIABLE_CHARS); i++) {
        if (character.compare(STANDARD_VARIABLE_CHARS[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool IsDigit(char digit) {
    for (int i = 0; i < 10; i++) {
        if (digit == DIGITS[i]) {
            return true;
        }
    }
    return false;
}

bool IsOperator(string ops) {
    for (int i = 0; i < ARRAY_COUNT(operators); i++) {
        if (ops.compare(operators[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool IsSpecial(string special) {
    for (int i = 0; i < ARRAY_COUNT(KEYWORDS); i++) {
        if (special.compare(KEYWORDS[i]) == 0) {
            return true;
        }
    }
    return false;
}


bool IsAssignment(string assignment) {
    return assignment == "=";
}

bool IsBracket(string bracket) {
    return (bracket == "(" || bracket == ")");
}

bool IsEnd(string ended) {
    return ended == "?";
}

bool IsDecimal(char decimal) {
    return decimal == '.';
}

bool IsFunction(string func) {
    return func == "function";
}

bool IsStartStatement(string start) {
    return start == "start";
}

bool IsEndStatement(string endstatement) {
    return endstatement == "end";
}

string RemoveWhitespace(string input, long long length) {
    string newString = "";
    int quotationDetector = 0;

    for (long long i = 0; i < length; i++) {
        if (input[i] == '"') {
            quotationDetector = (quotationDetector + 1) % 2;
        }
        if (quotationDetector == 0) {
            if (input[i] == ' ') {
                continue;
            }
            else {
                newString = newString + (input[i] + string());
            }
        }
        else {
            newString = newString + (input[i] + string());
        }
    }
    return newString;
}

void tokenize(string input, vector<TOKEN> tokened, outputStr *output_stream1) {
    string scope = "GLOBAL"; // Inital scope is set globally.
    map<string, long long> functionMapper;
    long long functionCount = 0;
    input = RemoveWhitespace(input, input.length());
    int index = 0;
    while (index < input.size()) {
        DisplayToken(tokened);
        string s(1, input[index]);
        if (IsEnd(s)) { // End of a statement
            TOKEN ended = { "END", "?" };
            index++;
            tokened.push_back(ended);
        }
        else if (IsDigit(input[index])) {
            TOKEN digit = { "NUM", s };
            index++;
            while (index < input.size() && (IsDigit(input[index]) || IsDecimal(input[index]))) {
                if (input[index] == '.') { // A floating number
                    digit.type = "DECIMAL";
                    digit.token += input[index];
                    index++;
                    continue;
                }
                digit.token += input[index];
                index++;
            }
            tokened.push_back(digit);
        }
        else if (IsOperator(s)) { // Operators
            TOKEN ops = { "OPERATOR", s };

            while (index < input.size() && IsOperator(s)) {
                ops.token = input[index];
                if (IsOperator(s)) {
                    tokened.push_back(ops);
                }
                index++;
                s = string() + input[index];
            }
            continue;
        }
        else if (IsBracket(s)) { // () <- round brackets
            TOKEN ops = { "ROUND_BRACKET", s };
            index++;
            tokened.push_back(ops);
        }
        else if (IsAssignment(s)) { // Equal sign (assignment)
            TOKEN assignment = { "ASSIGN", s };
            index++;
            tokened.push_back(assignment);
        }
        else if (s == "\"") { // Strings
            TOKEN stringInput = { "STRING", "" };
            index++;
            s = string() + input[index];
            while (index < input.size() && s != "\"") {
                stringInput.token += s;
                index++;
                s = string() + input[index];
            }
            tokened.push_back(stringInput);
            index++;
        }
        else if (s == "[") {
            while (index < input.size() && (string() + input[index]) != "]") {
                index++;
            }
            index++;
        }
        else { // Is a reserved keyword or ID variable.
            TOKEN special = { "SPECIAL", s };
            while (index < input.size()) {
                if (special.token == "print") {
                    tokened.push_back({ "PRINT", special.token });
                    index++;
                    break;
                }
                if (IsFunction(special.token)) {
                    tokened.push_back({ "FUNCTION", special.token });
                    index++;
                    break;
                }
                if (IsStartStatement(special.token)) {
                    if (index - 3 >= 0 && tokened.size() >= 3 && tokened[tokened.size() - 3].type == "FUNCTIONNAME") {
                        scope = tokened[tokened.size() - 3].token;
                    }
                    tokened.push_back({ "START", special.token });
                    index++;
                    break;
                }
                if (IsEndStatement(special.token)) {
                    tokened.push_back({ "ENDSTATEMENT", special.token });
                    scope = "GLOBAL";
                    index++;
                    break;
                }
                if (IsSpecial(special.token)) {
                    tokened.push_back(special);
                    index++;
                    break;
                }
                if (IsBracket(s)) { // () <- round brackets
                    if (s == "(") {
                        if (tokened[tokened.size() - 1].token == "function") {
                            tokened.push_back({ "FUNCTIONNAME", special.token });
                            functionMapper[special.token] = functionCount;
                            functionCount++;
                        }
                    }
                    TOKEN ops = { "ROUND_BRACKET", s };
                    index++;
                    tokened.push_back(ops);
                    break;
                }
                if (!IsStandard(string() + input[index + 1])) {
                    if (tokened[tokened.size() - 1].token == "function") {
                        tokened.push_back({ "FUNCTIONNAME", special.token });
                        index++;
                    }
                    else {
                        tokened.push_back({ "ID", special.token, scope});
                        index++;
                    }
                    break;
                }
                if (index + 1 < input.size() && (IsOperator(string() + input[index + 1]) || IsEnd(string() + input[index + 1]))) {
                    tokened.push_back({ "ID", special.token, scope});
                    index++;
                    break;
                }

                if (index + 1 < input.size() && IsAssignment(string() + input[index + 1])) {
                    tokened.push_back({ "ID", special.token, scope });
                    tokened.push_back({ "ASSIGN", string() + input[index + 1] });
                    index += 2;
                    break;
                }
                index++;
                s = string() + input[index];
                special.token += s;
            }
        }
    }
    DisplayToken(tokened);
    // Sample Program
    // start
    //  x = 2.
    // end
    vector<functionDetails> functions;
    CompoundStatement(program(tokened, functions), output_stream1);
}

