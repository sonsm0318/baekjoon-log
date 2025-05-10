#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
vector<int> sorted;
long long totalCnt = 0;

void merge(int left, int mid, int right)
{
	int tmpCnt = mid - left + 1;
	int leftIdx = left;
	int midIdx = mid + 1;
	int sortedIdx = left;

	while (leftIdx <= mid && midIdx <= right)
	{
		if (arr[leftIdx] <= arr[midIdx])
		{
			sorted[sortedIdx++] = arr[leftIdx++];
			tmpCnt--;
		}
		else
		{
			sorted[sortedIdx++] = arr[midIdx++];
			totalCnt += tmpCnt;
		}
	}
	while (leftIdx <= mid)
	{
		sorted[sortedIdx++] = arr[leftIdx++];
	}
	while (midIdx <= right)
	{
		sorted[sortedIdx++] = arr[midIdx++];
	}

	for (int cnt = left; cnt <= right; cnt++)
	{
		arr[cnt] = sorted[cnt];
	}
}

void mergeSort(int left, int right)
{
	if (right <= left) return;

	int mid = (right + left) / 2;
	mergeSort(left, mid);
	mergeSort(mid + 1, right);
	merge(left, mid, right);
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	
	arr.resize(N);
	sorted.resize(N);

	for (int cnt = 0; cnt < N; cnt++)
		cin >> arr[cnt];

	mergeSort(0, N - 1);

	cout << totalCnt;

	return 0;
}
