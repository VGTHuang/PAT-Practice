//PAT 1004, 2018/2/14

/*
题目描述
One important factor to identify acute stroke (急性脑卒中) is the volume of the stroke core. 
Given the results of image analysis in which the core regions are identified in each MRI slice, 
your job is to calculate the volume of the stroke core.

输入描述:
Each input file contains one test case.  For each case, the first line contains 4 positive integers: 
M, N, L and T, where M and N are the sizes of each slice (i.e. pixels of a slice are in an M by N matrix, 
and the maximum resolution is 1286 by 128); L (<=60) is the number of slices of a brain; and T is the 
integer threshold (i.e. if the volume of a connected core is less than T, then that core must not be counted).

Then L slices are given.  Each slice is represented by an M by N matrix of 0's and 1's, where 
1 represents a pixel of stroke, and 0 means normal.  Since the thickness of a slice is a constant, 
we only have to count the number of 1's to obtain the volume.  However, there might be several 
separated core regions in a brain, and only those with their volumes no less than T are counted. 
Two pixels are "connected" and hence belong to the same region if they share a common side, as shown 
by Figure 1 where all the 6 red pixels are connected to the blue one.



Figure 1


输出描述:
For each case, output in a line the total volume of the stroke core.

输入例子:
3 4 5 2
1 1 1 1
1 1 1 1
1 1 1 1
0 0 1 1
0 0 1 1
0 0 1 1
1 0 1 1
0 1 0 0
0 0 0 0
1 0 1 1
0 0 0 0
0 0 0 0
0 0 0 1
0 0 0 1
1 0 0 0

输出例子:
26
*/

//simple approach, might cause overflow

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

const unsigned int M_max = 1286, N_max = 128, L_max = 60;

class Brain {
private:
	struct pix {
		bool visited;
		bool stroke;
	};
	unsigned short int M, N, L, T;
	pix *** pixel;
	unsigned short int volume;
public:
	vector<int> core;    //size = how many cores there are; if core[i] > T, then the core is valid
	Brain(unsigned short int m, unsigned short int n, unsigned short int l, unsigned short int t) :
		M(m), N(n), L(l), T(t) {
		pixel = (pix***)malloc(L * sizeof(pix**));
		unsigned short int i, j;
		for (i = 0; i < L; i++) {
			pixel[i] = (pix**)malloc(M * sizeof(pix*));
			for (j = 0; j < M; j++)
				pixel[i][j] = (pix*)malloc(N * sizeof(pix));
		}
	}
	void Init(void);
	void Print(void);
	void Search(void);
	void DFS(int l, int m, int n);
	void Outputvol(void);
};

void Brain::Init(void) {
	unsigned short int l, m, n;
	bool tempstroke;
	for (l = 0; l < L; l++) {
		for (m = 0; m < M; m++) {
			for (n = 0; n < N; n++) {
				cin >> tempstroke;
				pixel[l][m][n].stroke = tempstroke;
				pixel[l][m][n].visited = false;   //no pixel has been visited
			}
		}
	}
}

void Brain::Print(void) {  //test if input is corrent
	unsigned short int l, m, n;
	for (l = 0; l < L; l++) {
		for (m = 0; m < M; m++) {
			for (n = 0; n < N; n++) {
				cout << pixel[l][m][n].visited << ' ';
			}
			cout << endl;
		}
		cout << "\n\n";
	}
}

void Brain::Search(void) {
	int l, m, n;
	for (l = 0; l < L; l++)
		for (m = 0; m < M; m++)
			for (n = 0; n < N; n++) {
				if (pixel[l][m][n].visited == 1 || pixel[l][m][n].stroke == 0); //if this pixel is either visited or ==0
				else {
					core.push_back(0);   //apparently a new core is found
					DFS(l, m, n);
				}
			}
}

void Brain::DFS(int l, int m, int n) {
	if (l < 0 || n < 0 || m < 0 || l >= L || m >= M || n >= N) return;   //out of pixel's boundary
	if (pixel[l][m][n].visited == true || pixel[l][m][n].stroke == false) return;       //this pixel has been visited or == 0
	core.back()++;
	pixel[l][m][n].visited = true;      //visit this pixel
	DFS(l - 1, m, n);
	DFS(l + 1, m, n);
	DFS(l, m - 1, n);
	DFS(l, m + 1, n);
	DFS(l, m, n - 1);
	DFS(l, m, n + 1);
	return;
}

void Brain::Outputvol(void) {
	unsigned int i, vol = 0;
	for (i = 0; i < core.size(); i++) {
		if (core[i] >= T)
			vol += core[i];
	}
	cout << vol;     //volumn is the sum of every core with a volumn equal to or greater than T
}

int main() {
	unsigned short int m, n, l, t;
	cin >> m >> n >> l >> t;
	if (m > M_max || n > N_max || l > L_max) return 0;   //check boundary

	Brain B(m, n, l, t);
	B.Init();
	B.Search();

	B.Outputvol();
	return 0;
}
