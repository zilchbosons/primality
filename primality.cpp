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

bool divisors[4] = {2, 3, 5, 7};

bool valid(char* s) {
	mpz_t r ;
	mpz_init(r);
	mpz_set_str(r, s, 10);
	mpz_t rem;
	mpz_init(rem);
	mpz_mod_ui(rem, r, 2);
	if (mpz_cmp_si(rem, 0)==0) return true;
	mpz_mod_ui(rem, r, 3);
	if (mpz_cmp_si(rem, 0)==0) return true;
	mpz_mod_ui(rem, r, 5);
	if (mpz_cmp_si(rem, 0)==0) return true;
	mpz_mod_ui(rem, r, 7);
	mpz_clear(r);
	if (mpz_cmp_si(rem, 0)==0) return true;
	mpz_clear(rem);
	return false;
}

bool isPrimeHelper(char* nn, char* cc) {
	mpz_t nt;
	mpz_init(nt);
	mpz_set_str(nt, nn, 10);
	mpz_mul(nt, nt, nt);
	mpz_t resultant;
	mpz_init(resultant);
	int np = 0;
	for (int i = 0; i < 3; ++i) {
		int ck = cc[i] - '0';
		switch(i) {
			case 0:
				if (ck) {
					mpz_add_ui(resultant, nt, 1); 
				} else {
					if (mpz_cmp_ui(nt, 1)<0) {
						mpz_set_si(resultant, 0);
					} else {
						mpz_sub_ui(resultant, nt, 1);
					} 
				}
				break;
			case 1:
				if (ck) {
					mpz_add_ui(resultant, nt, 9); 
				} else {
					if (mpz_cmp_ui(nt, 9)<0) {
						mpz_set_si(resultant, 0);
					} else {
						mpz_sub_ui(resultant, nt, 9); 
					}
				}
				break;
			case 2:
				if (ck) {
					mpz_add_ui(resultant, nt, 4); 
				} else {
					if (mpz_cmp_ui(nt, 4)<0) {
						mpz_set_si(resultant, 0);
					} else {
						mpz_sub_ui(resultant, nt, 4); 
					}
				}
				break;
			default:
				break;
		}
		if (valid(strdup(mpz_get_str(0, 10, resultant)))) {
			++np;
		}
	}
	mpz_clear(nt);
	mpz_clear(resultant);
	if (np>1) return false;
	else return true;
}

char* dec2bin(int x) {
	std::string str = "";
	while (x > 0) {
		str += boost::lexical_cast<std::string>(x % 10) ;
		x /= 10;
	}
	char* r = reverse_string((char*)str.c_str());
	return r;
}

bool isPrime(char* nn) {
	int np = 0; 
	for (int i = 0; i < 7; ++i)  {
		char* cc = dec2bin(i);
		bool p = isPrimeHelper(nn, cc);
		if (!p) {
			++np;
		} 
	}
	if (np > 4) return false;
	else return true;
}

int main() {
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

