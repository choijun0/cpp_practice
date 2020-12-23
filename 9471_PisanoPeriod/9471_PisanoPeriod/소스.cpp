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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int P;
	cin >> P;
	for (int i = 0; i < P; i++) {
		int N;
		int M;
		cin >> N >> M;
		ll n1 = 1;
		ll n2 = 1;
		int index = 3;
		bool trigger = false;
		while (true) {
			ll n3 = (n1 + n2) % M;
			if (trigger) {
				if (n3 == 1) {
					break;
				}
				else 
					trigger = false;
			}
			if (n3 == 1) trigger = true;
			n1 = n2;
			n2 = n3;
			index++;
		}
		cout << N << " " << index - 2 << "\n";
	}

	return 0;
}