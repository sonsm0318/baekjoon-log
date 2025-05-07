#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

struct Data
{
	string word;
	int len;
	int num;
};

Data arr[100000];
Data sorted[100000];

void merge(int left, int mid, int right)
{
	int leftIdx = left;
	int midIdx = mid + 1;
	int sortedIdx = left;

	while (leftIdx <= mid && midIdx <= right)
	{
		if (arr[leftIdx].num > arr[midIdx].num)
		{
			sorted[sortedIdx++] = arr[leftIdx++];
		}
		else if (arr[leftIdx].num < arr[midIdx].num)
		{
			sorted[sortedIdx++] = arr[midIdx++];
		}
		else
		{
			if (arr[leftIdx].len > arr[midIdx].len)
			{
				sorted[sortedIdx++] = arr[leftIdx++];
			}
			else if (arr[leftIdx].len < arr[midIdx].len)
			{
				sorted[sortedIdx++] = arr[midIdx++];
			}
			else
			{
				if (arr[leftIdx].word < arr[midIdx].word)
				{
					sorted[sortedIdx++] = arr[leftIdx++];
				}
				else
				{
					sorted[sortedIdx++] = arr[midIdx++];
				}
			}
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

	for (int i = left; i <= right; i++)
	{
		arr[i] = sorted[i];
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

	unordered_map<string, int> myMap;
	string tmp;
	int N, M;

	cin >> N;
	cin >> M;

	int idx = 0;

	for (int cnt = 0; cnt < N; cnt++)
	{
		cin >> tmp;

		if (tmp.length() >= M)
		{
			if (++myMap[tmp] == 1)
			{
				arr[idx].word = tmp;
				arr[idx].len = tmp.length();
				idx++;
			}
		}
	}

	for (int cnt = 0; cnt < idx; cnt++)
	{
		arr[cnt].num = myMap[arr[cnt].word];
	}

	mergeSort(0, idx - 1);

	for (int cnt = 0; cnt < idx; cnt++)
	{
		cout << arr[cnt].word << "\n";
	}

	return 0;
}
