#include <iostream>
#include <vector>
using namespace std;

int parent(int n) { return n / 2; }
int left(int n) { return 2 * n; }
int right(int n) { return 2 * n + 1; }

vector<long long> tree;
vector<long long> arr;

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx] = arr[start];
	}
	else
	{
		int mid = (start + end) / 2;
		build(left(idx), start, mid);
		build(right(idx), mid + 1, end);
		tree[idx] = (tree[left(idx)] * tree[right(idx)]) % 1000000007;
	}
}

long long query(int idx, int start, int end, int l, int r)
{
	if (r < start || end < l) return 1; 
	if (l <= start && end <= r) return tree[idx]; 

	int mid = (start + end) / 2;

	return (query(left(idx), start, mid, l, r) * query(right(idx), mid + 1, end, l, r)) % 1000000007;
}

void update(int idx, int start, int end, int change, long long val) 
{
	if (change < start || change > end) return;

	if (start == end) 
	{
		tree[idx] = val;
		return;
	}
	int mid = (start + end) / 2;
	update(left(idx), start, mid, change, val);
	update(right(idx), mid + 1, end, change, val);
	tree[idx] = (tree[left(idx)] * tree[right(idx)]) % 1000000007;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, K;

	cin >> N;
	cin >> M;
	cin >> K;

	arr.resize(N + 1);
	tree.resize(4 * N);

	for (int cnt = 1; cnt <= N; cnt++)
	{
		cin >> arr[cnt];
	}

	build(1, 1, N);

	for (int cnt = 0; cnt < M + K;cnt++)
	{
		long long order, first, second;

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
}
