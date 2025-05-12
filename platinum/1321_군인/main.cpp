#include <vector>
#include <iostream>
using namespace std;

vector<int> arr;
vector<int> tree;

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx] = arr[start];
	}
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
	}
}

void update(int idx, int start, int end, int find, int num)
{
	if (start == end)
	{
		tree[idx] += num;
	}
	else
	{
		int mid = (start + end) / 2;
		if (find <= mid)
			update(idx << 1, start, mid, find, num);
		else
			update(idx << 1 | 1, mid + 1, end, find, num);
		tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
	}
}

int query(int idx, int start, int end, int find)
{
	if (start == end)
	{
		return start;
	}
	int mid = (start + end) / 2;
	if (tree[idx << 1] >= find)
		return query(idx << 1, start, mid, find);
	else
		return query(idx << 1 | 1, mid + 1, end, find - tree[idx << 1]);
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	arr.resize(N + 1);
	tree.resize(4 * N);

	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	build(1, 1, N);

	int M;
	cin >> M;

	for (int i = 0; i < M; i++)
	{
		int order, first, second;
		cin >> order;
		cin >> first;

		switch (order)
		{
		case 1:
			cin >> second;
			update(1, 1, N, first, second);
			break;
		case 2:
			cout << query(1, 1, N, first) << "\n";
			break;
		}
	}

	return 0;
}
