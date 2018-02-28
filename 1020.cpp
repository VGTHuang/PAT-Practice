//PAT 1020, 2018/2/28

/*
题目描述
If a machine can save only 3 significant digits, the float numbers 12300 and 12358.9 are considered equal since they are both saved as 0.123*105 with simple chopping.  Now given the number of significant digits on a machine and two float numbers, you are supposed to tell if they are treated equal in that machine.

输入描述:
Each input file contains one test case which gives three numbers N, A and B, where N (<100) is the number of significant digits, and A and B are the two float numbers to be compared.  Each float number is non-negative, no greater than 10100, and that its total digit number is less than 100.


输出描述:
For each test case, print in a line "YES" if the two numbers are treated equal, and then the number in the standard form "0.d1...dN*10^k" (d1>0 unless the number is 0); or "NO" if they are not treated equal, and then the two numbers in their standard form.  All the terms must be separated by a space, with no extra space at the end of a line.
Note: Simple chopping is assumed without rounding.

输入例子:
3 12300 12358.9

输出例子:
YES 0.123*10^5

测试用例:
99 0 0.000

对应输出应该为:

YES 0.000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000*10^0

测试用例:
2 0.00000000000000012 0.00000000000000012354

对应输出应该为:

YES 0.12*10^-15

*/

//this approach is by comparing standard forms of each integers (string).

#include <iostream>
#include <string>

using namespace std;

string num1, num2, stdnum1, stdnum2;
int machinedig = 10;

string intToString(const int i) {
	int temp = i, digit;
	if (i >= 0) {
		for (digit = 1; digit < 1000; digit++) {
			temp /= 10;
			if (temp == 0)break;
		}
		temp = i;
		char* s = new char[digit + 1];
		s[digit] = '\0';
		while (digit != 0) {
			digit--;
			s[digit] = temp % 10 + 48;
			temp = temp / 10;
		}
		return s;
	}
	else if (i == 0) {
		return "0";
	}
	else {
		temp = -temp;
		for (digit = 1; digit < 1000; digit++) {
			temp /= 10;
			if (temp == 0)break;
		}
		temp = -i;
		char* s = new char[digit + 2];
		s[digit + 1] = '\0';
		s[0] = '-';
		while (digit != 0) {
			digit--;
			s[digit + 1] = temp % 10 + 48;
			temp = temp / 10;
		}
		return s;
	}
}

string charToString(const char c) {
	char* s = new char[2];
	s[0] = c;
	s[1] = '\0';
	return s;
}

int getFirstNozero(string num) {
	for (int i = 0; i < num.length(); i++) {
		if (num[i] != '0' && num[i] != '.') return i;
	}
	return -1;
}

int getDecimalPoint(string num) {
	for (int i = 0; i < num.length(); i++) {
		if (num[i] == '.') return i;
	}
	return -1;
}

string convertToStandard(const string num) {
	string stdnum;
	int nozero = getFirstNozero(num), decimal = getDecimalPoint(num);
	int exponent, printcount = 0;
	int i;
	if (nozero == -1) {
		stdnum.append("0.");
		
		for (printcount = 0; printcount < machinedig; printcount++) stdnum.append("0");
		stdnum.append("*10^");
		stdnum.append("0");
	}
	else if (nozero != -1) {
		if (decimal == -1) {
			stdnum.append("0.");
			exponent = num.length() - nozero;
			for (i = nozero; i < num.length() && printcount < machinedig; i++) {
				stdnum.append(charToString(num[i]));
				printcount++;
			}
			if (printcount < machinedig) {
				for (i = 0; i < machinedig - printcount; i++) {
					stdnum.append("0");
				}
			}
			stdnum.append("*10^");
			stdnum.append(intToString(exponent));
		}
		else if (decimal != -1) {
			stdnum.append("0.");
			exponent = decimal - nozero;
			if (exponent < 0)exponent++;
			for (i = nozero; i < num.length() && printcount < machinedig; i++) {
				if (num[i] != '.') {
					stdnum.append(charToString(num[i]));
					printcount++;
				}
			}
			if (printcount < machinedig) {
				for (i = 0; i < machinedig - printcount; i++) {
					stdnum.append("0");
				}
			}
			stdnum.append("*10^");
			stdnum.append(intToString(exponent));
		}
	}
	return stdnum;
}

int main() {
	cin >> machinedig >> num1 >> num2;
	stdnum1 = convertToStandard(num1);
	stdnum2 = convertToStandard(num2);


	if (stdnum1.compare(stdnum2) == 0) {
		cout << "YES ";
		cout << stdnum1;
		
	}
	else {
		cout << "NO ";
		cout << stdnum1;
		cout << ' ';
		cout << stdnum2;
	}

	return 0;
}