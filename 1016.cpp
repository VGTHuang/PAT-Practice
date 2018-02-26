//PAT 1016, 2018/2/26

/*
题目描述
Mice and Rice is the name of a programming contest in which each programmer must write a piece of code to control the movements of a mouse in a given map.  The goal of each mouse is to eat as much rice as possible in order to become a FatMouse.
First the playing order is randomly decided for NP programmers.  Then every NG programmers are grouped in a match.  The fattest mouse in a group wins and enters the next turn.  All the losers in this turn are ranked the same.  Every NG winners are then grouped in the next match until a final winner is determined.
For the sake of simplicity, assume that the weight of each mouse is fixed once the programmer submits his/her code.  Given the weights of all the mice and the initial playing order, you are supposed to output the ranks for the programmers.

输入描述:
Each input file contains one test case.  For each case, the first line contains 2 positive integers: NP and NG (<= 1000), the number of programmers and the maximum number of mice in a group, respectively.  If there are less than NG mice at the end of the player's list, then all the mice left will be put into the last group.  The second line contains NP distinct non-negative numbers Wi (i=0,...NP-1) where each Wi is the weight of the i-th mouse respectively.  The third line gives the initial playing order which is a permutation of 0,...NP-1 (assume that the programmers are numbered from 0 to NP-1).  All the numbers in a line are separated by a space.


输出描述:
For each test case, print the final ranks in a line.  The i-th number is the rank of the i-th programmer, and all the numbers must be separated by a space, with no extra space at the end of the line.

输入例子:
11 3
25 18 0 46 37 3 19 22 57 56 10
6 0 8 7 10 5 9 1 4 2 3

输出例子:
5 5 5 2 5 5 5 3 1 3 5
*/

//very messy!

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int NP, NG;
struct programmer {
	int order;
	int mouseweight;
	int index;
	int rank;
};
vector<programmer> contestant;
vector<programmer> ranked;

bool cmpcontestants(programmer a, programmer b) {
	return (a.order < b.order);
}

bool cmpcontestantsrank(programmer a, programmer b) {
	return (a.rank > b.rank);
}

bool cmpcontestantsindex(programmer a, programmer b) {
	return (a.index < b.index);
}

void print() {
	for (int i = 0; i < contestant.size(); i++) {
		cout << contestant[i].mouseweight << ' ' << contestant[i].rank << ' ' << contestant[i].order << endl;
	}
	cout << "***********\n";
}

int getmax(int from, int to) {
	int fattest = 0, max;
	for (int i = from; i <= to; i++) {
		if (contestant[i].mouseweight > fattest) {
			fattest = contestant[i].mouseweight;
			max = i;
		}
	}
	return max;
}

void contestantRank() {
	unsigned int max, temp, i, myrank = 0;
	
	while (!contestant.empty()) {
		myrank++;
		for (temp = 0; temp + NG - 1 < contestant.size(); temp += NG) {
			max = getmax(temp, temp + NG - 1);
			for (i = temp; i <= temp + NG - 1; i++)
				if (i != max) contestant[i].rank = myrank;
		}
		if (temp <= contestant.size() - 1) {
			max = getmax(temp, contestant.size() - 1);
			for (i = temp; i <= contestant.size() - 1; i++)
				if (i != max || contestant.size() == 1) contestant[i].rank = myrank; 
			    // debug: if only 1 contestant remains, then it has to pop (|| contestant.size() == 1)
		}
		for (temp = 0; temp < contestant.size();) {
			if (contestant[temp].rank != myrank)
				temp++;
			else {
				programmer tempcon;
				tempcon.index = contestant[temp].index;
				tempcon.mouseweight = contestant[temp].mouseweight;
				tempcon.order = contestant[temp].order;
				tempcon.rank = contestant[temp].rank;
				ranked.push_back(tempcon);

				contestant.erase(contestant.begin() + temp);
			}
		}
	}
}

int main() {
	//input
	cin >> NP >> NG;
	contestant.resize(NP);
	for (unsigned int i = 0; i < contestant.size(); i++) {
		cin >> contestant[i].mouseweight;
		contestant[i].index = i;
		contestant[i].rank = -1;
	}
	for (unsigned int i = 0; i < contestant.size(); i++) {
		int temp;
		cin >> temp;
		contestant[temp].order = i;
	}

	//logic
	sort(contestant.begin(), contestant.end(), cmpcontestants);

	contestantRank();

	sort(ranked.begin(), ranked.end(), cmpcontestantsrank);

	int temprank = 1, prerank;
	for (unsigned int i = 0; i < ranked.size(); i++) {
		if (i > 0 && ranked[i].rank != prerank) temprank = i + 1;
		prerank = ranked[i].rank;
		ranked[i].rank = temprank;
	}

	sort(ranked.begin(), ranked.end(), cmpcontestantsindex);

	for (unsigned i = 0; i < ranked.size() - 1; i++)
			cout << ranked[i].rank << ' ';
		cout << ranked[ranked.size() - 1].rank;


	return 0;
}