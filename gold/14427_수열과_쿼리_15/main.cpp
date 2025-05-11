#include <vector>
#include <iostream>
using namespace std;

vector<int> arr;
vector<int> tree;

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx] = start;
	}
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		int l = tree[idx << 1];
		int r = tree[idx << 1 | 1];
		if (arr[l] < arr[r]) tree[idx] = l;
		else if (arr[l] > arr[r]) tree[idx] = r;
		else tree[idx] = min(l, r);
	}
}

int query(int idx, int start, int end, int l, int r)
{
	if (start > r || end < l) return 0;
	if (l <= start && end <= r) return tree[idx];
	int mid = (start + end) / 2;
	int left = query(idx << 1, start, mid, l, r);
	int right = query(idx << 1 | 1, mid + 1, end, l, r);

	if (arr[left] < arr[right])
		return left;
	if (arr[left] > arr[right])
		return right;
	else
		return left < right ? left : right;
}

void update(int idx, int start, int end, int find, int num)
{
	if (start == end)
	{
		return;
	}
	else
	{
		int mid = (start + end) / 2;
		if(find <= mid)
			update(idx << 1, start, mid, find, num);
		else
			update(idx << 1 | 1, mid + 1, end, find, num);
		int l = tree[idx << 1];
		int r = tree[idx << 1 | 1];
		if (arr[l] < arr[r]) tree[idx] = l;
		else if (arr[l] > arr[r]) tree[idx] = r;
		else tree[idx] = min(l, r);
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
		cin >> arr[cnt];

	arr[0] = 1000000000;
	build(1,1,N);

	cin >> M;

	for (int cnt = 0; cnt < M; cnt++)
	{
		int order, first, second;

		cin >> order;


		switch (order)
		{
		case 1:
			cin >> first;
			cin >> second;
			arr[first] = second;
			update(1, 1, N, first, second);
			break;
		case 2:
			cout << tree[1] << "\n";
			break;
		}
	}

	return 0;
}
