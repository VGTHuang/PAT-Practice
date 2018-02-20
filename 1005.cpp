//PAT 1005, 2018/2/14

/*
题目描述
A family hierarchy is usually presented by a pedigree tree where all the nodes on the same level 
belong to the same generation.  Your task is to find the generation with the largest population.

输入描述:
Each input file contains one test case.  Each case starts with two positive integers N (<100) which 
is the total number of family members in the tree (and hence assume that all the members are numbered 
from 01 to N), and M (<N) which is the number of family members who have children.  Then M lines follow, 
each contains the information of a family member in the following format:

ID K ID[1] ID[2] ... ID[K]

where ID is a two-digit number representing a family member, K (>0) is the number of his/her children, 
followed by a sequence of two-digit ID's of his/her children. For the sake of simplicity, let us fix 
the root ID to be 01.  All the numbers in a line are separated by a space.


输出描述:
For each test case, print in one line the largest population number and the level of the 
corresponding generation.  It is assumed that such a generation is unique, and the root level 
is defined to be 1.

输入例子:
23 13
21 1 23
01 4 03 02 04 05
03 3 06 07 08
06 2 12 13
13 1 21
08 2 15 16
02 2 09 10
11 2 19 20
17 1 22
05 1 11
07 1 14
09 1 17
10 1 18

输出例子:
9 4
*/

//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

class Family {
private:
	unsigned int totalnum, parentnum;   /*N (<100) the total number of family members in the tree
				(and hence assume that all the members are numbered from 01 to N)
				and M (<N) which is the number of family members who have children.*/

	vector<vector<int>> bound;
	vector<bool> visited;
	unsigned int* gen;                          //to record each member's generation
public:
	Family(int N, int M) :totalnum(N), parentnum(M) {
		visited.resize(N + 1, false);  //+1: member starts at 01
		bound.resize(N + 1);           //+1: member starts at 01
		gen = (unsigned int*)malloc((N + 1) * sizeof(unsigned int));//+1: member starts at 01
		gen[01] = 1;                   //"the root level is defined to be 1."
	}
	void Initbound(void);
	void Printfamily(void);
	void DFS(int ver);
	void Sortgen() {
		sort(gen, gen + totalnum + 1);
	}
	void Getlargest() {              //"print in one line the largest population number
		                             //and the level of the corresponding generation."
		unsigned int largest_ppl = 0, largest_level = 1, temp_ppl = 1;
		unsigned int i;
		for (i = 1; i < totalnum + 1; i++) {
			if (i == totalnum || gen[i] != gen[i + 1]) {
				if (temp_ppl >= largest_ppl) {
					largest_level = gen[i];
					largest_ppl = temp_ppl;
				}
				temp_ppl = 1;
			}
			else temp_ppl++;
		}
		cout << largest_ppl << ' ' << largest_level;
	}
};

void Family::Initbound(void) {        //"Then M lines follow, each contains the information
	                                  //of a family member in the following format:"
	unsigned int i, j;
	unsigned int par, childnum, tempchild;
	for (i = 01; i <= parentnum; i++) {
		cin >> par >> childnum;
		for (j = 0; j < childnum; j++) {
			cin >> tempchild;
			bound[par].push_back(tempchild);
		}
	}
	return;
}

void Family::Printfamily(void) {    //to test if input is corrent
	unsigned int i, j;
	for (i = 01; i < bound.size(); i++) {
		if (bound[i].size()) {
			cout << i << ' ' << bound[i].size();
			for (j = 0; j < bound[i].size(); j++) {
				cout << ' ' << bound[i][j];
			}
			cout << endl;
		}
	}
}

void Family::DFS(int ver) {
	bool end = true;
	unsigned int tempchild;
	for (tempchild = 0; tempchild < bound[ver].size(); tempchild++) {
		if (!visited[bound[ver][tempchild]]) {
			end = false;
			break;
		}
	}
	if (end)
		return;
	else {
		for (tempchild = 0; tempchild < bound[ver].size(); tempchild++) {
			if (!visited[bound[ver][tempchild]]) {
				gen[bound[ver][tempchild]] = gen[ver] + 1; //it's generation = its parent's generation + 1
				visited[bound[ver][tempchild]] = true;
				DFS(bound[ver][tempchild]);
			}
		}
	}
}

int main() {
	unsigned int N, M;
	cin >> N >> M;
	Family F(N, M);
	F.Initbound();
	F.DFS(01);
	F.Sortgen();
	F.Getlargest();
	return 0;
}
