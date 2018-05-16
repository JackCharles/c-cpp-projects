#include <iostream>
#include <queue>
using namespace std;

#define N 7

//核心广度优先遍历+dist+path
int ShortestPath_NoWeight(int Edge[][N], int v, int dist[], int path[], int NodeNum)
{
	if (NodeNum < 1 || v < 0 || v >= NodeNum)
		return -1;

	//采用广度优先遍历， dist[i]表示v到i号顶点的最短路径
	//path[i]表示v到i这条路径上i的前驱结点
	queue<int> q;
	for (int i = 0; i < NodeNum; ++i)
	{
		dist[i] = -1;//-1表示未曾访问过
		path[i] = -1;//-1表示不可达
	}
	dist[v] = 0;
	q.push(v);

	while (!q.empty())
	{
		int CurrNode = q.front();
		q.pop();

		//访问currnode的邻接点
		for(int i=0;i<NodeNum;++i)
			if (Edge[CurrNode][i] != 0 && dist[i] == -1)
			{
				q.push(i);
				//更新距离和前驱结点（能访问到说明可达）
				dist[i] = dist[CurrNode] + 1;
				path[i] = CurrNode;
			}
	}
	return 0;
}




int main()
{
	int Graph[N][N] = {
		{0,1,0,1,0,0,0},
		{0,0,0,1,1,0,0},
		{1,0,0,0,0,1,0},
		{0,0,1,0,1,1,1},
		{0,0,0,0,0,0,1},
		{0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0}
	};

	int path[N], dist[N];
	if (ShortestPath_NoWeight(Graph, 2, dist, path, N) == 0)
	{
		for (int i = 0; i < N; ++i)
		{
			if (dist[i] > 0)
			{
				cout << "2->" << i << ": " << dist[i] << " [" << i;
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