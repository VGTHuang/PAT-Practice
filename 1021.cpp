//PAT 1021, 2018/3/1

/*
题目描述
Given two sets of integers, the similarity of the sets is defined to be Nc/Nt*100%, where Nc is the number of distinct common numbers shared by the two sets, and Nt is the total number of distinct numbers in the two sets.  Your job is to calculate the similarity of any given pair of sets.

输入描述:
Each input file contains one test case.  Each case first gives a positive integer N (<=50) which is the total number of sets.  Then N lines follow, each gives a set with a positive M (<=104) and followed by M integers in the range [0, 109].  After the input of sets, a positive integer K (<=2000) is given, followed by K lines of queries.  Each query gives a pair of set numbers (the sets are numbered from 1 to N).  All the numbers in a line are separated by a space.


输出描述:
For each query, print in one line the similarity of the sets, in the percentage form accurate up to 1 decimal place.

输入例子:
3
3 99 87 101
4 87 101 5 87
7 99 101 18 5 135 18 99
2
1 2
1 3

输出例子:
50.0%
33.3%
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
//INT_MAX = 2147483647

using namespace std;

struct elem {
	int value;
	short int set;
};

vector<elem> all;   //record every element in one same vector

bool cmpelem(elem a, elem b) {
	return (a.value < b.value);
}

void cmpset(short int a, short int b) {
	if (a == b || all.size() == 1) {
		cout << "100.0%";
		return;
	}

	int i = 0, j, Nc = 0, Nt = 0;
	
	while (i != all.size()) {
		int rec;
		if (all[i].set == a) {
			rec = 1;
			j = i + 1;
			while (j < all.size() && all[j].value == all[i].value) {
				if (all[j].set == b) {
					rec = 2;
				}
				j++;
			}
		}
		else if (all[i].set == b) {
			rec = 1;
			j = i + 1;
			while (j < all.size() && all[j].value == all[i].value) {
				j++;
			}
		}
		else {
			rec = 0;
			j = i + 1;
			while (j < all.size() && all[j].value == all[i].value) {
				if ((all[j].set == a || all[j].set == b) && rec == 0)rec = 1;
				else if (all[j].set == b && rec == 1)rec = 2;
				j++;
			}
		}
		
		switch (rec)
		{
		case 0:
			//printf("0,%d,%d\n", all[i].value, all[i].set);
			break;
		case 1:
			//printf("1,%d,%d\n", all[i].value, all[i].set);
			Nt++;
			break;
		case 2:
			//printf("2,%d,%d\n", all[i].value, all[i].set);
			Nc++;
			Nt++;
			break;
		default:
			break;
		}
		i = j;
	}


	printf("%.1f%%", Nc * 100.0 / Nt);
}

int main() {
	int setnum, setcount = 1;
	elem tempelem;
	cin >> setnum;
	while (setcount <= setnum) {
		int setsize;
		cin >> setsize;
		for (int i = 0; i < setsize; i++) {
			cin >> tempelem.value;
			tempelem.set = setcount;
			all.push_back(tempelem);
		}
		
		if (getchar() == '\n') {
			setcount++;
		}
	}
	stable_sort(all.begin(), all.end(), cmpelem);
	//for (int i = 0; i < all.size(); i++)	cout << all[i].value << ' ' << all[i].set << endl;
	int querynum;
	short int seta, setb;
	cin >> querynum;
	for (int i = 0; i < querynum; i++) {
		cin >> seta >> setb;
		if (seta > setb) swap(seta, setb);
		
		cmpset(seta, setb);
		if (i < querynum - 1) cout << endl;
	}


	return 0;
}