#include <iostream>
using namespace std;

long long arr[10];

void getAnswer(int N)
{
	int factor = 1;
	while (N / factor > 0)
	{
		int left = N / (factor * 10);
		int cur = (N / factor) % 10;
		int right = N % factor;

		for (int i = 0; i <= 9; ++i)
		{
			if (i == 0) 
			{
				if (cur < i)
					arr[i] += left * factor;
				arr[i] -= factor;
			}

			if (cur > i)
				arr[i] += (left + 1) * factor;
			else if (cur == i)
				arr[i] += left * factor + (right + 1);
			else
				arr[i] += left * factor;
		}
		factor *= 10;
	}
}

int main(void)
{
	int N;

	cin >> N;

	getAnswer(N);

	for (int i = 0; i < 10; i++)
		cout << arr[i] << " ";

	return 0;
}