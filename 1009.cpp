//PAT 1009, 2018/2/17

/*
题目描述
According to Wikipedia:
Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. Each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there. It repeats until no input elements remain.

Heap sort divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region. it involves the use of a heap data structure rather than a linear-time search to find the maximum.
Now given the initial sequence of integers, together with a sequence which is a result of several iterations of some sorting method, can you tell which sorting method we are using?

输入描述:
Each input file contains one test case.  For each case, the first line gives a positive integer N (<=100).  Then in the next line, N integers are given as the initial sequence.  The last line contains the partially sorted sequence of the N numbers.  It is assumed that the target sequence is always ascending.  All the numbers in a line are separated by a space.


输出描述:
For each test case, print in the first line either "Insertion Sort" or "Heap Sort" to indicate the method used to obtain the partial result.  Then run this method for one more iteration and output in the second line the resuling sequence.  It is guaranteed that the answer is unique for each test case.  All the numbers in a line must be separated by a space, and there must be no extra space at the end of the line.

输入例子:
10
3 1 2 8 7 5 9 4 6 0
1 2 3 7 8 5 9 4 6 0

输出例子:
Insertion Sort
1 2 3 5 7 8 9 4 6 0

测试用例:
27
8 2 22 14 21 20 24 19 16 5 18 13 10 23 9 11 17 26 3 4 27 25 12 15 1 6 7
17 16 15 14 12 10 13 11 3 7 4 6 5 1 9 2 8 18 19 20 21 22 23 24 25 26 27

对应输出应该为:

Heap Sort
16 14 15 11 12 10 13 8 3 7 4 6 5 1 9 2 17 18 19 20 21 22 23 24 25 26 27

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void swapelem(vector<int>& seq, unsigned int a, unsigned int b) {
	if (a >= seq.size() || b >= seq.size()) return;
	int temp;
	temp = seq[a];
	seq[a] = seq[b];
	seq[b] = temp;
	return;
}

void printseq(const vector<int> seq) {
	unsigned int i;
	for (i = 0; i < seq.size(); i++) {
		cout << seq[i];
		if (i < seq.size() - 1)
			cout << ' ';
	}
	cout << endl;
	return;
}

bool seqcmp(const vector<int> seq1, const vector<int> seq2) {
	unsigned int i;
	if (seq1.size() != seq2.size())
		return false;
	for (i = 0; i < seq1.size(); i++)
		if (seq1[i] != seq2[i])return false;
	return true;
}

void heappop(vector<int>& seq, int last) {
	int max = seq[0];
	seq[0] = seq[last];
	int temp = 0;
	while (temp < last / 2) {
		if (seq[(temp + 1) * 2 - 1] < seq[temp] && seq[(temp + 1) * 2] < seq[temp]) break;
		if (seq[(temp + 1) * 2 - 1] > seq[(temp + 1) * 2]) {
			swapelem(seq, temp, (temp + 1) * 2 - 1);
			temp = (temp + 1) * 2 - 1;
		}
		else if (seq[(temp + 1) * 2 - 1] < seq[(temp + 1) * 2]) {
			swapelem(seq, temp, (temp + 1) * 2);
			temp = (temp + 1) * 2;
		}
	}
	seq[last] = max;
	return;
}

int main() {
	int tempkey, tempnum;  //size: number of integers
	unsigned int size, i;
	bool isinsert = false;
	//input
	cin >> size;
	vector<int> inseq(size);
	vector<int> heseq(size);
	vector<int> targetseq(size);
	for (i = 0; i < size; i++) {
		cin >> tempkey;
		inseq[i] = heseq[i] = tempkey;
	}
	for (i = 0; i < size; i++) {
		cin >> tempkey;
		targetseq[i] = tempkey;
	}
	//insertion
	for (i = 1; i < inseq.size(); i++) {
		tempnum = i;
		while (tempnum - 1 >= 0 && inseq[tempnum - 1] > inseq[tempnum]) {
			swapelem(inseq, tempnum - 1, tempnum);
			tempnum--;
		}
		if (seqcmp(inseq, targetseq)) {
			isinsert = true;
			break;
		}
	}
	if (isinsert) {
		cout << "Insertion Sort\n";
		tempnum = i+1;
		while (tempnum - 1 >= 0 && inseq[tempnum - 1] > inseq[tempnum]) {
			swapelem(inseq, tempnum - 1, tempnum);
			tempnum--;
		}
		printseq(inseq);
	}
	//heap
	else {
		make_heap(heseq.begin(), heseq.end());
		for (i = heseq.size() - 1; i >= 0; i--) {
			heappop(heseq, i);
			if (seqcmp(heseq, targetseq)) break;
		}
		cout << "Heap Sort\n";
		heappop(heseq, i - 1);
		printseq(heseq);
	}
	
	return 0;
}