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
enum class Adjacent_Side //방향은 중앙에있는 면기준이다.
{
	Up,
	Down,
	Left,
	Right,
	UpR,
	DownR,
	LeftR,
	RightR
};
enum class Turn_Direction 
{
	Clock, UnClock
};
class Adjacent_Data;
class Cube
{
private:
	char** side_Data;
	Adjacent_Data* adj_Cube;
public:
	Cube(char** side_Data);
	friend ostream& operator << (ostream& o, const Cube& pT);
	void Set_Adj_Cube(Adjacent_Data* adj_d);
	void turn(Turn_Direction turn_Direction);
	friend class Adjacent_Data;
};
class Adjacent_Data
{
private:
	Cube* cube;
	Adjacent_Side adj_Side;
public:
	Adjacent_Data(Cube* cube = NULL, Adjacent_Side adj_side = Adjacent_Side::Up)
	{
		this->cube = cube;
		this->adj_Side = adj_side;
	}
	Adjacent_Data operator= (Adjacent_Data* op1);
	friend class Cube;
};
Adjacent_Data Adjacent_Data::operator= (Adjacent_Data* op1)
{
	this->cube = op1->cube;
	this->adj_Side = op1->adj_Side;
	return *this;
}
Cube::Cube(char** side_Data) {
	this->side_Data = side_Data;
}
ostream& operator << (ostream& o, const Cube& pT)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			o << pT.side_Data[i][j];
		}
		if (i < 2) o << endl;
	}
	return o;
}
void Cube::Set_Adj_Cube(Adjacent_Data* adj_d)
{
	adj_Cube = new Adjacent_Data[4];
	for (int i = 0; i < 4; i++)
		adj_Cube[i] = adj_d[i];
}
void Cube::turn(Turn_Direction turn_Direction) 
{
	queue<char> temp_Value;
	//#.1 데이터 입력
	for (int i = 0; i < 4; i++)
	{
		char** temp_Side_Data;
		switch (adj_Cube[i].adj_Side)
		{
		case Adjacent_Side::Up:
			temp_Side_Data = adj_Cube[i].cube->side_Data;
			temp_Value.push(temp_Side_Data[0][0]);
			temp_Value.push(temp_Side_Data[0][1]);
			temp_Value.push(temp_Side_Data[0][2]);
			break;
		case Adjacent_Side::Right:
			temp_Side_Data = adj_Cube[i].cube->side_Data;
			temp_Value.push(temp_Side_Data[0][2]);
			temp_Value.push(temp_Side_Data[1][2]);
			temp_Value.push(temp_Side_Data[2][2]);
			break;
		case Adjacent_Side::Down:
			temp_Side_Data = adj_Cube[i].cube->side_Data;
			temp_Value.push(temp_Side_Data[2][0]);
			temp_Value.push(temp_Side_Data[2][1]);
			temp_Value.push(temp_Side_Data[2][2]);
			break;
		case Adjacent_Side::Left:
			temp_Side_Data = adj_Cube[i].cube->side_Data;
			temp_Value.push(temp_Side_Data[0][0]);
			temp_Value.push(temp_Side_Data[1][0]);
			temp_Value.push(temp_Side_Data[2][0]);
			break;
		case Adjacent_Side::UpR:
			temp_Side_Data = adj_Cube[i].cube->side_Data;
			temp_Value.push(temp_Side_Data[0][2]);
			temp_Value.push(temp_Side_Data[0][1]);
			temp_Value.push(temp_Side_Data[0][0]);
			break;
		case Adjacent_Side::RightR:
			temp_Side_Data = adj_Cube[i].cube->side_Data;
			temp_Value.push(temp_Side_Data[2][2]);
			temp_Value.push(temp_Side_Data[1][2]);
			temp_Value.push(temp_Side_Data[0][2]);
			break;
		case Adjacent_Side::DownR:
			temp_Side_Data = adj_Cube[i].cube->side_Data;
			temp_Value.push(temp_Side_Data[2][2]);
			temp_Value.push(temp_Side_Data[2][1]);
			temp_Value.push(temp_Side_Data[2][0]);
			break;
		case Adjacent_Side::LeftR:
			temp_Side_Data = adj_Cube[i].cube->side_Data;
			temp_Value.push(temp_Side_Data[2][0]);
			temp_Value.push(temp_Side_Data[1][0]);
			temp_Value.push(temp_Side_Data[0][0]);
			break;
		}
	}
	//#.2 회전
	if (turn_Direction == Turn_Direction::Clock) //순행 회전
	{
		//#.2-1 Turn itself
		char* temp_Side_char = new char[8]
		{   side_Data[0][0],
			side_Data[0][1],
			side_Data[0][2],
			side_Data[1][2],
			side_Data[2][2],
			side_Data[2][1],
			side_Data[2][0],
			side_Data[1][0],
		};
		side_Data[0][0] = temp_Side_char[6];
	    side_Data[0][1] = temp_Side_char[7];
		side_Data[0][2] = temp_Side_char[0];
		side_Data[1][2] = temp_Side_char[1];
		side_Data[2][2] = temp_Side_char[2];
		side_Data[2][1] = temp_Side_char[3];
		side_Data[2][0] = temp_Side_char[4];
		side_Data[1][0] = temp_Side_char[5];
		delete temp_Side_char;
		//#.2-2 Adjacent Cube Turning
		for (int i = 1; ; i++)
		{
			char** temp_Side_Data;
			if (i == 4) i = 0;
			switch (adj_Cube[i].adj_Side)
			{
			case Adjacent_Side::Up:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 0; j < 3; j++) {
					temp_Side_Data[0][j] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::Right:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 0; j < 3; j++) {
					temp_Side_Data[j][2] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::Down:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 0; j < 3; j++) {
					temp_Side_Data[2][j] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::Left:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 0; j < 3; j++) {
					temp_Side_Data[j][0] = temp_Value.front();
					temp_Value.pop();
				}
				break;


			case Adjacent_Side::UpR:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 2; j >= 0; j--) {
					temp_Side_Data[0][j] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::RightR:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 2; j >= 0; j--) {
					temp_Side_Data[j][2] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::DownR:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 2; j >= 0; j--) {
					temp_Side_Data[2][j] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::LeftR:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 2; j >= 0; j--) {
					temp_Side_Data[j][0] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			}
			if (i == 0) break;
		}
	}
	else
	{
		//#.2-1 Turn itself
		char* temp_Side_char = new char[8]
		{ side_Data[0][0],
			side_Data[0][1],
			side_Data[0][2],
			side_Data[1][2],
			side_Data[2][2],
			side_Data[2][1],
			side_Data[2][0],
			side_Data[1][0],
		};
		side_Data[0][0] = temp_Side_char[2];
		side_Data[0][1] = temp_Side_char[3];
		side_Data[0][2] = temp_Side_char[4];
		side_Data[1][2] = temp_Side_char[5];
		side_Data[2][2] = temp_Side_char[6];
		side_Data[2][1] = temp_Side_char[7];
		side_Data[2][0] = temp_Side_char[0];
		side_Data[1][0] = temp_Side_char[1];
		delete temp_Side_char;

		for (int i = 3; ; i++)
		{
			if (i == 4) i = 0;
			char** temp_Side_Data;
			switch (adj_Cube[i].adj_Side)
			{
			case Adjacent_Side::Up:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 0; j < 3; j++) {
					temp_Side_Data[0][j] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::Right:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 0; j < 3; j++) {
					temp_Side_Data[j][2] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::Down:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 0; j < 3; j++) {
					temp_Side_Data[2][j] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::Left:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 0; j < 3; j++) {
					temp_Side_Data[j][0] = temp_Value.front();
					temp_Value.pop();
				}
				break;


			case Adjacent_Side::UpR:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 2; j >= 0; j--) {
					temp_Side_Data[0][j] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::RightR:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 2; j >= 0; j--) {
					temp_Side_Data[j][2] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::DownR:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 2; j >= 0; j--) {
					temp_Side_Data[2][j] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			case Adjacent_Side::LeftR:
				temp_Side_Data = adj_Cube[i].cube->side_Data;
				for (int j = 2; j >= 0; j--) {
					temp_Side_Data[j][0] = temp_Value.front();
					temp_Value.pop();
				}
				break;
			}
			if (i == 2) break;
		}
	}
}
void Make_Cube(vector<Cube>* cubes);
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int num_Of_TestCase; 
	cin >> num_Of_TestCase;
	for (int i = 0; i < num_Of_TestCase; i++)
	{
		//#.1 makeCube
		vector<Cube>* cubes = new vector<Cube>();
		Make_Cube(cubes);

		int num_Of_Test;
		cin >> num_Of_Test;
		//#.2-1 Check_Side
		for (int j = 0; j < num_Of_Test; j++) {
			string input = "";
			cin >> input;
			int index = 0;
			switch (input[0])
			{
			case 'U':
				index = 0;
				break;
			case 'D':
				index = 1;
				break;
			case 'F':
				index = 2;
				break;
			case 'B':
				index = 3;
				break;
			case 'L':
				index = 4;
				break;
			case 'R':
				index = 5;
				break;
			}
			//#.2-2 Check_Direction
			if (input[1] == '+') (*cubes)[index].turn(Turn_Direction::Clock);
			else (*cubes)[index].turn(Turn_Direction::UnClock);
		}
		cout << (*cubes)[0] << endl;
		delete cubes;
	}
	return 0;
}

void Make_Cube(vector<Cube>* cubes) 
{
	char color[6] = { 'w', 'y', 'r', 'o', 'g', 'b' };
	//#.1 큐브 생성
	for (int i = 0; i < 6; i++) {
		char** cube_Side_Value = new char* [3];
		for (int j = 0; j < 3; j++) 
		{
			cube_Side_Value[j] = new char[3]{ color[i], color[i], color[i] };
		}
		cubes->push_back(*new Cube(cube_Side_Value));
	}
	//#.2 큐브 연결
	for (int i = 0; i < 6; i++) 
	{
		Adjacent_Data* adj_Dt;
		switch (i)
		{
		case 0:
			adj_Dt = new Adjacent_Data[4]{
				{&(*cubes)[3], Adjacent_Side::Down},
				{&(*cubes)[5], Adjacent_Side::UpR},
				{&(*cubes)[2], Adjacent_Side::UpR},
				{&(*cubes)[4], Adjacent_Side::UpR},
			};
			(*cubes)[0].Set_Adj_Cube(adj_Dt);
			break;
		case 1:
			adj_Dt = new Adjacent_Data[4]{
				{&(*cubes)[2], Adjacent_Side::Down},
				{&(*cubes)[5], Adjacent_Side::Down},
				{&(*cubes)[3], Adjacent_Side::UpR},
				{&(*cubes)[4], Adjacent_Side::Down},
			};
			(*cubes)[1].Set_Adj_Cube(adj_Dt);
			break;
		case 2:
			adj_Dt = new Adjacent_Data[4]{
				{&(*cubes)[0], Adjacent_Side::Down},
				{&(*cubes)[5], Adjacent_Side::Left},
				{&(*cubes)[1], Adjacent_Side::UpR},
				{&(*cubes)[4], Adjacent_Side::RightR},
			};
			(*cubes)[2].Set_Adj_Cube(adj_Dt);
			break;
		case 3:
			adj_Dt = new Adjacent_Data[4]{
				{&(*cubes)[1], Adjacent_Side::Down},
				{&(*cubes)[5], Adjacent_Side::RightR},
				{&(*cubes)[0], Adjacent_Side::UpR},
				{&(*cubes)[4], Adjacent_Side::Left},
			};
			(*cubes)[3].Set_Adj_Cube(adj_Dt);
			break;
		case 4:
			adj_Dt = new Adjacent_Data[4]{
				{&(*cubes)[0], Adjacent_Side::Left},
				{&(*cubes)[2], Adjacent_Side::Left},
				{&(*cubes)[1], Adjacent_Side::Left},
				{&(*cubes)[3], Adjacent_Side::Left},
			};
			(*cubes)[4].Set_Adj_Cube(adj_Dt);
			break;
		case 5:
			adj_Dt = new Adjacent_Data[4]{
				{&(*cubes)[0], Adjacent_Side::RightR},
				{&(*cubes)[3], Adjacent_Side::RightR},
				{&(*cubes)[1], Adjacent_Side::RightR},
				{&(*cubes)[2], Adjacent_Side::RightR},
			};
			(*cubes)[5].Set_Adj_Cube(adj_Dt);
			break;
		}
	}
}