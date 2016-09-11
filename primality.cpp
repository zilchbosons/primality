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
using namespace common;


bool isPrime(char* nn) {
	mpz_t nt ;
	mpz_init(nt);
	mpz_t rt;
	mpz_init(rt);
	mpz_t _qt;
	mpz_init(_qt);
	mpz_t qt;
	mpz_init(qt);
	int initial = 7;
	mpz_set_str(nt, nn, 10);
	while (1) {
		mpz_mod_ui(rt, nt, initial);
		mpz_div_ui(qt, nt, initial);
		gmp_printf("\n%Zd\t%Zd\t%d\n",qt, rt, initial);
		mpz_add_ui(_qt, qt, initial);
		if (mpz_cmp_si(rt, 0)==0) {
			mpz_mul_ui(_qt, _qt, 7);
		} else {
			mpz_mul(_qt, _qt, rt);
		}
	if (mpz_cmp_ui(_qt , 100)<0) {
		int zt = mpz_get_ui(_qt);
		if (common::_isPrime(zt) || _riemannExists(zt)) {
			return true;
		} else {
			return false;
		}
	} else {
		gmp_printf("\n%Zd\t%Zd\t%d\n",qt, rt, initial);
		mpz_set(nt, qt);
	}
}
mpz_clear(qt);
mpz_clear(rt);        
mpz_clear(nt); 

}


//#if 0
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

	bool prime = isPrime((char*)nn);
	if (prime) {
		cout << nn <<"\t is Prime.\n";
	} else {
		cout << nn <<"\t is Composite\n";
	}
	fclose(fp);
	free(nn);
	return 0;
}
//#endif
