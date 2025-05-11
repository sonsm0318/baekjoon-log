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
		tree[idx] = tree[idx << 1] < tree[idx << 1 | 1] ? tree[idx << 1] : tree[idx << 1 | 1];
	}
}

int query(int idx, int start, int end, int l, int r)
{
	if (start > r || end < l) return 1000000000;
	if (l <= start && end <= r) return tree[idx];
	int mid = (start + end) / 2;
	int left = query(idx << 1, start, mid, l, r);
	int right = query(idx << 1 | 1, mid + 1, end, l, r);
	return left < right ? left : right;
}

void update(int idx, int start, int end, int find, int num)
{
	if (start == end)
	{
		tree[idx] = num;
	}
	else
	{
		int mid = (start + end) / 2;
		if(find <= mid)
			update(idx << 1, start, mid, find, num);
		else
			update(idx << 1 | 1, mid + 1, end, find, num);
		tree[idx] = tree[idx << 1] < tree[idx << 1 | 1] ? tree[idx << 1] : tree[idx << 1 | 1];
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N;

	arr.resize(N + 1);
	tree.resize(4 * N);

	for (int cnt = 1; cnt <= N; cnt++)
		cin >> arr[cnt];

	build(1,1,N);

	cin >> M;

	for (int cnt = 0; cnt < M; cnt++)
	{
		int order, first, second;

		cin >> order;
		cin >> first;
		cin >> second;

		switch (order)
		{
		case 1:
			update(1, 1, N, first, second);
			break;
		case 2:
			cout << query(1, 1, N, first, second) << "\n";
			break;
		}
	}

	return 0;
}
