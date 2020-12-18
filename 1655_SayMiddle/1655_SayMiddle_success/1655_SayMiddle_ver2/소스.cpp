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
	priority_queue<int, vector<int>, less<int>> max_Heap; //최대힙 - root가 가장 큰 값
	priority_queue<int, vector<int>, greater<int>> min_Heap; //최소힙 - root가 가장 작은 값
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int number;
		cin >> number;
		//#.1 조건1 max_Heap의 크기는 min_Heap과 같거나 하나크다.
		if (max_Heap.size() > min_Heap.size())
			min_Heap.push(number);
		else
			max_Heap.push(number);
		//#.2 조건2 max_Heap.top()는 min_Heap.top()보다 작거나 같다. 다르면 바꿔준다. 
		//바꿔줘도 최대 최소힙 조건만족
		if (!max_Heap.empty() && !min_Heap.empty() && max_Heap.top() > min_Heap.top()) {
			int temp_MaxHeap = max_Heap.top();
			int temp_MinHeap = min_Heap.top();
			max_Heap.pop();
			min_Heap.pop();
			max_Heap.push(temp_MinHeap);
			min_Heap.push(temp_MaxHeap);
		}
		//Print
		cout << max_Heap.top() << "\n";
	}
	return 0;
}