//PAT 1019, 2018/2/28

/*
题目描述
Given any positive integer N, you are supposed to find all of its prime factors, and write them in the format N = p1^k1 * p2^k2 *...*pm^km.

输入描述:
Each input file contains one test case which gives a positive integer N in the range of long int.


输出描述:
Factor N in the format N = p1^k1 * p2^k2 *...*pm^km, where pi's are prime factors of N in increasing order, and the exponent ki is the number of pi -- hence when there is only one pi, ki is 1 and must NOT be printed out.

输入例子:
97532468

输出例子:
97532468=2^2*11*17*101*1291
*/

//messy

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
vector<int> smallprime;
vector<long int> largeprime;
vector<long int> factor;
const int smallprimeMAX = 200;

bool isprime(long int n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (n == 3) return true;
	long int MAX = (long int)sqrt(n);
	for (int i = 2; i <= MAX; i++) {
		if (n%i == 0) return false;
	}
	return true;
}

void getShortPrimeList() {          //a positive composite integer is most likely to have factors under smallprimeMAX
	smallprime.push_back(2);
	int i, j;
	bool isprime;
	for (i = 3; i <= smallprimeMAX; i += 2) {
		isprime = true;
		for (j = 0; j < smallprime.size(); j++) {
			if (i%smallprime[j] == 0) {
				isprime = false;
				break;
			}
		}
		if (isprime) {
			smallprime.push_back(i);
		}
	}
}

void getLargePrimeList(long int range) {
	largeprime.push_back(2);
	long int i, j;
	bool isprime;
	for (i = smallprimeMAX + 1; i <= range; i += 1) {
		isprime = true;
		for (j = 0; j < smallprime.size(); j++) {
			if (i%smallprime[j] == 0) {
				isprime = false;
				break;
			}
		}
		if (isprime) {
			for (j = 0; j < largeprime.size(); j++) {
				if (i%largeprime[j] == 0) {
					isprime = false;
					break;
				}
			}
		}
		if (isprime) {
			largeprime.push_back(i);
		}
	}
}

void printFactor(long int num) {
	cout << num << '=';
	int i;
	int samefactorcount;
	for (i = 0; i < factor.size();) {
		cout << factor[i];
		samefactorcount = 0;
		while (i + samefactorcount + 1 < factor.size() && 
			factor[i + samefactorcount] == factor[i + samefactorcount + 1]) {
			samefactorcount++;
		}
		if (samefactorcount > 0) cout << '^' << samefactorcount+1;
		i += samefactorcount + 1;
		if (i >= factor.size()) break;
		else cout << '*';
	}
}

int main() {
	getShortPrimeList();
	long int num, numcopy;
	cin >> num;
	if (num == 1) {
		cout << "1=1";
	}
	else if (isprime(num)) {
		cout << num << '=' << num;
	}
	
	else {

		numcopy = num;
		int i;
		for (i = 0; i < smallprime.size(); i++) {
			if (numcopy == 1)break;
			else while (numcopy%smallprime[i] == 0 && numcopy >= smallprime[i]) {
				
				numcopy /= smallprime[i];
				factor.push_back(smallprime[i]);
			}
		}
		if (numcopy > smallprimeMAX) {
			if (isprime(numcopy)) {
				factor.push_back(numcopy);
			}
			else {
				getLargePrimeList((int)sqrt(numcopy));
				for (i = 0; i < largeprime.size();) {
					if (isprime(numcopy)) {
						factor.push_back(numcopy);
						break;
					}
					while (numcopy%largeprime[i] == 0) {
						numcopy /= largeprime[i];
						factor.push_back(largeprime[i]);
					}
					i++;
				}
			}
		}
		printFactor(num);

	}
	
	return 0;
}