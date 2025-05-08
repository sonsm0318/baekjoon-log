#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> arr;

int visited[100001];
int sequence = 1;

void DFS(int current)
{
	visited[current] = sequence++;

	for (int cnt = 0; cnt < arr[current].size(); cnt++)
	{
		if (!visited[arr[current][cnt]])
		{
			DFS(arr[current][cnt]);
		}
	}
}

int main(void)
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, R;

	cin >> N;
	cin >> M;
	cin >> R;

	arr.resize(N + 1);

	for (int cnt = 0; cnt < M; cnt++)
	{
		int first, second;

		cin >> first;
		cin >> second;

		arr[first].push_back(second);
		arr[second].push_back(first);
	}

	for (int cnt = 1; cnt <= N; cnt++)
	{
		sort(arr[cnt].rbegin(), arr[cnt].rend());
	}
		
	DFS(R);

	for (int cnt = 1; cnt <= N; cnt++)
	{
		cout << visited[cnt] << "\n";
	}

	return 0;
}
