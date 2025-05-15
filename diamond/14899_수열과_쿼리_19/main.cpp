#define BIG_NUM 1000000000

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
	ll lazyDiv;
};

ll arr[100001];
Node tree[400004];

inline int divNum(int a, int num) {
	if (a >= 0) return a / num;
	return (a - (num - 1)) / num;
}

void lazyUpdate(int idx, int start, int end)
{
	if (tree[idx].lazyDiv == BIG_NUM && tree[idx].lazySum == 0) return;

	if (tree[idx].lazyDiv == BIG_NUM)
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
		tree[idx].sum = (tree[idx].lazyDiv + tree[idx].lazySum) * (end - start + 1);
		tree[idx].max = tree[idx].lazyDiv + tree[idx].lazySum;
		tree[idx].min = tree[idx].lazyDiv + tree[idx].lazySum;

		if (start != end)
		{
			tree[idx << 1].lazyDiv = tree[idx << 1 | 1].lazyDiv = tree[idx].lazyDiv;
			tree[idx << 1].lazySum = tree[idx << 1 | 1].lazySum = tree[idx].lazySum;
		}
	}

	tree[idx].lazyDiv = BIG_NUM;
	tree[idx].lazySum = 0;
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
		tree[idx] = { arr[start],arr[start], arr[start], 0, BIG_NUM };
	}
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		pull(tree[idx], tree[idx << 1], tree[idx << 1 | 1]);
		tree[idx].lazyDiv = BIG_NUM;
	}
}

void rangeAdd(int idx, int start, int end, int l, int r, int num)
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

void rangeDiv(int idx, int start, int end, int l, int r, int num)
{
	lazyUpdate(idx, start, end);

	if (start > r || end < l) return;
	if (l <= start && end <= r)
	{
		if (divNum(tree[idx].max,num) == divNum(tree[idx].min,num))
		{
			tree[idx].lazyDiv = divNum(tree[idx].max, num);
			lazyUpdate(idx, start, end);
			return;
		}

		if (tree[idx].min + 1 == tree[idx].max)
		{
			tree[idx].lazySum = divNum(tree[idx].min, num) - tree[idx].min;
			lazyUpdate(idx, start, end);
			return;
		}
	}

	int mid = (start + end) / 2;
	rangeDiv(idx << 1, start, mid, l, r, num);
	rangeDiv(idx << 1 | 1, mid + 1, end, l, r, num);
	pull(tree[idx], tree[idx << 1], tree[idx << 1 | 1]);
}

int rangeMin(int idx, int start, int end, int l, int r) 
{
	lazyUpdate(idx, start, end);
	
	if (r < start || end < l) return 1e9;
	if (l <= start && end <= r) return tree[idx].min;
	
	int mid = (start + end) >> 1;
	return min(rangeMin(idx << 1, start, mid, l, r), rangeMin(idx << 1 | 1, mid + 1, end, l, r));
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
	cin >> Q;

	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	build(1, 1, N);

	for (int i = 0; i < Q; i++)
	{
		int order, first, second, num;

		cin >> order >> first >> second;

		switch (order)
		{
		case 1:
			cin >> num;
			rangeAdd(1, 1, N, first + 1, second + 1, num);
			break;
		case 2:
			cin >> num;
			rangeDiv(1, 1, N, first + 1, second + 1, num);
			break;
		case 3:
			cout << rangeMin(1, 1, N, first + 1, second + 1) << "\n";
			break;
		case 4:
			cout << rangeSum(1, 1, N, first + 1, second + 1) << "\n";
			break;
		}
	}
}