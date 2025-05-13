#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> arr;
vector<vector<int>> tree;

void merge(vector<int>& ret, vector<int>& left, vector<int>& right)
{
	ret.resize(left.size() + right.size());
	int l = 0;
	int m = 0;
	int r = 0;

	while (l < left.size() && m < right.size())
	{
		if (left[l] < right[m])
			ret[r++] = left[l++];
		else
			ret[r++] = right[m++];
	}

	while (l < left.size())
		ret[r++] = left[l++];
	
	while (m < right.size())
		ret[r++] = right[m++];
}

void build(int idx, int start, int end)
{
	if (start == end)
	{
		tree[idx].resize(1);
		tree[idx][0] = arr[start];
	}
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);

		merge(tree[idx], tree[idx << 1], tree[idx << 1 | 1]);
	}
}

int query(int idx, int start, int end, int l, int r, int least)
{
	if (start > r || end < l) return 0;
	if (l <= start && end <= r)
	{
		int ret = tree[idx].end() - upper_bound(tree[idx].begin(), tree[idx].end(), least);
		return ret;
	}
	int mid = (start + end) / 2;
	return query(idx << 1, start, mid, l, r, least) + query(idx << 1 | 1, mid + 1, end, l, r, least);
}


int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	arr.resize(N + 1);
	tree.resize(4 * N);

	for (int i = 1; i <= N; i++)
		cin >> arr[i];

	build(1, 1, N);

	int M;
	cin >> M;

	int answer = 0;

	for (int cnt = 0; cnt < M; cnt++)
	{
		int a, b, c;

		cin >> a;
		cin >> b;
		cin >> c;
		
		int i = a^answer;
		int j = b^answer;
		int k = c^answer;

		if (i > j) swap(i, j);

		answer = query(1, 1, N, i, j, k);
		cout << answer << "\n";
	}
}
