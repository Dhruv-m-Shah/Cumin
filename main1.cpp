#include "../../../gmp-6.1.2/gmp.h"
#include <iostream>
int main(int argc, char **argv) 
{
	mpf_set_default_prec(10);
	mpz_t n, t;
	mpz_init(n);
	mpz_set_str(n, "22342342342346352234432234234234234234324234234234234234234123123", 10);
	mpz_add_ui(n, n, 1);
	size_t sz = mpz_sizeinbase(n, 10);
	std::cout<<sz<<std::endl;
}

