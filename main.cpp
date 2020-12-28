
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
		unsigned long long charArrayLen = 0;
		string seperator = "abhashcumin420ab~~ab~~cumin19065";
		string tempStr = "";
		for(int i = 0; i < output_stream1->string_output.size(); i++){
			charArrayLen += output_stream1->string_output[i].size() + 32;
			tempStr += seperator;
			tempStr += output_stream1->string_output[i];
		}	
		char temp1[charArrayLen];
		for(int i = 0; i < tempStr.size(); i++){
			temp1[i] = tempStr[i];
		}
		temp1[tempStr.size()] = '\0';
		delete output_stream1;
		return temp1;
	}
}
