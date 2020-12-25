#include "../../../gmp-6.1.2/gmp.h"
#include <iostream>
int main(int argc, char **argv) 
{
	mpf_set_default_prec(10);
	mpz_t n, t;
	mpz_init(n);
	mpz_init(t);
	mpz_set_str(n, "22342342342346352234432234234234234234324234234234234234234123123", 10);
	mpz_set_ui(t, 123123);
	mpz_add_ui(n, n, 1);
	mpz_out_str(stdout, 10, n);
	std::cout<<'\n'<<std::endl;
	mpz_mul(n, n, n);
	mpz_divexact_ui(n,t,5);
	mpf_t x, y;
	mpf_init(y);
	mpf_set_str(x, "3.14", 10);
	mpf_set_str(y, "133.2315", 10);
	mpf_out_str(stdout, 10, 11,  y);
	char * temp = new char[1025];
	mp_exp_t exp;
	mpf_get_str(temp, &exp, 10, 10, y);
	for(int i = 0; i < 10; i++){
		std::cout<<temp[i]<<std::endl;
	}
	std::cout<<exp<<std::endl;

}

