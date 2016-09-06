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
#include <vector>
#include <boost/lexical_cast.hpp>
#include <algorithm>
#include "common.hpp"

using namespace std;

int eigen[5] = { -1, 2, 3, 1, -3 };

const int nmrk = 69384;
const int mrkn = 93846;
const int rknm = 38469;
const int knmr = 84693;
const int lossFor1Cyc = 4;

#define divLT5 10000

int signature[5] = { -1, 2, 3, 1, -3 };

long double getMultiplier(int x, long int divisor) {
	switch (x) {
		case 0:
			return nmrk / divisor;
			break;
		case 1:
			return mrkn / divisor;
			break;

		case 2:
			return rknm / divisor;
			break;

		case 3:
			return knmr / divisor;
			break;

		case 4:
			return nmrk / divisor;
			break;

		default:
			return nmrk / divisor;
			break;
	}
	return nmrk / divisor;
}

char* factorizeEQ5(char* nn) {
	int num = atoi(nn);
	std::string num2 = "";
	for (int i = 0 ; i < 5; ++i) {
		int nk = nn[i] - '0';
		if (num + signature[i] > 9) {
			nk = nk - (7 - signature[i]);
		} else if  ((nk + signature[i])<0) {
			nk = nk + (7 + signature[i]);
		} else {
			nk = nk + signature[i];
		}
		num2 += boost::lexical_cast<std::string>(nk);
	}
	long int num3 = atoi((char*) num2.c_str());
	long double acc = log(num3)*log(69384);
	acc += log(lossFor1Cyc);
	char* factor = strdup((char*) boost::lexical_cast<std::string>(floor(acc)).c_str());
	return factor;
}

char* factorizeLT5(char* nn) {
	long double acc = 0;
	int num = atoi(nn);
	for (int i = 0 ; i < 5; ++i) {
		long double term = (num + signature[i] > 9)? (num - (7 - signature[i])):((num + signature[i]) <0) ? (num+ (7+ signature[i])):(num + signature[i]);
		long double multiplier = getMultiplier(i, divLT5);
		acc += log(term)*log(multiplier);
	}
	acc = acc / log(nmrk);
	acc += log(lossFor1Cyc);
	std::string result = boost::lexical_cast<std::string>(floor(acc));
	return strdup((char*) result.c_str());
}

char* factorizeGT5(char* nn) {
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
	if (l == 5) {
		char* factor = factorizeEQ5(nn);
		if (factor) {
			cout << "\nFactor:\t"<<factor<<"\n";
		}
	} else if (l < 5) {
		char* factor = factorizeLT5(nn);
		if (factor) {
			cout << "\nFactor:\t"<<factor<<"\n";
		}
	} else {
		char* factor = factorizeGT5(nn);
		if (factor) {
			cout << "\nFactor:\t"<<factor<<"\n";
		}
	}
	fclose(fp);
	free(nn);
	return 0;
}

