#include <iostream>
#include <vector>

using namespace std;

int left(int n) { return 2 * n; }
int right(int n) { return 2 * n + 1; }

struct Data
{
	long long num;
	long long sum;
};

vector<Data> tree;
vector<long long> arr;

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx].num = arr[start];
		tree[idx].sum = 0;
	}
	else
	{
		int mid = (start + end) / 2;
		build(left(idx), start, mid);
		build(right(idx), mid + 1, end);
		tree[idx].sum = 0;
	}
}

long long query(int idx, int start, int end, int find)
{
	if (start == end) return tree[idx].num + tree[idx].sum;

	int mid = (start + end) / 2;
	if(find <= mid)
		return tree[idx].sum + query(left(idx), start, mid, find);
	else
		return tree[idx].sum + query(right(idx), mid + 1, end, find);
}

void update(int idx, int start, int end, int l, int r, long long add)
{
	if (l > end || r < start) return;
	if (l <= start && r >= end) 
		tree[idx].sum += add;
	else
	{
		int mid = (start + end) / 2;
		update(left(idx), start, mid, l, r, add);
		update(right(idx), mid + 1, end, l, r, add);
	}
}

void printTree(int idx, int start, int end)
{
	cout << tree[idx].num << " " << tree[idx].sum << "\n";

	if (start != end)
	{
		int mid = (start + end) / 2;
		printTree(left(idx), start, mid);
		printTree(right(idx), mid + 1, end);
	}
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
	{
		cin >> arr[cnt];
	}

	build(1, 1, N);
	
	cin >> M;

	for (int cnt = 0; cnt < M; cnt++)
	{
		int order, first, second;
		long long add;

		cin >> order;
		cin >> first;

		switch (order)
		{
		case 1:
			cin >> second;
			cin >> add;
			update(1, 1, N, first, second, add);
			break;
		case 2:
			cout << query(1, 1, N, first) << "\n";
			break;
		}
	}

	return 0;
}
