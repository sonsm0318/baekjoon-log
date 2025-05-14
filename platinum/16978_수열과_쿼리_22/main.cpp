#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct firstOrder
{
	int find;
	int num;
};

struct secondOrder
{
	int sequence;
	int k;
	int left;
	int right;
	long long answer;
};

vector<int> arr;
vector<long long> tree;
vector<firstOrder> firstQuery;
vector<secondOrder> secondQuery;

void build(int idx, int start, int end)
{
	if (start == end)
		tree[idx] = arr[start];
	else
	{
		int mid = (start + end) / 2;
		build(idx << 1, start, mid);
		build(idx << 1 | 1, mid + 1, end);
		tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
	}
}

void update(int idx, int start, int end, int find, int num)
{
	if (start == end)
		tree[idx] = num;
	else
	{
		int mid = (start + end) / 2;
		if (find <= mid)
			update(idx << 1, start, mid, find, num);
		else
			update(idx << 1 | 1, mid + 1, end, find, num);

		tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
	}
}

long long query(int idx, int start, int end, int l, int r)
{
	if (start > r || end < l) return 0;
	if (l <= start && end <= r) return tree[idx];
	int mid = (start + end) / 2;
	return	query(idx << 1, start, mid, l, r) +
			query(idx << 1 | 1,mid + 1, end, l, r);
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

	for (int i = 0; i < M; i++)
	{
		int order, first, second, third;

		cin >> order;
		cin >> first;
		cin >> second;

		switch (order)
		{
		case 1:
			firstQuery.push_back({ first, second });
			break;
		case 2:
			cin >> third;
			secondQuery.push_back({ i, first, second, third });
			break;
		}
	}
	sort(secondQuery.begin(), secondQuery.end(), [](const secondOrder& a, const secondOrder& b)
		{
			return a.k < b.k;
		});

	int fIdx = 0;

	for (int i = 0; i < secondQuery.size(); i++)
	{
		while (secondQuery[i].k > fIdx)
		{
			update(1, 1, N, firstQuery[fIdx].find, firstQuery[fIdx].num);
			fIdx++;
		}
		secondQuery[i].answer = query(1, 1, N, secondQuery[i].left, secondQuery[i].right);
	}

	sort(secondQuery.begin(), secondQuery.end(), [](const secondOrder& a, const secondOrder& b)
		{
			return a.sequence < b.sequence;
		});

	for (int i = 0; i < secondQuery.size(); i++)
	{
		cout << secondQuery[i].answer << "\n";
	}
}
