
#include "lexer.h";
#include "main.h";
#include<iostream>;

using namespace std;
				
int main(){
	string test = "start int x=1+1? end";
	vector<TOKEN> temp;
	tokenize(test, temp);
}

extern "C"{
	void interpretorWrapper(string code){
		vector<TOKEN> temp;
		tokenize(code, temp);
	}
}
