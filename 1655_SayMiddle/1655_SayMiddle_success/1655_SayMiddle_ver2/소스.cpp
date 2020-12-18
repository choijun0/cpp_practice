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
	priority_queue<int, vector<int>, less<int>> max_Heap; //�ִ��� - root�� ���� ū ��
	priority_queue<int, vector<int>, greater<int>> min_Heap; //�ּ��� - root�� ���� ���� ��
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int number;
		cin >> number;
		//#.1 ����1 max_Heap�� ũ��� min_Heap�� ���ų� �ϳ�ũ��.
		if (max_Heap.size() > min_Heap.size())
			min_Heap.push(number);
		else
			max_Heap.push(number);
		//#.2 ����2 max_Heap.top()�� min_Heap.top()���� �۰ų� ����. �ٸ��� �ٲ��ش�. 
		//�ٲ��൵ �ִ� �ּ��� ���Ǹ���
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