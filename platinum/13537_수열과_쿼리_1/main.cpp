#include <iostream>
#include <vector>]
#include <algorithm>
using namespace std;

vector<int> arr;
vector<vector<int>> tree;

void merge(vector<int>& arr, vector<int>& leftArr, vector<int>& rightArr)
{
	arr.resize(leftArr.size() + rightArr.size());
	int arrIdx = 0;
	int leftIdx = 0;
	int rightIdx = 0;

	while (leftIdx < leftArr.size() && rightIdx < rightArr.size())
	{
		if (leftArr[leftIdx] < rightArr[rightIdx])
		{
			arr[arrIdx++] = leftArr[leftIdx++];
		}
		else
		{
			arr[arrIdx++] = rightArr[rightIdx++];
		}
	}
	while (leftIdx < leftArr.size())
	{
		arr[arrIdx++] = leftArr[leftIdx++];
	}
	while (rightIdx < rightArr.size())
	{
		arr[arrIdx++] = rightArr[rightIdx++];
	}
}

void build(int idx, int  start, int end)
{
	if (start == end)
	{
		tree[idx].resize(1);
		tree[idx][0] = arr[start];
	}
	else
	{
		int mid = (start + end) / 2;
		build(2 * idx, start, mid);
		build(2 * idx + 1, mid + 1, end);
		merge(tree[idx], tree[2 * idx], tree[2 * idx + 1]);
	}
}

int countGreater(int idx, int s, int e, int l, int r, int k) {
	if (r < s || e < l) return 0;       
	if (l <= s && e <= r) 
	{              
		auto it = upper_bound(tree[idx].begin(), tree[idx].end(), k);
		return tree[idx].end() - it;     
	}
	int mid = (s + e) / 2;
	return countGreater(idx << 1, s, mid, l, r, k) +
		countGreater(idx << 1 | 1, mid + 1, e, l, r, k);
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

	int N, M;

	cin >> N;
	arr.resize(N + 1);
	tree.resize(4 * N);
	for (int cnt2 = 1; cnt2 <= N; cnt2++)
		cin >> arr[cnt2];

	build(1, 1, N);

	cin >> M;


	for (int cnt2 = 0; cnt2 < M; cnt2++)
	{
		int order, first, second;
		vector<int> tmp;

		cin >> order;
		cin >> first;
		cin >> second;

		cout << countGreater(1, 1, N, order, first, second) << "\n";
			
	}
}
