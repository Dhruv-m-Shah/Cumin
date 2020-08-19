#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include "parser.h"
using namespace std;

#define ARRAY_COUNT(x) (sizeof(x)/sizeof((x)[0]))

long long myindex = 0;

node* expr(vector<TOKEN> tokened);

node* Variable(vector<TOKEN> tokened) {
    node* current = new node();
    current->left = NULL;
    current->right = NULL;
    current->val = tokened[myindex];
    myindex++;
    return current;
}

node* factor(vector<TOKEN> tokened) {
    node* current = new node();
    if (tokened[myindex].token == "+") {
        current->val = tokened[myindex];
        myindex++;
        current->left = factor(tokened);
        current->unary = true;
        return current;
    }
    else if (tokened[myindex].token == "-") {
        current->val = tokened[myindex];
        myindex++;
        current->left = factor(tokened);
        current->unary = true;
        return current;
    }
    else if (tokened[myindex].token == "(") {
        myindex++;
        current = expr(tokened);
        if (tokened[myindex].token == ")") {
            myindex++;
            return current;
        }
    }
    else if (tokened[myindex].type == "ID") {
        return Variable(tokened);
    }
    else {
        current->left = NULL;
        current->right = NULL;
        current->val = tokened[myindex];
        myindex++;
        return current;
    }
}

node* term(vector<TOKEN> tokened) {
    node* current = factor(tokened);
    int marker = 0;
    while (myindex < tokened.size() && (tokened[myindex].token == "*" || tokened[myindex].token == "/")) {
        marker = 1;
        TOKEN temp = tokened[myindex];
        if (tokened[myindex].token == "*") {
            myindex++;
        }
        else {
            myindex++;
        }
        node* newNode = new node();
        newNode->val = temp;
        newNode->right = factor(tokened);
        newNode->left = current;
        current = newNode;
    }

    return current;
}

node* expr(vector<TOKEN> tokened) {
    node* current = new node();
    current = term(tokened);
    int marker = 0;
    while (myindex < tokened.size() && (tokened[myindex].token == "+" || tokened[myindex].token == "-")) {
        marker = 1;
        TOKEN temp = tokened[myindex];
        if (tokened[myindex].token == "+") {
            myindex++;
        }
        else {
            myindex++;
        }
        node* newNode = new node();
        newNode->val = temp;
        newNode->right = term(tokened);
        newNode->left = current;
        current = newNode;
    }
    return current;
}

node* Assignment(vector<TOKEN> tokened) {
    node* current = new node();
    current->left = Variable(tokened);
    current->val = tokened[myindex];
    myindex++;
    if (tokened[myindex].type == "STRING") {
        node* temp = new node();
        temp->val = tokened[myindex];
        temp->right = NULL;
        temp->left = NULL;
        current->right = temp;
    }
    current->right = expr(tokened);
    return current;
}

node* Statement(vector<TOKEN> tokened) {
    node* current = new node();
    if (tokened[myindex].type == "ID") {
        current = Assignment(tokened);
    }
    return current;
}

vector<node*> StatementList(vector<TOKEN> tokened) {
    vector<node*> results;
    if (tokened[myindex].type == "ENDSTATEMENT") {
        myindex++;
        return results;
    }
    node* current = new node();
    current = Statement(tokened);
    results.push_back(current);
    while (myindex < tokened.size() && tokened[myindex].token == "?") {
        myindex++;
        if (tokened[myindex].token == "end") {
            myindex++;
            break;
        }
        results.push_back(Statement(tokened));
    }
    return results;
}

vector<functionDetails> program(vector<TOKEN> tokened, vector<functionDetails> functions) {
    myindex = 0;
    while (myindex < tokened.size()) {
        if (tokened[myindex].token == "function") {
            myindex += 4; // Skip the function name and start
            cout << myindex << " " << "TEST" << endl;
            functionDetails func = {StatementList(tokened)};
            functions.push_back(func);
        }
        if (tokened[myindex].token == "start") {
            myindex++;
            functionDetails func = { StatementList(tokened) };
            functions.push_back(func);
        }
    }
    return functions;
}

