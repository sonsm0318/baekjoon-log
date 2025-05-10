#include <iostream>
#include <vector>

using namespace std;

int left(int n) { return 2 * n; }
int right(int n) { return 2 * n + 1; }

struct MinMax
{
	int min;
	int max;
};

vector<MinMax> tree;
vector<int> arr;

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx].min = arr[start - 1];
		tree[idx].max = arr[start - 1];
	}
	else
	{
		int mid = (start + end) / 2;
		build(left(idx), start, mid);
		build(right(idx), mid + 1, end);

		if (tree[left(idx)].min < tree[right(idx)].min)
		{
			tree[idx].min = tree[left(idx)].min;
		}
		else
		{
			tree[idx].min = tree[right(idx)].min;
		}

		if (tree[left(idx)].max > tree[right(idx)].max)
		{
			tree[idx].max = tree[left(idx)].max;
		}
		else
		{
			tree[idx].max = tree[right(idx)].max;
		}
	}
}

MinMax query(int idx, int start, int end, int l, int r)
{
	if (l > end || r < start) return { 1000000000,1 };
	if (l <= start && r >= end) return tree[idx];

	int mid = (start + end) / 2;

	MinMax leftData = query(left(idx), start, mid, l, r);
	MinMax rightData = query(right(idx), mid + 1, end, l, r);

	if (mid < l)
	{
		return rightData;
	}
	else if (mid + 1 > r)
	{
		return leftData;
	}

	MinMax ret;

	if (leftData.min < rightData.min)
	{
		ret.min = leftData.min;
	}
	else
	{
		ret.min = rightData.min;
	}

	if (leftData.max > rightData.max)
	{
		ret.max = leftData.max;
	}
	else
	{
		ret.max = rightData.max;
	}

	return ret;
}

void update(int idx, int start, int end, int change, int num)
{
	if (start == end)
	{
		tree[idx].min = num;
		tree[idx].max = num;
	}
	else
	{
		int mid = (start + end) / 2;

		if (change <= mid)
			update(2 * idx, start, mid, change, num);
		if (change > mid)
			update(2 * idx + 1, mid + 1, end, change, num);

		if (tree[left(idx)].min < tree[right(idx)].min)
		{
			tree[idx].min = tree[left(idx)].min;
		}
		else
		{
			tree[idx].min = tree[right(idx)].min;
		}

		if (tree[left(idx)].max > tree[right(idx)].max)
		{
			tree[idx].max = tree[left(idx)].max;
		}
		else
		{
			tree[idx].max = tree[right(idx)].max;
		}
	}
}

void swap(int a, int b)
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int T;
	cin >> T;

	for (int cnt = 0; cnt < T; cnt++)
	{
		int N, M;

		cin >> N;
		cin >> M;

		arr.assign(N, int());
		tree.assign(4 * N, MinMax());

		for (int cnt2 = 0; cnt2 < N; cnt2++)
		{
			arr[cnt2] = cnt2 + 1;
		}
		build(1, 1, N);

		for (int cnt2 = 0; cnt2 < M; cnt2++)
		{
			int order, first, second;

			cin >> order;
			cin >> first;
			cin >> second;

			switch (order)
			{
			case 0:
				update(1, 1, N, first + 1, arr[second]);
				update(1, 1, N, second + 1, arr[first]);
				swap(first, second);
				break;
			case 1:
				MinMax tmp = query(1, 1, N, first + 1, second + 1);
				if (tmp.min == first + 1 && tmp.max == second + 1)
				{
					cout << "YES" << "\n";
				}
				else
				{
					cout << "NO" << "\n";
				}
				break;
			}
		}
	}
}
