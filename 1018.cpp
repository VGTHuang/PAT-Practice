//PAT 1018, 2018/2/28

/*
题目描述
If you are a fan of Harry Potter, you would know the world of magic has its own currency system -- as Hagrid explained it to Harry, "Seventeen silver Sickles to a Galleon and twenty-nine Knuts to a Sickle, it's easy enough."  Your job is to write a program to compute A+B where A and B are given in the standard form of "Galleon.Sickle.Knut" (Galleon is an integer in [0, 10^7], Sickle is an integer in [0, 17), and Knut is an integer in [0, 29)).

输入描述:
Each input file contains one test case which occupies a line with A and B in the standard form, separated by one space.


输出描述:
For each test case you should output the sum of A and B in one line, with the same format as the input.

输入例子:
3.2.1 10.16.27

输出例子:
14.1.28
*/

//have simpler approaches. used class to make it more structured.

#include <iostream>
#include <string>
using namespace std;

const int sickle2knut = 29, galleon2sickle = 17;


class hpcurrency {
public:
	long int galleon;
	int sickle;
	int knut;
	hpcurrency(string a) {
		galleon = 0;
		sickle = 0;
		knut = 0;
		int i;
		for (i = 0; a[i] != '.'; i++) {
			galleon *= 10;
			galleon += (int)a[i] - 48;
		}
		for (i++; a[i] != '.'; i++) {
			sickle *= 10;
			sickle += (int)a[i] - 48;
		}
		for (i++; a[i] != '\0'; i++) {
			knut *= 10;
			knut += (int)a[i] - 48;
		}
	}

	void addandoutput(hpcurrency cur) {
		galleon += cur.galleon;
		sickle += cur.sickle;
		knut += cur.knut;

		sickle += knut / sickle2knut;
		knut = knut % sickle2knut;
		galleon += sickle / galleon2sickle;
		sickle = sickle % galleon2sickle;

		output();
	}
	void output() {
		cout << galleon << '.' << sickle << '.' << knut;
	}
};

int main() {
	string tempcur;

	cin >> tempcur;
	hpcurrency cur1(tempcur);

	cin >> tempcur;
	hpcurrency cur2(tempcur);

	cur1.addandoutput(cur2);

	return 0;
}