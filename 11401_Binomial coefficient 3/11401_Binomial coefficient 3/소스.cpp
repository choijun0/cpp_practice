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
#include <cstdio>

using namespace std;
/*
* 페르마의 소정리
* a가 p(소수)의 배수가 아닐때 
* a^(p - 1) % p = 1 = a^(p - 1) --- 1(mod p)
* 합동식의 성질에 따라
* a^(p - 2) --- a^(-1) (mod p) 가성립한다.
* 마쥴러 연산자 성질
* (AB) % p = (A % p * B % p) % p
* (n, r) % p = (n!) % p * ((n - r)! * r!) ^ (p - 2) % p
*/
const long long int Max = 1000000007;
long long int fac[4000001], inv[4000001];
long long int M_Pow(long long int n, long long int v) {
	long long int ret = 1;
	/*
	M_Pow해석 
	여기서 분할정복은 무조건 2등분이다.
	v를 2로 나눠주는건 내려갈수록 2배로 쪼개지기 때문
	시행마다 v가 다음에 쪼개질때 짝수로 쪼개지는지 검사한다. v가 홀수라면 해당 층에 쪼개야하는 수만큼 
	ret에 곱해준다 왜? 해당수를 배재하고 강제로 짝수로 만들었기 때문이다.
	n이 나타내는것은 현재층의 (항수 x 2)를 의미하기도 하기때문에 n을 ret에 곱해주는 것은 배재한 2를 그대로 결과에
	반영되도록 곱해주는 것이다.
	ex) 시행전 n = 2 , v = 7  // v가홀 수임으로 뻬내야할 2의수가 1개임을 의미한다.
	    시행1  n = 4 , v = 3 // v가홀 수임으로  n=4인 것은 뻬내야할 2의수가 2개임을 의미한다. 2 x 2
		시행2  n = 16, v = 1 // v가 1일때는 더이상 분할이 의미가 없음으로 지금까지 쌓아왔던 짝수 제곱항(n)을 곱한다. 
	*/
	while (v > 0) {
		if (v % 2) {
			ret *= n;
			ret %= Max;
		}
		n *= n;
		n %= Max;
		v /= 2;
	}
	return ret;
}
int main()
{
	fac[0] = 1;
	fac[1] = 1;
	for (int i = 2; i <= 4000000; i++) {
		fac[i] = (fac[i - 1] * i) % Max;
	}
	inv[4000000] = M_Pow(fac[4000000], Max - 2);
	for (long long int i = 4000000 - 1; i > 0; i--)
		inv[i] = (inv[i + 1] * (i + 1)) % Max;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	long long int n, k;
	cin >> n >> k;
	if (n == k || !k) {
		cout << 1 << "\n";
		return 0;
	}
	long long int r = (fac[n] * inv[n - k]) % Max;
	r = (r * inv[k]) % Max;
	cout << r << "\n";
	return 0;
}