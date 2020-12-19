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

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int R, C;
	queue<pair<int, int>> water_Queue;
	vector<pair<int, int>> swan;
	char** map;
	bool** visit;
	cin >> R >> C;
	//#.1
	map = new char* [R];
	visit = new bool* [R];
	for (int i = 0; i < R; i++) {
		map[i] = new char[C];
		visit[i] = new bool[C];
	}
	//#.2
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> map[i][j];
			visit[i][j] = false;
			if (map[i][j] == '.' || map[i][j] == 'L') {
				water_Queue.push(make_pair(i, j));
			}
			if (map[i][j] == 'L') {
				swan.push_back(make_pair(i, j));
			}
		}
	}
	//#.3 
	int rate_Of_Day = 0;
	int A[4] = { 0,0,1,-1 };
	int B[4] = { 1,-1,0,0 };
	queue<pair<int, int>> swan_q;
	swan_q.push(swan[0]);
	bool isFind = false;
	while (true) {
		//#.1 Search
		queue<pair<int, int>> water_Adjacent_ice; //날마다 초기화
		while (!swan_q.empty()) {
			int n = swan_q.front().first;
			int m = swan_q.front().second;
			swan_q.pop();
			if (n == swan[1].first && m == swan[1].second) {
				isFind = true;
				break;
			}
			for (int i = 0; i < 4; i++) {
				int temp_N = n + A[i];
				int temp_M = m + B[i];
				if (temp_N < 0 || temp_N >= R || temp_M < 0 || temp_M >= C || visit[temp_N][temp_M]) continue;
				visit[temp_N][temp_M] = true;
				if (map[temp_N][temp_M] == 'X') {
					water_Adjacent_ice.push(make_pair(temp_N, temp_M));
					continue;
				}
				swan_q.push(make_pair(temp_N, temp_M));
			}
		}
		if (isFind) {
			break;
		}
		swan_q = water_Adjacent_ice;

		//#.2 MeltingIce
		int waterQSize = water_Queue.size();
		while (waterQSize--) {
			int n = water_Queue.front().first;
			int m = water_Queue.front().second;
			water_Queue.pop();
			for (int i = 0; i < 4; i++) {
				int temp_N = n + A[i];
				int temp_M = m + B[i];
				if (temp_N < 0 || temp_N >= R || temp_M < 0 || temp_M >= C) continue;
				if (map[temp_N][temp_M] == 'X') {
					map[temp_N][temp_M] = '.';
					water_Queue.push(make_pair(temp_N, temp_M));
				}
			}
		}
		rate_Of_Day++;
	}
	cout << rate_Of_Day << "\n";
	return 0;
}