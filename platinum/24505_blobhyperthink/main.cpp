#include <iostream>
#include <vector>
using namespace std;

#define MOD (1e9 + 7)
#define N 100001

int tree[12][N];

void update(int curr, int last, int val)
{
	while(last < N)
	{
		tree[curr][last] += val;
		if (tree[curr][last] >= MOD)
			tree[curr][last] -= MOD;
		last += last & -last;
	}
}

int query(int curr, int last)
{
	int ret = 0;

	while(last > 0)
	{
		ret += tree[curr][last];
		if (ret >= MOD)
			ret -= MOD;
		last -= last & -last;
	}
	return ret;
}

int main(void)
{
	int n;
	cin >> n; 

	for (int i = 1; i <= n; i++)
	{
		int x;
		cin >> x;
		update(1, x, 1);
		for (int k = 2; k < 12; k++)
		{
			int val(query(k - 1, x - 1));
			update(k, x, val);
		}
	}
	cout << query(11, 1e5);

	return 0;
}