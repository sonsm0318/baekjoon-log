#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;

struct Node
{
	ll sum;
	ll lazy;
};

ll arr[1000001];
Node tree[4000000];

void build(int idx, int start, int end)
{
	if (start == end)
		tree[idx] = { arr[start],0 };
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		tree[idx] = { tree[idx << 1].sum + tree[idx << 1 | 1].sum, 0 };
	}
}

void lazyUpdate(int idx, int start, int end)
{
	tree[idx].sum += tree[idx].lazy * (end - start + 1);
	if (start != end)
	{
		tree[idx << 1].lazy += tree[idx].lazy;
		tree[idx << 1 | 1].lazy += tree[idx].lazy;
	}
	tree[idx].lazy = 0;
}

void rangeAdd(int idx, int start, int end, int l, int r, int add)
{
	lazyUpdate(idx, start, end);

	if (start > r || end < l) return;
	if (l <= start && end <= r)
	{
		tree[idx].lazy += add;
		lazyUpdate(idx, start, end);
		return;
	}
	int mid = (start + end) / 2;
	rangeAdd(idx << 1, start, mid, l, r, add);
	rangeAdd(idx << 1 | 1, mid + 1, end, l, r, add);
	tree[idx].sum = tree[idx << 1].sum + tree[idx << 1 | 1].sum;
}

ll rangeSum(int idx, int start, int end, int l, int r)
{
	lazyUpdate(idx, start, end);

	if (start > r || end < l) return 0;
	if (l <= start && end <= r) return tree[idx].sum;
	int mid = (start + end) / 2;
	return 	rangeSum(idx << 1, start, mid, l, r) +
			rangeSum(idx << 1 | 1, mid + 1, end, l, r);
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N, M, K;
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	build(1, 1, N);

	for (int i = 0; i < M + K; i++)
	{
		int a, b, c;
		ll d;
		cin >> a >> b >> c;

		switch (a)
		{
		case 1:
			cin >> d;
			rangeAdd(1, 1, N, b, c, d);
			break;
		case 2:
			cout << rangeSum(1, 1, N, b, c) << "\n";
			break;
		}
	}

	return 0;
}