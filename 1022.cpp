//PAT 1022, 2018/3/4

/*
题目描述
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.
A Complete Binary Tree (CBT) is a tree that is completely filled, with the possible exception of the bottom level, which is filled from left to right.
Now given a sequence of distinct non-negative integer keys, a unique BST can be constructed if it is required that the tree must also be a CBT.  You are supposed to output the level order traversal sequence of this BST.

输入描述:
Each input file contains one test case.  For each case, the first line contains a positive integer N (<=1000).  Then N distinct non-negative integer keys are given in the next line.  All the numbers in a line are separated by a space and are no greater than 2000.


输出描述:
For each test case, print in one line the level order traversal sequence of the corresponding complete binary search tree.  All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

输入例子:
10
1 2 3 4 5 6 7 8 9 0

输出例子:
6 3 8 1 5 7 9 0 2 4
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

int nodenum;
vector<int> bitree;
vector<int> nums;

int getrootrank(int n) {  //given the num of nodes in a BST/CBT, return the ranking of root node
	int cpl_level;
	for (cpl_level = 1; pow(2, cpl_level) - 1 < n; cpl_level++);
	cpl_level--;
	if (n - (pow(2, cpl_level) - 1) <= pow(2, cpl_level - 1)) {  //incomplete part on the left
		return (n - pow(2, cpl_level - 1));
	}
	else
		return pow(2, cpl_level)-1;
}

void traverse(int from, int to, int n) {
	if (to - from < 0)return;
	int rootrank = getrootrank(to - from + 1);
	bitree[n] = from + rootrank;
	//getchar();
	traverse(from, from+rootrank - 1, (n + 1) * 2 - 1);
	if (to - from - rootrank - 1 >= 0)
		traverse(from + rootrank + 1, to, (n + 1) * 2);
	return;
}

int main() {

	//input
	cin >> nodenum;
	bitree.resize(nodenum);
	for (int i = 0; i < nodenum; i++) {
		int temp;
		cin >> temp;
		nums.push_back(temp);
	}
	sort(nums.begin(), nums.end());
	traverse(0, nodenum-1, 0);
	for (int i = 0; i < nodenum; i++) {
		cout << nums[bitree[i]];
		if (i == nodenum - 1) cout << ' ';
	}
	return 0;
}