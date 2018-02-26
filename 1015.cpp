//PAT 1015, 2018/2/24

/*
题目描述
It is said that in 2013, there were about 100 graduate schools ready to proceed over 40,000 applications in Zhejiang Province.  It would help a lot if you could write a program to automate the admission procedure.
Each applicant will have to provide two grades: the national entrance exam grade GE, and the interview grade GI.  The final grade of an applicant is (GE + GI) / 2.  The admission rules are:

The applicants are ranked according to their final grades, and will be admitted one by one from the top of the rank list.
If there is a tied final grade, the applicants will be ranked according to their national entrance exam grade GE.  If still tied, their ranks must be the same.
Each applicant may have K choices and the admission will be done according to his/her choices: if according to the rank list, it is one's turn to be admitted; and if the quota of one's most preferred shcool is not exceeded, then one will be admitted to this school, or one's other choices will be considered one by one in order. If one gets rejected by all of preferred schools, then this unfortunate applicant will be rejected.
If there is a tied rank, and if the corresponding applicants are applying to the same school, then that school must admit all the applicants with the same rank, even if its quota will be exceeded.

输入描述:
Each input file contains one test case.  Each case starts with a line containing three positive integers: N (<=40,000), the total number of applicants; M (<=100), the total number of graduate schools; and K (<=5), the number of choices an applicant may have.
In the next line, separated by a space, there are M positive integers.  The i-th integer is the quota of the i-th graduate school respectively.
Then N lines follow, each contains 2+K integers separated by a space.  The first 2 integers are the applicant's GE and GI, respectively.  The next K integers represent the preferred schools.  For the sake of simplicity, we assume that the schools are numbered from 0 to M-1, and the applicants are numbered from 0 to N-1.


输出描述:
For each test case you should output the admission results for all the graduate schools.  The results of each school must occupy a line, which contains the applicants' numbers that school admits.  The numbers must be in increasing order and be separated by a space.  There must be no extra space at the end of each line.  If no applicant is admitted by a school, you must output an empty line correspondingly.

输入例子:
11 6 3
2 1 2 2 2 3
100 100 0 1 2
60 60 2 3 5
100 90 0 3 4
90 100 1 2 0
90 90 5 1 3
80 90 1 0 2
80 80 0 1 2
80 80 0 1 2
80 70 1 3 2
70 80 1 2 3
100 100 0 2 4

输出例子:
0 10
3
5 6 7
2 8

1 4

测试用例:
20 3 3
4 7 8
5 3 1 1 0
9 1 2 1 2
9 3 1 0 0
2 6 2 2 0
9 2 2 2 1
7 5 2 0 0
8 9 0 1 1
1 2 0 0 0
9 4 1 2 2
5 0 2 1 1
0 6 0 2 2
6 1 0 0 2
7 6 2 1 0
3 7 0 0 0
5 4 0 2 2
3 0 1 0 0
8 8 0 0 2
4 9 0 0 2
8 9 1 1 0
4 9 0 1 2

对应输出应该为:

6 16 17 19
0 2 8 9 15 18
1 3 4 5 10 11 12 14
*/

//messy; passed all but one test

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct student {
	int index;
	int GE;
	int GI;
	float FG;  // debug: this needs to be float
	int rank;
	vector<int> school;
};

struct school {
	int quota;
	vector<int> graduate;
};

int N, M, K;
vector<school> university;
vector<student> graduate;

bool cmpgrade(student s1, student s2) {
	return(s1.FG > s2.FG || (s1.FG == s2.FG && s1.GE > s2.GE));
}

void rankstudent() {
	sort(graduate.begin(), graduate.end(), cmpgrade);
	int temprank = 0;
	for (unsigned i = 0; i < graduate.size(); i++) {
		graduate[i].rank = temprank;
		if (i < graduate.size() - 1) {
			if (graduate[i].FG == graduate[i + 1].FG && graduate[i].GE == graduate[i + 1].GE); //tied
			else temprank++;
		}
	}
}

int choosemyschool(const int thisgrad) {
	int i = 0;
	while (i < K) {
		if (university[graduate[thisgrad].school[i]].quota
			>
			university[graduate[thisgrad].school[i]].graduate.size()) 
			return graduate[thisgrad].school[i];
		i++;
	}
	return -1;  //rejected
}

void getadmission() {
	int thisgrad, myschool;
	for (thisgrad = 0; thisgrad < graduate.size(); thisgrad++) {
		myschool = choosemyschool(thisgrad);
		if (myschool == -1) continue;     // thisgrad is rejected
		else {   // thisgrad is admitted to myschool but needs to compare with other grads with tied ranks
			int tiedcount = 1;
			while (thisgrad + tiedcount < graduate.size()
				&& graduate[thisgrad].rank == graduate[thisgrad + tiedcount].rank //tied rank
				&& choosemyschool(thisgrad) == choosemyschool(thisgrad + tiedcount)
				)
				tiedcount++;
			for (unsigned int j = thisgrad; j < thisgrad + tiedcount; j++) {
				university[myschool].graduate.push_back(graduate[j].index);
			}
			thisgrad = thisgrad + tiedcount - 1;
		}
	}
	//sort grads in ascending order
	for (unsigned i = 0; i < university.size(); i++) {
		sort(university[i].graduate.begin(), university[i].graduate.end());
	}
}

void printadmission() {
	for (unsigned int i = 0; i < university.size(); i++) {
		for (unsigned int j = 0; j < university[i].graduate.size(); j++) {
			cout << university[i].graduate[j];
			if (j < university[i].graduate.size() - 1) cout << ' ';
		}
		cout << endl;
	}
}

int main() {
	//input
	unsigned int i, j;
	cin >> N >> M >> K;
	university.resize(M);
	for (i = 0; i < M; i++) {
		cin >> university[i].quota;
	}
	graduate.resize(N);
	for (i = 0; i < N; i++) {
		graduate[i].index = i;
		cin >> graduate[i].GE >> graduate[i].GI;
		graduate[i].FG = (graduate[i].GE + graduate[i].GI) / 2.0;
		graduate[i].school.resize(K);
		for (j = 0; j < K; j++) {
			
			cin >> graduate[i].school[j];
		}
	}
	//logic
	rankstudent();
	getadmission();
	printadmission();

	return 0;
}
