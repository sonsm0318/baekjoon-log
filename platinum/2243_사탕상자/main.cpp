#include <vector>
#include <iostream>
using namespace std;

struct Node
{
	int left, right;
	int count;
};

vector<Node> tree;

void update(int idx, int start, int end, int find, int num)
{
	if (start == end)
	{
		tree[idx].count += num;
	}
	else
	{
		int mid = (start + end) / 2;
		if(find <= mid)
			update(idx << 1, start, mid, find, num);
		else
			update(idx << 1 | 1, mid + 1, end, find, num);

		tree[idx].left = tree[idx << 1].count;
		tree[idx].right = tree[idx << 1 | 1].count;
		tree[idx].count = tree[idx].left + tree[idx].right;
	}
}

int query(int idx, int start, int end, int find)
{
	if (start == end)
	{
		tree[idx].count--;
		return start;
	}

	int mid = (start + end) / 2;
	int ret;
	if (tree[idx << 1].count >= find)
		ret = query(idx << 1, start, mid, find);
	else
		ret = query(idx << 1 | 1, mid + 1, end, find - tree[idx << 1].count);
	tree[idx].left = tree[idx << 1].count;
	tree[idx].right = tree[idx << 1 | 1].count;
	tree[idx].count = tree[idx].left + tree[idx].right;

	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int M;
	cin >> M;

	tree.resize(4 * 1000000);

	for (int i = 0; i < M; i++)
	{
		int order, first, second;

		cin >> order;
		cin >> first;
		

		switch (order)
		{
		case 1:
			cout << query(1, 1, 1000000, first) << "\n";
			break;
		case 2:
			cin >> second;
			update(1, 1, 1000000, first, second);
			break;
		}
	}
}
