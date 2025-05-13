#include <iostream>
#include <vector>
using namespace std;

struct Node
{
	int max1;
	int max2;
};

vector<int> arr;
vector<Node> tree;

void pull(int idx)
{
	if (tree[idx << 1].max1 > tree[idx << 1 | 1].max1)
	{
		tree[idx].max1 = tree[idx << 1].max1;
		if (tree[idx << 1].max2 > tree[idx << 1 | 1].max1)
		{
			tree[idx].max2 = tree[idx << 1].max2;
		}
		else
		{
			tree[idx].max2 = tree[idx << 1 | 1].max1;
		}
	}
	else if (tree[idx << 1].max1 < tree[idx << 1 | 1].max1)
	{
		tree[idx].max1 = tree[idx << 1 | 1].max1;
		if (tree[idx << 1 | 1].max2 > tree[idx << 1].max1)
		{
			tree[idx].max2 = tree[idx << 1 | 1].max2;
		}
		else
		{
			tree[idx].max2 = tree[idx << 1].max1;
		}
	}
	else
	{
		tree[idx].max1 = tree[idx].max2 = tree[idx << 1].max1;
	}
}

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx].max1 = arr[start];
		tree[idx].max2 = -1;
	}
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		
		pull(idx);
	}
}

void update(int idx, int start, int end, int find, int num)
{
	if (start == end)
	{
		tree[idx].max1 = num;
	}
	else
	{
		int mid = (start + end) / 2;
		if (find <= mid)
			update(idx << 1, start, mid, find, num);
		else
			update(idx << 1 | 1, mid + 1, end, find, num);

		pull(idx);
	}
}

Node query(int idx, int start, int end, int l, int r)
{
	if (l <= start && end <= r) return tree[idx];

	int mid = (start + end) / 2;
	if (r <= mid)
		return query(idx << 1, start, mid, l, r);
	else if (l > mid)
		return query(idx << 1 | 1, mid + 1, end, l, r);

	Node left = query(idx << 1, start, mid, l, r);
	Node right = query(idx << 1 | 1, mid + 1, end, l, r);
	Node ret;

	if (left.max1 > right.max1)
	{
		ret.max1 = left.max1;

		if (left.max2 > right.max1)
		{
			ret.max2 = left.max2;
		}
		else
		{
			ret.max2 = right.max1;
		}
	}
	else if(right.max1 > left.max1)
	{
		ret.max1 = right.max1;

		if (right.max2 > left.max1)
		{
			ret.max2 = right.max2;
		}
		else
		{
			ret.max2 = left.max1;
		}
	}
	else
	{
		ret.max1 = ret.max2 = left.max1;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;

	cin >> N;

	arr.resize(N + 1);
	tree.resize(4 * N);

	for (int cnt = 1; cnt <= N; cnt++)
		cin >> arr[cnt];
	
	build(1, 1, N);

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
		case 2:
			Node tmp = query(1, 1, N, first, second);
			cout << tmp.max1 + tmp.max2 << "\n";
			break;
		}
	}
}
