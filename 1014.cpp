//PAT 1014, 2018/2/20

/*
题目描述
A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- everyone involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier in a price P and sell or distribute them in a price that is r% higher than P.  Only the retailers will face the customers.
It is assumed that each member in the supply chain has exactly one supplier except the root supplier, and there is no supply cycle.

Now given a supply chain, you are supposed to tell the total sales from all the retailers.

输入描述:
Each input file contains one test case.  For each case, the first line contains three positive numbers: N (<=105), the total number of the members in the supply chain (and hence their ID's are numbered from 0 to N-1, and the root supplier's ID is 0); P, the unit price given by the root supplier; and r, the percentage rate of price increment for each distributor or retailer.  Then N lines follow, each describes a distributor or retailer in the following format:
Ki ID[1] ID[2] ... ID[Ki]
where in the i-th line, Ki is the total number of distributors or retailers who receive products from supplier i, and is then followed by the ID's of these distributors or retailers.  Kj being 0 means that the j-th member is a retailer, then instead the total amount of the product will be given after Kj.  All the numbers in a line are separated by a space.


输出描述:
For each test case, print in one line the total sales we can expect from all the retailers, accurate up to 1 decimal place.  It is guaranteed that the number will not exceed 1010.

输入例子:
10 1.80 1.00
3 2 3 5
1 9
1 4
1 7
0 7
2 6 1
1 8
0 9
0 4
0 3

输出例子:
42.4
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>  //printf()

using namespace std;


vector<vector<int>> member;
vector<int> isretailer;
vector<int> level;

void GetLevel() {  //use BFS to get supply level of each member
	level[0] = 0;  //root supplier's level = 0
	queue<int> que;
	int tempmem;
	unsigned int i;
	que.push(0);
	while (!que.empty()) {
		tempmem = que.front();
		que.pop();
		for (i = 0; i < member[tempmem].size(); i++) {
			level[member[tempmem][i]] = level[tempmem] + 1;
			que.push(member[tempmem][i]);
		}
	}
	return;
}

int main() {
	int N, i, j;
	double P, r;
	cin >> N >> P >> r;
	member.resize(N);
	isretailer.resize(N, 0);
	level.resize(N);

	int ki, tempnode;
	for (i = 0; i < N; i++) {
		cin >> ki;
		if (ki == 0) { //is retailer
			cin >> isretailer[i];
			if (isretailer[i] == 0)  //in case the retailer made 0 sales
				isretailer[i] = -1;
		}
		else
			for (j = 0; j < ki; j++) {
				cin >> tempnode;
				member[i].push_back(tempnode);
			}
	}

	GetLevel();
	double sum = 0;
	for (i = 0; i < N; i++) {
		if (isretailer[i] != 0) {
			if (isretailer[i] == -1);
			else {
				sum += P * pow(1 + 0.01 * r, (double)level[i]) * isretailer[i];
			}
		}
	}

	printf("%.1f", sum);

	return 0;
}
