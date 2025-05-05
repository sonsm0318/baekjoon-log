#include <iostream>
#include <vector>
using namespace std;

int preOrderArray[100000];

void solve(int len, int first)
{
	if (len <= 0) return;

	int idx = first + 1;
	while (preOrderArray[first] > preOrderArray[idx] && idx < first + len)
	{
		idx++;
	}
	solve(idx - 1 - first, first + 1);
	solve(len - idx + first, idx);

	std::cout << preOrderArray[first] << endl;
}

int main(void)
{
	int val;
	int idx = 0;
	while (cin >> val) 
	{
		preOrderArray[idx++] = val;
	}

	solve(idx, 0);

	return 0;
}
