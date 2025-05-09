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
		tree[idx].min = arr[start];
		tree[idx].max = arr[start];
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

MinMax qeury(int idx, int start, int end, int l, int r)
{
	if (l > end || r < start) return { 1000000000,1 };
	if (l <= start && r >= end) return tree[idx];

	int mid = (start + end) / 2;

	MinMax leftData = qeury(left(idx), start, mid, l, r);
	MinMax rightData = qeury(right(idx), mid + 1, end, l, r);

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

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M;

	cin >> N;
	cin >> M;

	arr.resize(N + 1);
	tree.resize(4 * N);

	for (int cnt = 1; cnt <= N; cnt++)
	{
		cin >> arr[cnt];
	}

	build(1, 1, N);

	for (int cnt = 0; cnt < M; cnt++)
	{
		int left, right;

		cin >> left;
		cin >> right;

		MinMax prt = qeury(1, 1, N, left, right);

		cout << prt.min << " " << prt.max << "\n";
	}

	return 0;
}
