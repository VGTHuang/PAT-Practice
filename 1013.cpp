//PAT 1013, 2018/2/20

/*
题目描述
The task of this problem is simple: insert a sequence of distinct positive integers into a hash table, and output the positions of the input numbers.  The hash function is defined to be "H(key) = key % TSize" where TSize is the maximum size of the hash table.  Quadratic probing (with positive increments only) is used to solve the collisions.
Note that the table size is better to be prime.  If the maximum size given by the user is not prime, you must re-define the table size to be the smallest prime number which is larger than the size given by the user.

输入描述:
Each input file contains one test case.  For each case, the first line contains two positive numbers: MSize (<=104) and N (<=MSize) which are the user-defined table size and the number of input numbers, respectively.  Then N distinct positive integers are given in the next line.  All the numbers in a line are separated by a space.


输出描述:
For each test case, print the corresponding positions (index starts from 0) of the input numbers in one line.  All the numbers in a line are separated by a space, and there must be no extra space at the end of the line.  In case it is impossible to insert the number, print "-" instead.

输入例子:
4 4
10 6 4 15

输出例子:
0 1 4 -
*/

#include <iostream>
#include <cstdlib>

using namespace std;

bool isprime(const int a) {
	if (a < 2) return false;        //1 is not prime
	int divisor;
	for (divisor = 2; divisor * divisor <= a; divisor++) {
		if (a % divisor == 0) return false;
	}
	return true;
}

void ResizeTable(int& t) {     //if t is not a prime number, find the minimum prime number larger than t
	if (isprime(t)) return;
	t++;
	while (!isprime(t) && t <= 10007) t++;  //table size <= 10007
	return;
}

int Hashpush(int key, int* t, int tsize) {
	int finalpoint;
	int hkey = key % tsize;
	if (t[hkey] == -1) {
		t[hkey] = key;
		finalpoint = hkey;
		return finalpoint;
	}
	int shift = 1;
	while (shift * shift <= tsize) {
		if (t[(hkey + shift*shift) % tsize] == -1) {
			t[(hkey + shift*shift) % tsize] = key;
			finalpoint = (hkey + shift*shift) % tsize;
			return finalpoint;
		}
		shift++;
	}
	return -1;
}

int main() {
	int tablesize, inputnum, i, tempinput;
	cin >> tablesize >> inputnum;
	ResizeTable(tablesize);
	int* table = (int*)malloc(sizeof(int)*tablesize);
	for (i = 0; i < tablesize; i++) table[i] = -1;  //inputs are positive integers. 0 represents empty
	for (i = 0; i < inputnum; i++) {
		cin >> tempinput;
		int fin = Hashpush(tempinput, table, tablesize);
		if (fin != -1)cout << fin;
		else cout << '-';
		if (i < inputnum - 1) cout << ' ';
	}
	return 0;
}