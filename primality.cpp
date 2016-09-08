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
	mpz_init(nt);
	mpz_set_str(nt, nn, 10);
	mpz_t n_next;
	mpz_init(n_next);
	mpz_add_ui(n_next, nt, 1);
	mpz_t n_previous;
	mpz_init(n_previous);
	mpz_sub_ui(n_previous, nt, 1);
	mpz_mul(n_next, n_next, n_next);
	mpz_mul(n_previous, n_previous, n_previous);
	mpz_mul(nt, nt, nt);
	mpz_t result;
	mpz_init(result);
	mpz_sub(result, n_next, nt);
	mpz_add_ui(result, result, 29*29);
	mpz_t rt;
	mpz_init(rt);
	mpz_mod_ui(rt, result, 7);
	int rem = mpz_get_ui(rt);
	mpz_t result2;
	mpz_init(result2);
	mpz_sub(result2, nt, n_previous);
	mpz_add_ui(result2, result2, 29*29);
	mpz_t rt2;
	mpz_init(rt2);
	mpz_mod_ui(rt2, result2, 7);
	int rem2 = mpz_get_ui(rt2);
	int n1 = nn[0] -'0';
	mpz_clear(nt);
	mpz_clear(n_next);
	mpz_clear(n_previous);
	mpz_clear(result2);
	mpz_clear(rt2);
	mpz_clear(result);
	mpz_clear(rt);

	if (n1 == 2 || n1 == 4) {
		if (rem == 0 || rem2 == 0) {
			//not prime
			return false;
		} else if ((rem == 6 || rem2 == 6) && (rem ==1 || rem2 ==1)) {
			return true;
		} else if ((rem != 5 && rem2 != 5 && rem != 3 && rem2 != 3)) {
			return true;
		} else {
			return false;
		}
	} else {
		if (rem == 0 || rem2 == 0) {
			//not prime
			return true;
		} else if ((rem == 6 || rem2 == 6) && (rem ==1 || rem2 ==1)) {
			return false;
		} else if ((rem == 5 &&  rem2  == 3) ||  (rem == 3 && rem2 == 5)) {
			return true;
		} else {
			return false;
		}
	}
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

