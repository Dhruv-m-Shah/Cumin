#include "../../../gmp-6.1.2/gmp.h"
#include <iostream>
int main(int argc, char **argv) 
{
	mpf_set_default_prec(10);
	mpz_t n, t;
	mpz_set_str(n, "22342342342346352234432234234234234234324234234234234234234123123", 10);
	mpz_set_ui(t, 123123);
	mpz_add_ui(n, n, 1);
	char * temp1 = new char[1025];
	for(int i = 0; i < 1025; i++) temp1[i] = '!';
	mpz_get_str(temp1, 10, n);
	for(int i = 0; i < 1025; i++){
		if(temp1[i] == '\0') break;
		std::cout<<temp1[i]<<std::endl;
	}
}

