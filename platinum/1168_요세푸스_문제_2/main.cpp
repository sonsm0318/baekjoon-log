#include <iostream>
#include <vector>
using namespace std;

vector<int> tree;

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx] = 1;
	}
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
	}
}

int query(int idx, int start, int end, int find)
{
	if (start == end)
	{
		tree[idx] = 0;
		return start;
	}
	else
	{
		int mid = (start + end) / 2;
		int ret;
		if (tree[idx << 1] >= find)
			ret = query(idx << 1, start, mid, find);
		else
			ret = query(idx << 1 | 1, mid + 1, end, find - tree[idx << 1]);
		tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
		return ret;
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N;
	cin >> K;

	tree.resize(4 * N);

	build(1, 1, N);

	cout << "<";
	int pos = 0;

	for (int i = 0; i < N; i++)
	{
		pos = (pos + K - 1) % tree[1];
		if(i < N-1)
			cout << query(1, 1, N, pos + 1) << ", ";
		else
			cout << query(1, 1, N, pos + 1) << ">";
	}
}