#include <iostream>
#include <vector>
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
		tree[idx][0] = start;
	}
	else
	{
		int mid = (start + end) / 2;
		build(2 * idx, start, mid);
		build(2 * idx + 1, mid + 1, end);
		merge(tree[idx], tree[2 * idx], tree[2 * idx + 1]);
	}
}

vector<int> query(int idx, int start, int end, int l, int r)
{
	if (l > end || r < start) return vector<int>();
	if (l <= start && r >= end) return tree[idx];
	else
	{
		vector<int> ret;
		int mid = (start + end) / 2;
		vector<int> left = query(2 * idx, start, mid, l, r);
		vector<int> right = query(2 * idx + 1, mid + 1, end, l, r);
		merge(ret, left, right);
		return ret;
	}
}

void update(int idx, int start, int end, int change, int num)
{
	if (start == end)
	{
		tree[idx][0] = num;
	}
	else
	{
		int mid = (start + end) / 2;

		if (change <= mid)
			update(2 * idx, start, mid, change, num);
		if (change > mid)
			update(2 * idx + 1, mid + 1, end, change, num);
		merge(tree[idx], tree[2 * idx], tree[2 * idx + 1]);
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
		tree.assign(4 * N, vector<int>());

		for (int cnt2 = 0; cnt2 < N; cnt2++)
		{
			arr[cnt2] = cnt2 + 1;
		}
		build(1, 1, N);

		for (int cnt2 = 0; cnt2 < M; cnt2++)
		{
			int order, first, second;
			vector<int> tmp;

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
				tmp = query(1, 1, N, first + 1, second + 1);
				if (tmp[0] == first + 1 && tmp[second - first] == second + 1)
				{
					cout << "Yes" << "\n";
				}	
				else
				{
					cout << "No" << "\n";
				}
				break;
			}
		}
	}
}
