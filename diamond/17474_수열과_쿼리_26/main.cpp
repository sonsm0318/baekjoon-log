#include <vector>
#include <iostream>
using namespace std;

struct Node
{
	int max;
	int maxCount;
	int secondMax;
	int lazy;
	long long sum;
};

vector<Node> tree;
vector<int> arr;

int findMax(int a, int b)
{
	return a > b ? a : b;
}

inline void apply_chmin(Node& n, int x) 
{
	if (x >= n.max) return;
	n.sum -= 1LL * (n.max - x) * n.maxCount;
	n.max = x;
	if (n.lazy == -1 || x < n.lazy) n.lazy = x;
}

void pushDown(int idx) 
{
	if (tree[idx].lazy == -1) return;
	apply_chmin(tree[2 * idx], tree[idx].lazy);
	apply_chmin(tree[2 * idx + 1], tree[idx].lazy);
	tree[idx].lazy = -1;
}

Node merge(const Node& a, const Node& b) 
{
	Node ret;
	if (a.max == b.max) 
	{
		ret.max = a.max;
		ret.maxCount = a.maxCount + b.maxCount;
		ret.secondMax = findMax(a.secondMax, b.secondMax);
	}
	else if (a.max > b.max) 
	{
		ret.max = a.max;
		ret.maxCount = a.maxCount;
		ret.secondMax = findMax(a.secondMax, b.max);
	}
	else 
	{
		ret.max = b.max;
		ret.maxCount = b.maxCount;
		ret.secondMax = findMax(a.max, b.secondMax);
	}
	ret.sum = a.sum + b.sum;
	ret.lazy = -1;
	return ret;
}

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx].max = arr[start];
		tree[idx].secondMax = -1;
		tree[idx].sum = arr[start];
		tree[idx].maxCount = 1;
		tree[idx].lazy = -1;
	}
	else
	{
		int mid = (start + end) / 2;
		build(2 * idx, start, mid);
		build(2 * idx + 1, mid + 1, end);
		
		tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
	}
}

void firstQuery(int idx, int start, int end, int l, int r, int minNum)
{
	if (l > end || r < start || tree[idx].max <= minNum) return;
	if (l <= start && r >= end && tree[idx].secondMax < minNum)
	{
		apply_chmin(tree[idx], minNum);
		return;
	}
	pushDown(idx);
	int mid = (start + end) / 2;
	firstQuery(2 * idx, start, mid, l, r, minNum);
	firstQuery(2 * idx + 1, mid + 1, end, l, r, minNum);

	tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
}

int secondQuery(int idx, int start, int end, int l, int r)
{
	if (start > r || l > end) return -1;
	if (l <= start && end <= r) return tree[idx].max;
	pushDown(idx);
	int mid = (start + end) / 2;
	return findMax(
		secondQuery(2 * idx, start, mid, l, r), 
		secondQuery(2 * idx + 1, mid + 1, end, l, r)
	);
}

long long thirdQuery(int idx, int start, int end, int l, int r)
{
	if (start > r || l > end) return 0;
	if (l <= start && end <= r) return tree[idx].sum;

	pushDown(idx);
	int mid = (start + end) / 2;
	
	return	thirdQuery(2*idx, start, mid, l, r) +
			thirdQuery(2*idx+1, mid + 1, end, l, r);

	
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	arr.resize(N + 1);
	tree.resize(4 * N);

	for (int cnt = 1; cnt <= N; cnt++)
		cin >> arr[cnt];

	build(1, 1, N);

	int M;
	cin >> M;

	for (int cnt = 0; cnt < M; cnt++)
	{
		int order, first, second, minNum;
		cin >> order;
		cin >> first;
		cin >> second;

		switch (order)
		{
		case 1:
			cin >> minNum;
			firstQuery(1, 1, N, first, second, minNum);
			break;
		case 2:
			cout << secondQuery(1, 1, N, first, second) << "\n";
			break;
		case 3:
			cout << thirdQuery(1, 1, N, first, second) << "\n";
			break;
		}
	}
}
