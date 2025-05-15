#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef long long ll;

struct Node
{
	ll sum;
	ll max;
	ll min;
	ll lazySum;
	ll lazySqrt;
};

ll arr[100001];
Node tree[400004];

void lazyUpdate(int idx, int start, int end)
{
	if (tree[idx].lazySqrt == 0 && tree[idx].lazySum == 0) return;

	if (!tree[idx].lazySqrt)
	{
		tree[idx].sum += tree[idx].lazySum * (end - start + 1);
		tree[idx].max += tree[idx].lazySum;
		tree[idx].min += tree[idx].lazySum;

		if (start != end)
		{
			tree[idx << 1].lazySum += tree[idx].lazySum;
			tree[idx << 1 | 1].lazySum += tree[idx].lazySum;
		}
	}
	else
	{
		tree[idx].sum = (tree[idx].lazySqrt + tree[idx].lazySum) * (end - start + 1);
		tree[idx].max = tree[idx].lazySqrt + tree[idx].lazySum;
		tree[idx].min = tree[idx].lazySqrt + tree[idx].lazySum;

		if (start != end)
		{
			tree[idx << 1].lazySqrt = tree[idx << 1 | 1].lazySqrt = tree[idx].lazySqrt;
			tree[idx << 1].lazySum = tree[idx << 1 | 1].lazySum = tree[idx].lazySum;
		}
	}

	tree[idx].lazySqrt = tree[idx].lazySum = 0;
}

void pull(Node& parent, Node& left, Node& right)
{
	parent.max = left.max > right.max ? left.max : right.max;
	parent.min = left.min < right.min ? left.min : right.min;
	parent.sum = left.sum + right.sum;
}

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx] = { arr[start],arr[start], arr[start], 0, 0 };
	}
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		pull(tree[idx], tree[idx << 1], tree[idx << 1 | 1]);
	}
}

void rangeAdd(int idx, int start, int end, int l, int r, ll num)
{
	lazyUpdate(idx, start, end);

	if (start > r || end < l) return;
	if (l <= start && end <= r)
	{
		tree[idx].lazySum += num;
		lazyUpdate(idx, start, end);
		return;
	}

	int mid = (start + end) / 2;
	rangeAdd(idx << 1, start, mid, l, r, num);
	rangeAdd(idx << 1 | 1, mid + 1, end, l, r, num);
	pull(tree[idx], tree[idx << 1], tree[idx << 1 | 1]);
}

void rangeSqrt(int idx, int start, int end, int l, int r)
{
	lazyUpdate(idx, start, end);

	if (start > r || end < l) return;
	if (l <= start && end <= r)
	{
		if (floor(sqrt(tree[idx].max)) == floor(sqrt(tree[idx].min)))
		{
			tree[idx].lazySqrt = floor(sqrt(tree[idx].max));
			lazyUpdate(idx, start, end);
			return;
		}
		
		if (tree[idx].min + 1 == tree[idx].max)
		{
			tree[idx].lazySum = floor(sqrt(tree[idx].min)) - tree[idx].min;
			lazyUpdate(idx, start, end);
			return;
		}
	}

	int mid = (start + end) / 2;
	rangeSqrt(idx << 1, start, mid, l, r);
	rangeSqrt(idx << 1 | 1, mid + 1, end, l, r);
	pull(tree[idx], tree[idx << 1], tree[idx << 1 | 1]);
}

ll rangeSum(int idx, int start, int end, int l, int r)
{
	lazyUpdate(idx, start, end);

	if (start > r || end < l) return 0;
	if (l <= start && end <= r) return tree[idx].sum;

	int mid = (start + end) / 2;
	return	rangeSum(idx << 1, start, mid, l, r) +
			rangeSum(idx << 1 | 1, mid + 1, end, l, r);
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, Q;
	cin >> N;
	
	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	build(1, 1, N);

	cin >> Q;

	for (int i = 0; i < Q; i++)
	{
		int order, first, second;
		ll num;

		cin >> order >> first >> second;

		switch (order)
		{
		case 1:
			cin >> num;
			rangeAdd(1, 1, N, first, second, num);
			break;
		case 2:
			rangeSqrt(1, 1, N, first, second);
			break;
		case 3:
			cout << rangeSum(1, 1, N, first, second) << "\n";
			break;
		}
	}
}