#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> nodeArray;
bool visited[500];
bool loopCheck;
int treeNum;

void clearVisited(int len)
{
	for (int cnt = 0; cnt < len; cnt++)
		visited[cnt] = 0;
}

void DFS(int n, int prev)
{
	visited[n] = true;

	for (int cnt = 0; cnt < nodeArray[n].size(); cnt++)
	{
		if (visited[nodeArray[n][cnt]] == false)
		{
			DFS(nodeArray[n][cnt], n);
		}
		else if (nodeArray[n][cnt] != prev)
		{
			loopCheck = true;
		}
	}
}

int main(void)
{
	int d = 1;
	while (1)
	{
		int N, M;
		cin >> N;
		cin >> M;
		if (N == 0 && M == 0)
			break;

		nodeArray.resize(N);

		for (int cnt = 0; cnt < M; cnt++)
		{
			int first, second;

			cin >> first;
			cin >> second;

			nodeArray[first - 1].push_back(second - 1);
			nodeArray[second - 1].push_back(first - 1);
		}
		treeNum = 0;
		clearVisited(N);

		for (int cnt = 0; cnt < N; cnt++)
		{
			if (visited[cnt] == false)
			{
				loopCheck = false;
				DFS(cnt, -1);
				if (loopCheck == false)
				{
					treeNum++;
				}
			}
		}

		if (treeNum == 0)
		{
			cout << "Case " << d << ": No trees." << endl;
		}
		else if (treeNum == 1)
		{
			cout << "Case " << d << ": There is one tree." << endl;
		}
		else
		{
			cout << "Case " << d << ": A forest of " << treeNum << " trees." << endl;
		}

		for (int cnt = 0; cnt < N; cnt++)
		{
			nodeArray[cnt].clear();
		}
		d++;
	}

	return 0;
}
