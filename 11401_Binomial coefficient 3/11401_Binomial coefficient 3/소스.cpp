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
* �丣���� ������
* a�� p(�Ҽ�)�� ����� �ƴҶ� 
* a^(p - 1) % p = 1 = a^(p - 1) --- 1(mod p)
* �յ����� ������ ����
* a^(p - 2) --- a^(-1) (mod p) �������Ѵ�.
* ���췯 ������ ����
* (AB) % p = (A % p * B % p) % p
* (n, r) % p = (n!) % p * ((n - r)! * r!) ^ (p - 2) % p
*/
const long long int Max = 1000000007;
long long int fac[4000001], inv[4000001];
long long int M_Pow(long long int n, long long int v) {
	long long int ret = 1;
	/*
	M_Pow�ؼ� 
	���⼭ ���������� ������ 2����̴�.
	v�� 2�� �����ִ°� ���������� 2��� �ɰ����� ����
	���ึ�� v�� ������ �ɰ����� ¦���� �ɰ������� �˻��Ѵ�. v�� Ȧ����� �ش� ���� �ɰ����ϴ� ����ŭ 
	ret�� �����ش� ��? �ش���� �����ϰ� ������ ¦���� ������� �����̴�.
	n�� ��Ÿ���°��� �������� (�׼� x 2)�� �ǹ��ϱ⵵ �ϱ⶧���� n�� ret�� �����ִ� ���� ������ 2�� �״�� �����
	�ݿ��ǵ��� �����ִ� ���̴�.
	ex) ������ n = 2 , v = 7  // v��Ȧ �������� �������� 2�Ǽ��� 1������ �ǹ��Ѵ�.
	    ����1  n = 4 , v = 3 // v��Ȧ ��������  n=4�� ���� �������� 2�Ǽ��� 2������ �ǹ��Ѵ�. 2 x 2
		����2  n = 16, v = 1 // v�� 1�϶��� ���̻� ������ �ǹ̰� �������� ���ݱ��� �׾ƿԴ� ¦�� ������(n)�� ���Ѵ�. 
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