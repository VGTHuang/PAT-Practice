//PAT 1006, 2018/2/14

/*
题目描述
Zhejiang University has 6 campuses and a lot of gates.  From each gate we can collect the in/out times
and the plate numbers of the cars crossing the gate.  Now with all the information available, you are
supposed to tell, at any specific time point, the number of cars parking on campus, and at the end of the day
find the cars that have parked for the longest time period.

输入描述:
Each input file contains one test case.  Each case starts with two positive integers N (<= 10000), 
the number of records, and K (<= 80000) the number of queries.  Then N lines follow, each gives a record in the format
plate_number hh:mm:ss status
where plate_number is a string of 7 English capital letters or 1-digit numbers; 
hh:mm:ss represents the time point in a day by hour:minute:second, with the earliest time being 00:00:00 
and the latest 23:59:59; and status is either in or out.
Note that all times will be within a single day. Each "in" record is paired with the chronologically 
next record for the same car provided it is an "out" record. Any "in" records that are not paired with
an "out" record are ignored, as are "out" records not paired with an "in" record. It is guaranteed that
at least one car is well paired in the input, and no car is both "in" and "out" at the same moment. 
Times are recorded using a 24-hour clock.


Then K lines of queries follow, each gives a time point in the format hh:mm:ss.  Note: the queries 
are given in ascending order of the times.


输出描述:
For each query, output in a line the total number of cars parking on campus.  The last line of output 
is supposed to give the plate number of the car that has parked for the longest time period, and the 
corresponding time length.  If such a car is not unique, then output all of their plate numbers in a 
line in alphabetical order, separated by a space.

输入例子:
16 7
JH007BD 18:00:01 in
    ZD00001 11:30:08 out
DB8888A 13:00:00 out
ZA3Q625 23:59:50 out
ZA133CH 10:23:00 in
    ZD00001 04:09:59 in
JH007BD 05:09:59 in
ZA3Q625 11:42:01 out
  JH007BD 05:10:33 in
ZA3Q625 06:30:50 in
  JH007BD 12:23:42 out
ZA3Q625 23:55:00 in
JH007BD 12:24:23 out
ZA133CH 17:11:22 out
JH007BD 18:07:01 out
DB8888A 06:30:50 in
05:10:00
06:30:50
11:00:00
12:23:42
14:00:00
18:00:00
23:59:00

输出例子:
1
4
5
2
1
0
1
JH007BD ZD00001 07:20:09
*/

//sort of wrong

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;
const int N_max = 10000, K_max = 80000;
enum status { in, out };

struct record {
	string plate_number;
	int time;
	enum status mystat;
	bool valid;
};

int time2int(const string s) {
	return (((int)s[0] - 48) * 10 + ((int)s[1] - 48)) * 3600
		+ (((int)s[3] - 48) * 10 + ((int)s[4] - 48)) * 60
		+ (((int)s[6] - 48) * 10 + ((int)s[7] - 48));
}

void int2time(int i) {
	int hh, mm, ss;
	ss = i % 60;
	i /= 60;
	mm = i % 60;
	i /= 60;
	hh = i % 24;
	if (hh > 9)
		cout << hh << ':';
	else
		cout << '0' << hh << ':';
	if (mm > 9)
		cout << mm << ':';
	else
		cout << '0' << mm << ':';
	if (ss > 9)
		cout << ss;
	else
		cout << '0' << ss;

	return;
}

bool recordcmp(record a, record b) {
	return (a.time < b.time);
}

int main() {
	int N, K, maxtime = 0;
	vector<int> maxcar;
	cin >> N >> K;
	if (N > N_max || K > K_max) return 0;
	vector<struct record> R(N);
	unsigned int i, j;
	string temptime, tempstat;
	for (i = 0; i < N; i++) {
		cin >> R[i].plate_number >> temptime >> tempstat;
		R[i].time = time2int(temptime);
		if (!tempstat.compare("in")) R[i].mystat = in;
		else R[i].mystat = out;
		R[i].valid = false;
	}

	sort(&R[0], &R[0] + R.size(), recordcmp);  //"chronologically"
	
	
	for (i = 0; i < R.size() - 1; i++) {
		if (R[i].mystat == in) {
			for (j = i + 1; j < R.size(); j++) {
				if (!R[i].plate_number.compare(R[j].plate_number)) {
					if (R[j].mystat != R[i].mystat) {
						R[i].valid = R[j].valid = true;  //then this is a valid input
						if ((R[j].time - R[i].time) >= maxtime) {  //also calculate the timespan. Notice the >=
							maxtime = R[j].time - R[i].time;
							maxcar.push_back(i);   //might be more than 1 car with maximum parking time
							
						}
					}
					break;
				}
			}
		}
	}
	/*
	for (i = 0; i < R.size(); i++) {
		cout << R[i].plate_number << ' ' << R[i].time << ' ' << R[i].mystat << ' ' << R[i].valid << endl;
	}
	*/
	//get K lines of time
	int timepoint, currentnum = 0;
	j = 0;
	for (i = 0; i < K; i++) {
		cin >> temptime;
		timepoint = time2int(temptime);
		for (; R[j].time <= timepoint; j++) {    //"Note: the queries are given in ascending order of the times."
			if (R[j].valid && R[j].mystat == in)
				currentnum++;
			else if (R[j].valid && R[j].mystat == out)
				currentnum--;
		}
		cout << currentnum << endl;
	}
	//output maxcar
	for (i = 0; i < maxcar.size(); i++)
		cout << R[maxcar[i]].plate_number << ' ';
	//output maxtime in string form
	int2time(maxtime);

	return 0;
}
