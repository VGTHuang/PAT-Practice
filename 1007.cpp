//PAT 1007, 2018/2/15

/*
题目描述
Among all the factors of a positive integer N, there may exist several consecutive numbers.  
For example, 630 can be factored as 3*5*6*7, where 5, 6, and 7 are the three consecutive numbers.  
Now given any positive N, you are supposed to find the maximum number of consecutive factors, 
and list the smallest sequence of the consecutive factors.

输入描述:
Each input file contains one test case, which gives the integer N (131).


输出描述:
For each test case, print in the first line the maximum number of consecutive factors.  Then 
in the second line, print the smallest sequence of the consecutive factors in the format 
"factor[1]*factor[2]*...*factor[k]", where the factors are listed in increasing order, 
and 1 is NOT included.

输入例子:
630

输出例子:
3
5*6*7
*/

//parameters are messy!

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

struct con {
	int minfac;
	int num;
};

int main() {
	vector<con> consec;
	long int N, tempN;
	int i, j;
	cin >> N;
	struct con tempcon;
	for (i = 2; i <= sqrt(N); i++) {
		tempN = N;
		j = i;
		while (tempN%i == 0) {
			tempcon.minfac = i;
			tempcon.num = 1;
			consec.push_back(tempcon);
			tempN /= i;
			while (tempN % (j + 1) == 0) {
				consec.back().num++;
				j++;
				tempN /= j;
			}
		}
	}

	if (consec.empty()){
		cout << 1 << endl << N;
	}
	else {
		int maxcon = 0, connum;
		for (i = 0; i < consec.size(); i++) {
			if (consec[i].num > consec[maxcon].num)
				maxcon = i;
		}
		connum = consec[maxcon].minfac;
		cout << consec[maxcon].num << endl;
		cout << connum;
		for (i = 1; i < consec[maxcon].num; i++)
			cout << '*' << ++connum;
	}
	
	return 0;
}
