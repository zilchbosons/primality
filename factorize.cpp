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

void characterize(int* eigen, char* nn) {
	int l = strlen(nn);
	for (int i = 0; i < l; ++i) {
		int nk = nn[i] - '0';
		int r = nk % 7;
		if (r<5) {
			eigen[i] = r;
		} else if (r == 5) {
			eigen[i] = 0;
		} else if (r > 5) {
			eigen[i] = r - 7;
		}
	}
	return;
}

void print(int* eigen, int l) {
	for (int i = 0; i <l ;++i) {
		cout <<eigen[i]<<"\t,\t";
	}
	cout <<"\n";
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
	int* eigen = new int[l];
	for (int i  = 0; i <l ; ++i) {
	eigen[i] = 0;
	}
characterize(eigen, nn);
cout <<"\nEigenvector:\n";
print(eigen, l);
fclose(fp);
free(nn);
return 0;
}

