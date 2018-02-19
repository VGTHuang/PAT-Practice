//PAT 1012, 2018/2/20

/*
题目描述
The Japanese language is notorious for its sentence ending particles. Personal preference of such particles can be considered as a reflection of the speaker's personality. Such a preference is called "Kuchiguse" and is often exaggerated artistically in Anime and Manga. For example, the artificial sentence ending particle "nyan~" is often used as a stereotype for characters with a cat-like personality:
Itai nyan~ (It hurts, nyan~)
Ninjin wa iyada nyan~ (I hate carrots, nyan~)

Now given a few lines spoken by the same character, can you find her Kuchiguse?

输入描述:
Each input file contains one test case.  For each case, the first line is an integer N (2<=N<=100). Following are N file lines of 0~256 (inclusive) characters in length, each representing a character's spoken line. The spoken lines are case sensitive.


输出描述:
For each test case, print in one line the kuchiguse of the character, i.e., the longest common suffix of all N lines. If there is no such suffix, write "nai".

输入例子:
3
Itai nyan~
Ninjin wa iyadanyan~
uhhh nyan~

输出例子:
nyan~
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int ReverseLine_Len(string& s) {   // reverse line & return line's length
	int len, tempchar, tempnum;
	for (len = 0; s[len] != '\0'; len++);     // strlen() doesn't work on their complier?
	for (tempnum = 0; tempnum < len / 2; tempnum++) {
		tempchar = s[tempnum];
		s[tempnum] = s[len - 1 - tempnum];
		s[len - 1 - tempnum] = tempchar;
	}
	return len;
}

int main() {
	int linenum, i;
	// input
	cin >> linenum;
	cin.ignore(100, '\n');
	vector<string> line(linenum);     // store lines
	vector<int> linelen(linenum);     // store lengths of each line
	for (i = 0; i < linenum; i++) {
		getline(cin, line[i]);
		linelen[i] = ReverseLine_Len(line[i]);
	}
	// find kuchiguse
	vector<char> kuchiguse;
	bool flag = true;
	int charlen = 0;
	while (flag == true) {
		for (i = 0; i < linenum - 1; i++) {
			if (line[i][charlen] != line[i + 1][charlen])
				flag = false;
		}
		if (!flag)
			break;
		else {
			kuchiguse.push_back(line[0][charlen]);
			charlen++;
		}
	}
	if (kuchiguse.size() == 0)
		cout << "nai";

	else
		for (i = kuchiguse.size() - 1; i >= 0; i--)
			cout << kuchiguse[i];

	return 0;
}