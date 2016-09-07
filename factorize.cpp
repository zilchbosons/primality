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
const int _nmrk = 46938;

#define divLT5 10000

int signature[5] = { -1, 2, 3, 1, -3 };

long double getMultiplier(int x, long int divisor) {
	switch (x) {
		case 0:
			return (nmrk*.1 / divisor);
			break;
		case 1:
			return (mrkn*.1 / divisor);
			break;

		case 2:
			return (rknm*.1 / divisor);
			break;

		case 3:
			return (knmr*.1 / divisor);
			break;

		case 4:
			return (_nmrk*.1 / divisor);
			break;

		default:
			return (nmrk*.1 / divisor);
			break;
	}
	return (nmrk*.1 / divisor);
}

char* factorize(char* nn, int l, int offset) {
	int num = atoi(nn);
	std::string num2 = "";
	for (int i = offset ; i < offset+l; ++i) {
		int nk = nn[i-offset] - '0';
		if (nk + signature[i] > 9) {
			nk = (nk-10) +  signature[i];
			if (nk == 0 && l == 1) nk = 29;
		} else if  ((nk + signature[i])<0) {
			nk = (10-nk) +  signature[i];
			if (nk == 0 && l == 1) nk = 29;
		} else {
			nk = nk + signature[i];
		}
		num2 += boost::lexical_cast<std::string>(nk);
	}
	return strdup((char*) num2.c_str());
}


char* factorizeEQ1(char* nn) {
	long double acc = 0;
	int num = atoi(nn);
	int l = strlen(nn);
	long int mult = divLT5 / pow(10, l);
	for (int i = 0 ; i < 5; ++i) {
		int term = atoi(factorize(nn, l, i));
		if (term == 0) term = 29;
		long double multiplier = getMultiplier(i, mult);
		acc += log(term)*log(multiplier);
	}
	acc = log(acc);
	std::string result = boost::lexical_cast<std::string>(roundOff(acc));
	return strdup((char*) result.c_str());
}

std::string gFac = "";
char* factorizeEQ5(char* nn) {
	int l = strlen(nn);
	char*  snum3 = factorize(nn, l, 0);
	long int num3 = atoi(snum3);
	long double acc = log(num3)*log(69384);
	char* factor = strdup((char*) boost::lexical_cast<std::string>(roundOff(acc)).c_str());
	return factor;
}

std::string factorizeGT1(char* nn, int i, int l) {
	return gFac;
}

char* factorizeLEQ5(char* nn) {
	int l = strlen(nn);
	std::string ns = nn;
	int acc = 0;
	for (int i = 0; i < l; ++i) {
		std::rotate(ns.begin(), ns.begin()+1, ns.end());
		char* tmp = strdup((char*) ns.c_str());
		cout << "\ntmp:\t"<<tmp<<"\n";
		char* f = factorizeEQ5(tmp);
		acc+=atoi(f);
		free(tmp);
	}
	int factor= (acc % 10) + (acc / 10);
	cout <<"\nFactor:\t"<<factor<<"\n"; 
	return ((char*)(boost::lexical_cast<std::string>(factor)).c_str());
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
	if (l <= 5 && l>1) {
		if (l < 5) {
			char* factor = factorizeLEQ5(nn);
			if (factor) {
				cout << "\nFactor:\t"<<factor<<"\n";
			}
		} else if (l == 5) {
			char* factor = factorizeEQ5(nn);
			if (factor) {
				cout << "\nFactor:\t"<<factor<<"\n";
			}
		}
	} else  if (l ==1) {
		char* factor = factorizeEQ1(nn);
		if (factor) {
			cout << "\nFactor:\t"<<factor<<"\n";
		}
	} else {
		std::string factor = factorizeGT1(nn, 0, l);
		cout << "\nFactor:\t"<<factor<<"\n";
	}
	fclose(fp);
	free(nn);
	return 0;
}

