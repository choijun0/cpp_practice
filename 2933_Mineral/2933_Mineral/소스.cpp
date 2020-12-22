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
string cave[100];
int A[4] = { 1,-1, 0, 0 };
int B[4] = { 0,0,1,-1 };
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int R, C, N;
	//#.1
	cin >> R >> C;
	for (int i = 0; i < R; i++)
		cin >> cave[i];
	//#.2
	cin >> N;
	for (int i = 0; i < N; i++) {
		int height;
		cin >> height;
		height = (R - height);
		queue<pair<int, int>>adjacent_Q;
		//#.2-1 Delete_Mineral
		if (i % 2) {
			for (int k = C - 1; k >= 0; k--) {
				if (cave[height][k] == 'x') {
					cave[height][k] = '.';
					for (int c = 0; c < 4; c++) {
						int n = height + A[c];
						int m = k + B[c];
						if (n < 0 || n >= R || m < 0 || m >= C || cave[n][m] == '.')
							continue;
						adjacent_Q.push(make_pair(n, m));
					}
					break;
				}
			}
		}
		else {
			for (int k = 0; k < C; k++) {
				if (cave[height][k] == 'x') {
					cave[height][k] = '.';
					for (int c = 0; c < 4; c++) {
						int n = height + A[c];
						int m = k + B[c];
						if (n < 0 || n >= R || m < 0 || m >= C || cave[n][m] == '.')
							continue;
						adjacent_Q.push(make_pair(n, m));
					}
					break;
				}
			}
		}
		//#.2-2 Move_Mineral
		while (!adjacent_Q.empty()) {
			bool visit[100][100] = { false };
			queue<pair<int, int>>search_Q; //탐색할 미네랄
			search_Q.push(adjacent_Q.front());
			adjacent_Q.pop();
			vector<pair<int, int>>move_V; //움직여야할 클러스트터 집합
			visit[search_Q.front().first][search_Q.front().second] = true;
			//클러스터 집합을 저장한다.
			while (!search_Q.empty()) {
				int n = search_Q.front().first;
				int m = search_Q.front().second;
				search_Q.pop();
				move_V.push_back(make_pair(n, m));
				for (int c = 0; c < 4; c++) {
					int tn = n + A[c];
					int tm = m + B[c];
					if (tn < 0 || tn >= R || tm < 0 || tm >= C || visit[tn][tm] || cave[tn][tm] == '.')
						continue;
					visit[tn][tm] = true;
					search_Q.push(make_pair(tn, tm));
				}
			}
			//#.1 Check
			bool can_Move = true;
			int move_Distance = 1;
			while (can_Move) {
				for (int c = 0; c < move_V.size(); c++) {
					int n = move_V[c].first + move_Distance;
					int m = move_V[c].second;
					if (n == R || (!visit[n][m] && cave[n][m] == 'x')) {
						//바닥뚫음 or 미네랄인 동시에 방문하지 않은곳 = 다른 클러스터 -> 이동불가
						move_Distance--;
						can_Move = false;
						break;
					}
				}
				if (can_Move) move_Distance++;
			}
			if (move_Distance >= 1) {
				//#.2 Move
				for (int c = 0; c < move_V.size(); c++) {
					int n = move_V[c].first;
					int m = move_V[c].second;
					cave[n][m] = '.';
				}
				for (int c = 0; c < move_V.size(); c++) {
					int n = move_V[c].first + move_Distance;
					int m = move_V[c].second;
					cave[n][m] = 'x';
				}
				break; //오직 하나의 클러스터만 움직인다는게 조건이다.
				       //민약 한번의 클라스터 이동이 다른 인접한 미네랄의 이동에 관여할경우
				       //다음 인접한 미네랄 이동시 그자리에 인접한 미네랄이 아닌 다른 데이터가 들어갈수있다
				       //따라서 한번이동후 break를 해줘야한다.
			}
		}
	}
	//#.3 Print
	for (int aa = 0; aa < R; aa++) {
		cout << cave[aa] << "\n";
	}
	return 0;
}