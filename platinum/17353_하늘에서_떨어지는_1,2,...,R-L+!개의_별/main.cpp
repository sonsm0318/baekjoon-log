#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

struct Node
{
	ll sum;
	ll lazyAdd;
	ll lazySlope;
};

ll arr[100001];
Node tree[400004];

void build(int idx, int start, int end)
{
	if (start == end)
		tree[idx].sum = arr[start];
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		tree[idx].sum = tree[idx << 1].sum + tree[idx << 1 | 1].sum;
	}
}

void lazyUpdate(int idx, int start, int end)
{
	if (!tree[idx].lazyAdd && tree[idx].lazySlope == 0) return;

	int len = end - start + 1;
	tree[idx].sum += tree[idx].lazyAdd * len + tree[idx].lazySlope * 1LL * (len - 1) * len / 2;
	if (start != end)
	{
		int mid = (start + end) / 2;
		int l_len = mid - start + 1;
		tree[idx << 1].lazyAdd += tree[idx].lazyAdd;
		tree[idx << 1].lazySlope += tree[idx].lazySlope;
		tree[idx << 1 | 1].lazyAdd += tree[idx].lazyAdd + tree[idx].lazySlope * l_len;
		tree[idx << 1 | 1].lazySlope += tree[idx].lazySlope;
	}
	tree[idx].lazyAdd = tree[idx].lazySlope = 0;
}

void update(int idx, int start, int end, int l, int r)
{
	lazyUpdate(idx, start, end);

	if (start > r || end < l) return;
	if (l <= start && end <= r)
	{
		tree[idx].lazyAdd += start - l + 1;
		tree[idx].lazySlope += 1;
		lazyUpdate(idx, start, end);
		return;
	}
	int mid = (start + end) / 2;
	update(idx << 1, start, mid, l, r);
	update(idx << 1 | 1, mid + 1, end, l, r);
	tree[idx].sum = tree[idx << 1].sum + tree[idx << 1 | 1].sum;
}

ll query(int idx, int start, int end, int find)
{
	lazyUpdate(idx, start, end);
	if (start == end)
	{
		return tree[idx].sum;
	}
	int mid = (start + end) / 2;
	if (find <= mid)
		return query(idx << 1, start, mid, find);
	else
		return query(idx << 1 | 1, mid + 1, end, find);
}

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	build(1, 1, N);

	int M;
	cin >> M;

	for (int i = 0; i < M; i++)
	{
		int order, left, right;

		cin >> order;
		cin >> left;

		switch (order)
		{
		case 1:
			cin >> right;
			update(1, 1, N, left, right);
			break;
		case 2:
			cout << query(1, 1, N, left) << "\n";
			break;
		}
	}

	return 0;
}