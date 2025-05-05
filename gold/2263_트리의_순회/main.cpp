#include <iostream>
#include <vector>
using namespace std;

int inOrderArray[100000];
int hashInOrderArray[100000];
int postOrderArray[100000];

void solve(int iStart, int iEnd, int pStart, int pEnd)
{
	if (iStart > iEnd || pStart > pEnd)
	{
		return;
	}

	int root = postOrderArray[pEnd];
	cout << root << " ";

	int idx = hashInOrderArray[root];

	int leftSize = idx - iStart;

	solve(iStart, idx - 1, pStart, pStart + leftSize - 1);
	solve(idx + 1, iEnd, pStart + leftSize, pEnd - 1);
}

int main(void)
{
	int N;
	cin >> N;

	for (int cnt = 0; cnt < N; cnt++)
	{
		cin >> inOrderArray[cnt];
		hashInOrderArray[inOrderArray[cnt]] = cnt;
	}
	for (int cnt = 0; cnt < N; cnt++)
	{
		cin >> postOrderArray[cnt];
	}

	solve(0, N - 1, 0, N - 1);

	return 0;
}
