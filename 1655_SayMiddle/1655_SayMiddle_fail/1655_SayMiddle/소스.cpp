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

class Number 
{
public:
	int value;
	Number* left;
	Number* right;
	Number(int value, Number* left = NULL, Number* right = NULL) {
		this->value = value;
		this->left = left;
		this->right = right;
	}
};
class Number_List {
	int num_Of_Left = 0;
	int num_Of_Right = 0;
public:
	Number* center_Number;
	Number_List(Number* center_Number) {
		this->center_Number = center_Number;
		center_Number->left = new Number(-10001, NULL, center_Number);
		center_Number->right = new Number(10001, center_Number, NULL);
	}
	void Add(Number* add_Number, bool isLeft = true) {
		Number* temp_Number = center_Number;
		if (isLeft) {
			//#.1 Find seat
			while (add_Number->value <= temp_Number->value) {
				temp_Number = temp_Number->left;
			}
			//#.2 Insert
			add_Number->right = temp_Number->right;
			temp_Number->right->left = add_Number;
			temp_Number->right = add_Number;
			add_Number->left = temp_Number;
			num_Of_Left++;
		}
		else {
			//#.1 Find seat
			while (temp_Number->value < add_Number->value) {
				temp_Number = temp_Number->right;
			}
			//#.2 Insert
			add_Number->left = temp_Number->left;
			temp_Number->left->right = add_Number;
			temp_Number->left = add_Number;
			add_Number->right = temp_Number;
			num_Of_Right++;
		}
		//#.3 Check Center
		if (num_Of_Left > num_Of_Right) { //왼쪽이 더많을 때
			center_Number = center_Number->left;
			num_Of_Left--;
			num_Of_Right++;
		}
		else if (num_Of_Right - num_Of_Left == 2) { //오른쪽이 왼쪽보다 2개 많을 떄
			center_Number = center_Number->right;
			num_Of_Left++;
			num_Of_Right--;
		}
		else { //오른쪽 = 왼쪽

		}
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int N;
	cin >> N;
	vector<int> temp;
	Number_List number_List(new Number(0));
	for (int i = 0; i < N; i++) {
		int number;
		cin >> number;
		if (i == 0) {
			number_List.center_Number->value = number;
			continue;
		}
		number_List.Add(new Number(number), number <= number_List.center_Number->value);
		//Print
		cout << number_List.center_Number->value << endl;
	}
	return 0;
}