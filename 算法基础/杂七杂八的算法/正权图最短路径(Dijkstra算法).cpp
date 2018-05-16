#include <iostream>
using namespace std;

#define N 6
#define MAX 0x7FFFFFFF

//Dijkstra算法
//path dist分别记录当前节点的前驱结点和最短路径
int DShortestPath(int Edge[][N], int v, int path[], int dist[], int NodeNum)
{
	if (NodeNum < 1 || v < 0 || v >= NodeNum)
		return -1;

	//visited 记录当前节是否被访问
	int *visited = new int[NodeNum];
	for (int i = 0; i < NodeNum; ++i)
	{
		path[i] = -1;
		dist[i] = MAX;//要找最小值
		visited[i] = 0;
	}

	dist[v] = 0;//到自己的距离为0

	//求到剩余N-1个结点的最短距离
	for (int i = 0; i < NodeNum - 1; ++i)
	{
		visited[v] = 1;//访问v
		//更新v未被访问的邻接点的dist和path，dist在这样一次次迭代下减小
		for (int j = 0; j < NodeNum; ++j)
			if (Edge[v][j] != 0 && visited[j] == 0 && dist[v] + Edge[v][j] < dist[j])
			{
				dist[j] = dist[v] + Edge[v][j];
				path[j] = v;
			}

		//寻找下一个待访问的点(未访问过且dist最小的那个点)
		int ldist = MAX;
		for (int j = 0; j < NodeNum; ++j)
			if (visited[j] == 0 && dist[j] < ldist)
			{
				ldist = dist[j];
				v = j;
			}
	}

	delete[] visited;
	return 0;
}


int main()
{
	int Graph[N][N] = {
		{0, 12, 5, 8, 0, 0},
		{12, 0, 5, 0, 20, 0},
		{5, 5, 0, 6, 10, 8},
		{8, 0, 6, 0, 0, 4},
		{0, 20, 10, 0, 0, 9},
		{0, 0, 8, 4, 9, 0}
	};

	int dist[N], path[N];

	if (DShortestPath(Graph, 0, path, dist, N) == 0)
	{
		for (int i = 0; i < N; ++i)
		{
			if (dist[i] > 0)
			{
				cout << "0->" << i << ": " << dist[i] << " [" << i;
				int j = i;
				while (path[j] != -1)
				{
					cout << "<--" << path[j];
					j = path[j];
				}
				cout << "]" << endl;
			}
		}
	}
	return 0;
}