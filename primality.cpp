/*********************************************************************************
 * Permission is hereby granted, free of charge, to any person obtaining a copy	 *
 * of this software and associated documentation files (the "Software"), to deal  *
 * in the Software without restriction, including without limitation the rights   *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell	 *
 * copies of the Software, and to permit persons to whom the Software is		 *
 * furnished to do so, subject to the following conditions:			 *
 * 										 *
 * The above copyright notice and this permission notice shall be included in	 *
 * all copies or substantial portions of the Software.				 *
 * 										 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,	 *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE	 *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	 *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN	 *	
 * THE SOFTWARE.									 *
 **********************************************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <gmp.h>
#include <gmpxx.h>
#include <mpfr.h>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include <iomanip>
#include "common.hpp"

using namespace std;


bool isPrime(char* nn) {
	int l = strlen(nn);
	if (l ==1) {
		int nk = atoi(nn);
		if (nk == 2) {
			return true;
		} else if (nk <= 5) {
			if (nk == 3 || nk == 5) {
				return true;
			}
		}
	}
	mpz_t nt;
	mpz_t nz1;
	mpz_init(nz1);
	mpz_t nz2;
	mpz_init(nz2);
	mpz_t term;
	mpz_init(term);
	mpz_t term2;
	mpz_init(term2);
	mpz_init(nt);
	mpz_set_str(nt, nn, 10);
	mpfr_t nz;
	mpfr_t n1;
	mpfr_init2(n1, 4096);
	mpfr_t n2;
	mpfr_init2(n2, 4096);
	mpfr_init2(nz, 4096);
	mpfr_set_str(nz, nn, 10, MPFR_RNDN);
	mpfr_log2(nz, nz, MPFR_RNDN);
	mpfr_floor(nz, nz);
	mpfr_get_z(nz1, nz, MPFR_RNDN);
	mpz_add_ui(nz1, nz1, 1);
	mpfr_get_z(nz2, nz, MPFR_RNDN);
	mpz_sub_ui(nz2, nz2, 1);
	mpz_mul(nz1, nz1, nz1);
	mpz_mul(nz2, nz2, nz2);
	mpz_sub(nt, nz1, nz2);
	mpz_set_str(term, nn, 10);
	mpz_t constant1;
	mpz_init(constant1);
	mpz_set_str(constant1, "69384", 10);
	mpz_mul(term, term, constant1);
	mpz_add(term, term, nt);
	mpz_sqrt(term2, term);
	mpz_mul(term2, term2, term2);
	mpz_sub(term, term, term2);
	mpz_mod_ui(term, term, 7);
	mpz_clear(nz1);
	mpz_clear(nz2);
	mpz_clear(constant1);
	mpz_clear(nt);
	mpz_clear(term2);
	mpfr_clear(nz);
	mpfr_clear(n1);
	mpfr_clear(n2);
	if (mpz_cmp_ui(term, 3)<0) {
		return false;
	} else {
		return true;
	}
}


#if 0
int main(int, char**) {
	/* Step 1: Reading the Number to be factorized */
	FILE* fp = fopen("./input.txt", "r");
	std::string num = "";
	char n[1024];
	int ret = 0;
	while ((ret=fscanf(fp, "%s", n))!= EOF) {
		num += n;
	}
	cout << "\nNumber read was : \t" << num <<"\n";
	char* nn = strdup((char*) num.c_str());

	int l = strlen(nn);

	bool prime = isPrime(nn);
	if (prime) {
		cout << nn <<"\t is Prime.\n";
	} else {
		cout << nn <<"\t is Composite\n";
	}
	fclose(fp);
	free(nn);
	return 0;
}
#endif
