//PAT 1003, 2018/2/12

/*
A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- 
everyone involved in moving a product from supplier to customer.

Starting from one root supplier, everyone on the chain buys products from one's supplier 
in a price P and sell or distribute them in a price that is r% higher than P.
It is assumed that each member in the supply chain has exactly one supplier except the 
root supplier, and there is no supply cycle.

Now given a supply chain, you are supposed to tell the highest price we can expect from some retailers.
输入描述:
Each input file contains one test case.  For each case, The first line contains three 
positive numbers: N (<=105), the total number of the members in the supply chain (and 
hence they are numbered from 0 to N-1); P, the price given by the root supplier; and r, 
the percentage rate of price increment for each distributor or retailer.  Then the next 
line contains N numbers, each number Si is the index of the supplier for the i-th member.  
Sroot for the root supplier is defined to be -1.  All the numbers in a line are separated
by a space.


输出描述:
For each test case, print in one line the highest price we can expect from some retailers, 
accurate up to 2 decimal places, and the number of retailers that sell at the highest price.  
There must be one space between the two numbers.  It is guaranteed that the price will not
exceed 1010.
示例1
输入
9 1.80 1.00
1 5 4 4 -1 4 5 3 6
输出
1.85 2
*/

//solve it both recursively and non-recursively 

#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;

const int max_size = 100000;
int N;
double P, r;
int sup_count = 0, longest_route = 0, temp_route;
vector<int> mysup;    //record each member's supplier

void recur(int i) {      //find longest route recursively
	if (i == -1) {
		if (temp_route < longest_route) return;
		if (temp_route == longest_route) {
			sup_count++;
			return;
		}
		if (temp_route > longest_route) {
			longest_route = temp_route;
			sup_count = 1;
			return;
		}

	}
	else {
		temp_route++;
		recur(mysup[i]);
		return;
	}
}

void non_recur(int i) {      //find longest route non-recursively
	while (i != -1) {
		temp_route++;
		i = mysup[i];
	}
	if (i == -1) {
		if (temp_route < longest_route) return;
		if (temp_route == longest_route) {
			sup_count++;
			return;
		}
		if (temp_route > longest_route) {
			longest_route = temp_route;
			sup_count = 1;
			return;
		}

	}
}

int main() {
	cin >> N >> P >> r;   //input first row's information
	if (N > max_size) return 0;
	
	int i, sup;
	for (i = 0; i < N; i++) {
		cin >> sup;
		mysup.push_back(sup);
	}
	for (i = 0; i < N; i++){
		temp_route = 0;
		non_recur(i);
	}
	double highest_price = P * (pow((1 + r / 100), longest_route - 1));
	printf("%.2f %d", highest_price, sup_count);

	vector<int>().swap(mysup);  //clear vector
	return 0;
}
