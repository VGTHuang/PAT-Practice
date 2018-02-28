//PAT 1017, 2018/2/27

/*
题目描述
Stack is one of the most fundamental data structures, which is based on the principle of Last In First Out (LIFO).  The basic operations include Push (inserting an element onto the top position) and Pop (deleting the top element).  Now you are supposed to implement a stack with an extra operation: PeekMedian -- return the median value of all the elements in the stack.  With N elements, the median value is defined to be the (N/2)-th smallest element if N is even, or ((N+1)/2)-th if N is odd.

输入描述:
Each input file contains one test case.  For each case, the first line contains a positive integer N (<= 105).  Then N lines follow, each contains a command in one of the following 3 formats:

Push key
Pop
PeekMedian

where key is a positive integer no more than 105.


输出描述:
For each Push command, insert key into the stack and output nothing.  For each Pop or PeekMedian command, print in a line the corresponding returned value.  If the command is invalid, print "Invalid" instead.

输入例子:
17
Pop
PeekMedian
Push 3
PeekMedian
Push 2
PeekMedian
Push 1
PeekMedian
Pop
Pop
Push 5
Push 4
PeekMedian
Pop
Pop
Pop
Pop

输出例子:
Invalid
Invalid
3
2
2
1
2
4
4
5
3
Invalid
*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N;
vector<string> cmd;
vector<int> stack;
queue<int> numque;

int getMedian() {
	vector<int>temp;
	temp.assign(stack.begin(), stack.end());
	sort(temp.begin(), temp.end());
	int mednum = temp[temp.size()/2];
	for (int i = 0; i < stack.size(); i++) {
		if (stack[i] == mednum) return i;
	}
	return 0;
}

void executeInvalid() {
	cout << "Invalid" << endl;
}

void executePush() {
	int temp = numque.front();
	numque.pop();
	stack.push_back(temp);
	return;
}

void executePop() {
	if (stack.empty()) {
		cout << "Invalid\n";
		return;
	}
	cout << *(stack.end() - 1) << endl;
	stack.erase(stack.end() - 1);
	return;
}
			
void executPeekMedian() {
	if (stack.empty()) {
		cout << "Invalid\n";
		return;
	}
	cout << stack[getMedian()] << endl;
	return;
}



void executeCmd() {
	for (int i = 0; i < N; i++) {
		if (cmd[i].compare("PeekMedian") == 0)
			executPeekMedian();
		else if (cmd[i].compare("Pop") == 0)
			executePop();
		else if (cmd[i].compare(0, 5, "Push ") == 0)
			executePush();
		else
			executeInvalid();
	}
}

int main() {
	int i;
	string tempstring;
	getline(cin, tempstring);
	N = stoi(tempstring, 0);
	cmd.resize(N);

	for (i = 0; i < N; i++) {
		getline(cin, tempstring);
		cmd[i] = tempstring;
		if (tempstring.compare(0, 5, "Push ") == 0) {
			numque.push(stoi(tempstring.substr(5, 10),nullptr));
		}
	}
	
	executeCmd();
	
	return 0;
}