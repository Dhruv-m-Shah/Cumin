
#include "lexer.h";
#include "main.h";
#include<iostream>;

using namespace std;
				
int main(){
	string test = "start num x=4353452435234523453451*13453245234537245432589? end";
	vector<TOKEN> temp;
	tokenize(test, temp);
}

extern "C"{
	void interpretorWrapper(char * code){
		string str = string(code);
		vector<TOKEN> temp;
		tokenize(str, temp);
	}
}
