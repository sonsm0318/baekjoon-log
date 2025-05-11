#include <iostream>
#include <vector>
using namespace std;

struct Node
{
	int left;
	int right;
	int sum;
};

vector<int> arr;
vector<Node> tree;

void pull(int idx)
{
	tree[idx].left = tree[idx << 1].sum;
	tree[idx].right = tree[idx << 1 | 1].sum;
	tree[idx].sum = tree[idx].left + tree[idx].right;
}

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx].sum = arr[start];
		tree[idx].left = 0;
		tree[idx].right = 0;
	}
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		pull(idx);
	}
}

int query(int idx, int start, int end, int find)
{
	if (start == end)
	{
		tree[idx].sum = 0;
		return 1;
	}	
	int mid = (start + end) / 2;
	int ret;
	if (find <= mid)
		ret =  query(idx << 1, start, mid, find);
	else
		ret =  query(idx << 1 | 1, mid + 1, end, find) + tree[idx].left;
	pull(idx);
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
		cin >> arr[cnt];
	
	build(1, 1, N);

	for (int cnt = 0; cnt < M; cnt++)
		cin >> arr[cnt];

	for (int cnt = 0; cnt < M; cnt++)
	{
		cout << query(1, 1, N, arr[cnt]) << " ";
	}
}
