#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int arr[8001];
int sortedArr[500000];

int main(void)
{
	int N;
	cin >> N;

	int sum = 0;
	int max = -4000;
	int min = 4000;

	for (int cnt = 0; cnt < N; cnt++)
	{
		int tmp;
		cin >> tmp;
		arr[tmp + 4000]++;

		sum += tmp;

		if (max < tmp)
		{
			max = tmp;
		}
		if (min > tmp)
		{
			min = tmp;
		}
	}

	int mode = min + 4000;
	bool secondCheck = true;

	int idx = 0;

	int maxFreq = 0;
	for (int i = 8000; i >= 0; i--) 
	{
		if (arr[i] > maxFreq)
			maxFreq = arr[i];

		for(int j = 0; j < arr[i]; j++)
			sortedArr[idx++] = i - 4000;

	}

	for (int i = 0; i < 8001; i++)
	{
		if (arr[i] == maxFreq && secondCheck)
		{
			mode = i;
			secondCheck = false;
		}
		else if (arr[i] == maxFreq)
		{
			mode = i;
			break;
		}
	}

	int center = sortedArr[(N - 1) / 2];

	cout << ((sum >= 0) ? (int)((double)sum / N + 0.5) : (int)((double)sum / N - 0.5)) << endl;
	cout << center << endl;
	cout << mode - 4000 << endl;
	cout << max - min << endl;

	return 0;
}
