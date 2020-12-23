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
#define ll long long
using namespace std;

/* -----Use FisanoPeriod -----
//Pisano_Period
// M = 10^k일 때, k>2라면 주기는 15 * 10^(k-1)
const int Period = 1500000;
int fibo[1500001]; 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll n;
	cin >> n;
	fibo[0] = 0;
	fibo[1] = 1;
	for (int i = 2; i <= Period; i++) 
		fibo[i] = (fibo[i - 1] + fibo[i - 2]) % 1000000;
	ll m = n % Period;
	cout << fibo[m] << "\n";
	return 0;
}
*/
//* -----Use DivideConquer
// f(n+2) = f(n+1) + f(n) 
// |f(n+2)| = | 1 1 | x | f(n) |
// |f(n+1)|   | 1 0 |   |f(n+1)|

// |f(n+2)| = | 1 1 | x | 1 1 | x |f(n-1)|  ...............
// |f(n+1)|   | 1 0 |   | 1 0 |   | f(n) |

// |f(n+2)| = | 1 1 |^n x |f(2)|  
// |f(n+1)|   | 1 0 |     |f(1)|
const int Max = 1000000;
ll** Matrix_Multi(ll** op1, ll** op2, ll n) {
	ll** temp = new ll * [n];
	for (int i = 0; i < n; i++) {
		temp[i] = new ll[n];
		for (int j = 0; j < n; j++) temp[i][j] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				temp[i][j] += (op1[i][k] * op2[k][j]) % Max;
				temp[i][j] %= Max;
			}
		}
	}
	return temp;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	//#.1
	ll n;
	cin >> n;
	//#.2
	ll** matrix = new ll * [2];
	ll** temp = new ll * [2];
	for (int i = 0; i < 2; i++) {
		matrix[i] = new ll[2];
		temp[i] = new ll[2];
	}
	matrix[0][0] = 1;
	matrix[0][1] = 1;
	matrix[1][0] = 1;
	matrix[1][1] = 0;

	temp[0][0] = 1;
	temp[0][1] = 0;
	temp[1][0] = 0;
	temp[1][1] = 1;
	//#.3
	while (n > 0) {
		if (n % 2) {
			temp = Matrix_Multi(temp, matrix, 2);
		}
		matrix = Matrix_Multi(matrix, matrix, 2);
		n /= 2;
	}
	ll result = (temp[0][0] + temp[0][1]) - (temp[1][0] + temp[1][1]);
	while (result < 0) result += Max;
	cout << result << "\n";
}