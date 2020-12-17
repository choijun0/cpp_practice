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
int A[4] = { 0,0,-1,1 };
int B[4] = { 1,-1,0,0 };
using namespace std;
class Token 
{
private:
	int index;
	int n, m;
	int direction; //0-Right 1-Left 2-Up 3-Down
	Token* down_Token;
	Token* up_Token;
public:
	Token(int index, int n, int m, int direction) {
		this->index = index;
		this->n = n;
		this->m = m;
		this->direction = direction;
		//업혀저있는 입력은 주어지지 않음.
		down_Token = NULL;
		up_Token = NULL;
	}
	void Move(int*** map, int N,vector<Token>* token_List, bool is_Second_Move = false) {
		//#.0 블루이동 or 이탈 체크
		int temp_N = n + A[direction];
		int temp_M = m + B[direction];
		if (temp_N <0 || temp_N >= N || temp_M <0 || temp_M >= N || map[temp_N][temp_M][0] == 2)
		{
			if (is_Second_Move == true) return; //두번째이동인 동시에 해당조건을 만족한다면 뭠춘다.
			//방향변경 다시 움직임시도
			Reverse_Direction();
			Move(map, N, token_List, true);
			return;
		}
		//#.1 현재있는 칸에 자신이 가장아래있는지 체크
		if (down_Token == NULL) 
		{
			map[n][m][1] = -1; //현재 칸을 비워준다.
		}
		else 
		{
			this->down_Token->up_Token = NULL; //아래토큰의 Up토큰을 비워줌
			map[n][m][1] = this->down_Token->index; //바로 아래토큰이 가장위 토큰임
			this->down_Token = NULL; //자신의 아래토큰을 비워줌
		}
		//#.2 자신과 자신위에 있는 모든 토큰을 이동
		Token* move_Token = this;
		while (move_Token != NULL) {
			move_Token->n += A[direction];
			move_Token->m += B[direction];
			move_Token = move_Token->up_Token;
		}
		//#.3 Red이동 White이동 체크
		if (map[n][m][1] != -1) //이미토큰이 존재할때
		{
			if (map[n][m][0] == 0) { //White
				//그대로 쌓는다.
				((*token_List)[map[n][m][1]]).up_Token = this;
				this->down_Token = &((*token_List)[map[n][m][1]]);
			}
			else { //Red
				Token* under_Token = Reverse();
				((*token_List)[map[n][m][1]]).up_Token = under_Token;
				under_Token->down_Token = &((*token_List)[map[n][m][1]]);
			}
		}
		else {
			if (map[n][m][0] == 1) {
				Token* under_Token = Reverse(); 
			}
		}
		//#.3-1 가장 위엤는 토큰을 찾는다.
		Token* top_Token = this;
		while (top_Token->up_Token != NULL) {
			top_Token = top_Token->up_Token;
		}
		//#.3-2 값을 바꾼다.
		map[n][m][1] = top_Token->index;
	}
	Token* Reverse()
	{
		Token* next_Token = up_Token;
		//#.1 Reverse
		Token* temp_Token = up_Token;
		up_Token = down_Token;
		down_Token = temp_Token;
		//#.2 다음 토큰도 뒤집어준다.
		if (next_Token != NULL) {
			return next_Token->Reverse();
		}
		else return this;
	}
	void Reverse_Direction() {
		switch (this->direction) {
		case 0:
			this->direction = 1;
			break;
		case 1:
			this->direction = 0;
			break;
		case 2:
			this->direction = 3;
			break;
		case 3:
			this->direction = 2;
			break;
		}
	}
	int Check_Children() {
		if (down_Token != NULL) return -1;
		Token* cur_Token = this;
		int token_Count = 1;
		while (cur_Token->up_Token != NULL) {
			token_Count++;
			cur_Token = cur_Token->up_Token;
		}
		return token_Count;
	}
};
bool Ceck_Turn_Over(vector<Token>* Token_List);
int Start_Turn(int*** map, int N, vector<Token>* Token_List)
{
	int turn_Count = 0;
	if (Ceck_Turn_Over(Token_List)) return turn_Count;
	while (turn_Count < 1000) {
		turn_Count++;
		for (int i = 0; i < (*Token_List).size(); i++)
		{
			(*Token_List)[i].Move(map, N, Token_List);
			if (Ceck_Turn_Over(Token_List)) return turn_Count;
		}
	}
	return -1;
}
bool Ceck_Turn_Over(vector<Token>* Token_List)
{
	for (int i = 0; i < (*Token_List).size(); i++) {
		if ((*Token_List)[i].Check_Children() >= 4) {
			return true;
		}
	}
	return false;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N, K;
	cin >> N >> K; //4 ≤ N ≤ 12 4 ≤ K ≤ 10
	int*** map = new int** [N];
	for (int i = 0; i < N; i++) {
		map[i] = new int* [N];
		for (int j = 0; j < N; j++) {
			map[i][j] = new int[2];
		}
	}
	//#.1 SetMap
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j][0];
			map[i][j][1] = -1;
		}
	}
	//#.2 SetToken
	vector<Token> Token_List;
	for (int i = 0; i < K; i++) {
		int n, m, d;
		cin >> n >> m >> d;
		map[n - 1][m - 1][1] = i;
		Token_List.push_back(*(new Token(i, (n - 1), (m - 1), (d - 1))));
	}
	//#.3 StartTurn
	cout << Start_Turn(map, N, &Token_List) << endl;
	return 0;
}