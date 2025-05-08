#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int parent(int n) { return n / 2; }
int left(int n) { return 2 * n; }
int right(int n) { return 2 * n + 1; }

struct Data
{
	long long data;
	int start;
	int end;
};

Data arr[4000000];
Data tmpArr[1000000];
int segeTreeSize;

int getMaxTwoMultiple(int n)
{
	int a = 1;
	while (a * 2 <= n)
	{
		a *= 2;
	}
	return a;
}

void makeSegeTree(int n)
{
	int idx = 2 * n - 1;
	int extra = (n - getMaxTwoMultiple(n)) * 2;

	for (int cnt = extra - 1; cnt >= 0; cnt--)
	{
		arr[idx--] = tmpArr[cnt];
	}
	for (int cnt = n - 1; cnt >= extra; cnt--)
	{
		arr[idx--] = tmpArr[cnt];
	}

	while (idx > 0)
	{
		arr[idx].data = arr[left(idx)].data + arr[right(idx)].data;
		arr[idx].start = arr[left(idx)].start;
		arr[idx].end = arr[right(idx)].end;
		idx--;
	}
}

long long TreeSum(int leftIdx, int rightIdx, int idx)
{
	if (arr[idx].start >= leftIdx && arr[idx].end <= rightIdx) return arr[idx].data;
	if (arr[idx].start > rightIdx || arr[idx].end < leftIdx) return 0;
	return TreeSum(leftIdx, rightIdx, left(idx)) + TreeSum(leftIdx, rightIdx, right(idx));
}

void updateTree(int idx, long long num)
{
	int current = 1;

	while (1)
	{
		if (arr[current].start == arr[current].end)
		{
			arr[current].data = num;
			current = parent(current);
			break;
		}

		if (idx >= arr[left(current)].start && idx <= arr[left(current)].end)
		{
			current = left(current);
		}
		else
		{
			current = right(current);
		}
	}

	while (current > 0)
	{
		arr[current].data = arr[left(current)].data + arr[right(current)].data;
		current = parent(current);
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, K;

	cin >> N;
	cin >> M;
	cin >> K;

	for (int cnt = 0; cnt < N; cnt++)
	{
		cin >> tmpArr[cnt].data;
		tmpArr[cnt].start = cnt + 1;
		tmpArr[cnt].end = cnt + 1;
	}

	segeTreeSize = 2 * N - 1;
	makeSegeTree(N);


	for (int cnt = 0; cnt < M + K; cnt++)
	{
		long long order, first, second;

		cin >> order;
		cin >> first;
		cin >> second;

		switch(order)
		{
		case 1:
			updateTree(first, second);	
			break;
		case 2:
			cout << TreeSum(first, second, 1) << "\n";
			break;
		}
	}

	return 0;
}
