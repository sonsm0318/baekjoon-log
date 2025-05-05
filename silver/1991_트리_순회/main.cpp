#include <iostream>
#include <vector>
using namespace std;

struct Node
{
	char left;
	char right;
};

vector<vector<Node>> graph(26);

void SearchRoot(char n)
{
	cout << n;

	if (graph[n - 65][0].left != '.')
	{
		SearchRoot(graph[n - 65][0].left);
	}
	if (graph[n - 65][0].right != '.')
	{
		SearchRoot(graph[n - 65][0].right);
	}
}

void SearchLeft(char n)
{
	if (graph[n - 65][0].left != '.')
	{
		SearchLeft(graph[n - 65][0].left);
	}

	cout << n;

	if (graph[n - 65][0].right != '.')
	{
		SearchLeft(graph[n - 65][0].right);
	}
}

void SearchRight(char n)
{
	if (graph[n - 65][0].left != '.')
	{
		SearchRight(graph[n - 65][0].left);
	}
	if (graph[n - 65][0].right != '.')
	{
		SearchRight(graph[n - 65][0].right);
	}

	cout << n;
}

int main(void)
{
	int N;
	cin >> N;

	for (int cnt = 0; cnt < N; cnt++)
	{
		char parent, left, right;
		cin >> parent;
		cin >> left;
		cin >> right;

		graph[parent - 65].push_back({ left,right });
	}

	SearchRoot('A');
	cout << endl;
	SearchLeft('A');
	cout << endl;
	SearchRight('A');
	cout << endl;

	return 0;
}
