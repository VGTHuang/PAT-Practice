//PAT 1010, 2018/2/18

/*
题目描述
A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees.

Given the structure of a binary tree and a sequence of distinct integer keys, there is only one way 
to fill these keys into the tree so that the resulting tree satisfies the definition of a BST.  
You are supposed to output the level order traversal sequence of that tree.  The sample is 
illustrated by Figure 1 and 2.

输入描述:
Each input file contains one test case.  For each case, the first line gives a positive integer N (<=100)
which is the total number of nodes in the tree.  The next N lines each contains the left and the
right children of a node in the format "left_index right_index", provided that the nodes are numbered
from 0 to N-1, and 0 is always the root.  If one child is missing, then -1 will represent the NULL child pointer.  
Finally N distinct integer keys are given in the last line.

输出描述:
For each test case, print in one line the level order traversal sequence of that tree.  
All the numbers must be separated by a space, with no extra space at the end of the line.

输入例子:
9
1 6
2 3
-1 -1
-1 4
5 -1
-1 -1
7 -1
-1 8
-1 -1
73 45 11 58 82 25 67 38 42

输出例子:
58 25 82 11 38 67 45 73 42
*/

//

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <queue>

using namespace std;

int traverseCounter = 0;

struct _node {
	int left_index;
	int right_index;
	int key;
	int counter;
};

void lnr(_node* bitree, int nodenum) {
	if (bitree[nodenum].left_index == -1 && bitree[nodenum].right_index == -1) {
		bitree[nodenum].counter = traverseCounter++;
		return;
	}
	else {
		if (bitree[nodenum].left_index != -1)
			lnr(bitree, bitree[nodenum].left_index);
		bitree[nodenum].counter = traverseCounter++;
		if (bitree[nodenum].right_index != -1)
			lnr(bitree, bitree[nodenum].right_index);
		return;
	}
}

void leveltraversal(_node* bitree, int nodenum) {
	queue<int> nodeque;
	nodeque.push(0);
	while (!nodeque.empty()) {
		cout << bitree[nodeque.front()].key;
		if (bitree[nodeque.front()].left_index != -1)
			nodeque.push(bitree[nodeque.front()].left_index);
		if (bitree[nodeque.front()].right_index != -1)
			nodeque.push(bitree[nodeque.front()].right_index);
		nodeque.pop();
		if (!nodeque.empty()) cout << ' ';
	}
}

int main() {
	int nodenum, i;

	//input
	cin >> nodenum;
	_node* tree = (_node*)malloc(sizeof(_node) * nodenum);   //the structure
	int* keys = (int*)malloc(sizeof(int) * nodenum);         //N distinct integer keys
	for (i = 0; i < nodenum; i++) 
		cin >> tree[i].left_index >> tree[i].right_index;
	for (i = 0; i < nodenum; i++)
		cin >> keys[i];

	//sort keys in ascending order
	sort(keys, keys + nodenum);

	//traverse twice
	lnr(tree, 0);
	for (i = 0; i < nodenum; i++) {          //assign nodes with corresponding keys
		tree[i].key = keys[tree[i].counter];
	}
	leveltraversal(tree, nodenum);

	free(tree);
	free(keys);
	return 0;
}
