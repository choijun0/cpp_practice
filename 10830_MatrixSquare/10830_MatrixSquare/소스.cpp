#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <vector>
#include <set>
#include <sstream>

using namespace std;
const int Max = 1000;
int** Matrix_Square(int** a, int** b ,int n, int r, int m) {
	//#.1
	int** result_Matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		result_Matrix[i] = new int[m];
		for (int j = 0; j < m; j++)
			result_Matrix[i][j] = 0;
	}
	//#.2
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < r; k++) {
				result_Matrix[i][j] += (a[i][k] * b[k][j]);
			}
			result_Matrix[i][j] %= Max;
		}
	}
	return result_Matrix;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int N;
	long long int B;
	cin >> N >> B;
	//#.1
	int** A = new int* [N];
	int** ret = new int* [N];
	for (int i = 0; i < N; i++) {
		A[i] = new int[N];
		ret[i] = new int[N];
		for (int j = 0; j < N; j++) {
			A[i][j] = 0;
			if (i == j) ret[i][j] = 1;
			else ret[i][j] = 0;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> A[i][j];
		}
	}
	//#.2
	while (B > 0) {
		if (B % 2) {
			ret = Matrix_Square(ret, A, N, N, N);
		}
		A = Matrix_Square(A, A, N, N, N);
		B /= 2;
	}
	//#.3 Print
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << ret[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
	return 0;
}