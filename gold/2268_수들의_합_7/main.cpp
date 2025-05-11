#include <vector>
#include <iostream>
using namespace std;

vector<long long> tree;

long long query(int idx, int start, int end, int l, int r)
{
	if (start > r || end < l) return 0;
	if (l <= start && end <= r) return tree[idx];
	int mid = (start + end) / 2;
	return query(idx << 1, start, mid, l, r) + query(idx << 1 | 1, mid + 1, end, l, r);
}

void update(int idx, int start, int end, int find, long long num)
{
	if (start == end)
	{
		tree[idx] = num;
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

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;
	cin >> N;

	tree.assign(4 * N, 0);

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
		case 0:
			if (first > second) swap(first, second);
			cout << query(1, 1, N, first, second) << "\n";
			break;
		}
	}

	return 0;
}
