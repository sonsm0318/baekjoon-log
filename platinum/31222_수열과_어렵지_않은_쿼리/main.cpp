#include <vector>
#include <iostream>
using namespace std;

struct Node
{
	int left, right;
	int count;
};

vector<int> arr;
vector<Node> tree;

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx].count = 1;
		tree[idx].left = tree[idx].right = arr[start];
	}
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		tree[idx].left = tree[idx << 1].left;
		tree[idx].right = tree[idx << 1 | 1].right;

		if (tree[idx << 1].right == tree[idx << 1 | 1].left)
		{
			tree[idx].count = tree[idx << 1].count + tree[idx << 1 | 1].count - 1;
		}
		else
		{
			tree[idx].count = tree[idx << 1].count + tree[idx << 1 | 1].count;
		}
	}
}

void update(int idx, int start, int end, int find, int num)
{
	if (start == end)
	{
		tree[idx].left = tree[idx].right = num;
	}
	else
	{
		int mid = (start + end) / 2;
		if(find <= mid)
			update(idx << 1, start, mid, find, num);
		else
			update(idx << 1 | 1, mid + 1, end, find, num);

		tree[idx].left = tree[idx << 1].left;
		tree[idx].right = tree[idx << 1 | 1].right;

		if (tree[idx << 1].right == tree[idx << 1 | 1].left)
		{
			tree[idx].count = tree[idx << 1].count + tree[idx << 1 | 1].count - 1;
		}
		else
		{
			tree[idx].count = tree[idx << 1].count + tree[idx << 1 | 1].count;
		}
	}
}

Node query(int idx, int start, int end, int l, int r)
{
	if (start > r || end < l) return { 0,0,0 };
	if (l <= start && end <= r) return tree[idx];
	
	int mid = (start + end) / 2;
	if (r <= mid)
		return query(idx << 1, start, mid, l, r);
	if (l > mid)
		return query(idx << 1 | 1, mid + 1, end, l, r);

	Node ret;
	Node left = query(idx << 1, start, mid, l, r);
	Node right = query(idx << 1 | 1, mid + 1, end, l, r);

	ret.left = left.left;
	ret.right = right.right;

	if (left.right == right.left)
	{
		ret.count = left.count + right.count - 1;
	}
	else
		ret.count = left.count + right.count;

	return ret;
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

	for (int i = 0; i < M; i++)
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
		case 2:
			cout << query(1, 1, N, first, second).count << "\n";
			break;
		}
	}
}
