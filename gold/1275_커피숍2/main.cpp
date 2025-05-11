#include <vector>
#include <iostream>
using namespace std;

vector<int> arr;
vector<long long> tree;

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
		if(find <= mid)
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
	cin >> M;

	arr.resize(N + 1);
	tree.resize(4 * N);

	for (int cnt = 1; cnt <= N; cnt++)
		cin >> arr[cnt];

	build(1, 1, N);

	for (int cnt = 0; cnt < M; cnt++)
	{
		int l, r, find, num;

		cin >> l;
		cin >> r;
		cin >> find;
		cin >> num;

		if (l > r)swap(l, r);
		cout << query(1, 1, N, l, r) << "\n";
		update(1, 1, N, find, num);
	}
	return 0;
}
