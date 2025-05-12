#include <vector>
#include <iostream>
using namespace std;

vector<int> arr;
vector<int> tree;

void build(int idx, int start, int end)
{
	if (start == end)
		tree[idx] = arr[start];
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		tree[idx] = tree[idx << 1] > tree[idx << 1 | 1] ? tree[idx << 1] : tree[idx << 1 | 1];
	}
}

int query(int idx, int start, int end, int l, int r)
{
	if (start > r || end < l) return 0;
	if (l <= start && end <= r) return tree[idx];

	int mid = (start + end) / 2;
	int left = query(idx << 1, start, mid, l, r);
	int right = query(idx << 1 | 1, mid + 1, end, l, r);
	return left > right ? left : right;
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

	for (int i = 1; i <= N; i++)
		cin >> arr[i];	

	build(1, 1, N);

	M = (M - 1) * 2;

	for (int i = 1; i <= N - M; i++)
	{
		cout << query(1, 1, N, i, i + M) << " ";
	}
}
