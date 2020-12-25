
#include "lexer.h";
#include "main.h";
#include<iostream>;
#include <cstring>;

using namespace std;
outputStr* output_stream1 = new outputStr;		
int main(){
	string test = "start print(2)? end";
	vector<TOKEN> temp;
	tokenize(test, temp, output_stream1);
	std::cout<<output_stream1->string_output[0]<<std::endl;
	delete output_stream1;
}

extern "C"{
	char * interpretorWrapper(char * code){
		outputStr* output_stream1 = new outputStr;
		string str = string(code);
		vector<TOKEN> temp;
		tokenize(str, temp, output_stream1);
		char temp1[output_stream1->string_output.size() + 1];
		strcpy(temp1, output_stream1->string_output[0].c_str());
		delete output_stream1;
		return temp1;
	}
}
