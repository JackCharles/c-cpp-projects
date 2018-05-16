#include <iostream>
using namespace std;

#define N 6
#define MAX 0x7FFFFFFF

//Dijkstra�㷨
//path dist�ֱ��¼��ǰ�ڵ��ǰ���������·��
int DShortestPath(int Edge[][N], int v, int path[], int dist[], int NodeNum)
{
	if (NodeNum < 1 || v < 0 || v >= NodeNum)
		return -1;

	//visited ��¼��ǰ���Ƿ񱻷���
	int *visited = new int[NodeNum];
	for (int i = 0; i < NodeNum; ++i)
	{
		path[i] = -1;
		dist[i] = MAX;//Ҫ����Сֵ
		visited[i] = 0;
	}

	dist[v] = 0;//���Լ��ľ���Ϊ0

	//��ʣ��N-1��������̾���
	for (int i = 0; i < NodeNum - 1; ++i)
	{
		visited[v] = 1;//����v
		//����vδ�����ʵ��ڽӵ��dist��path��dist������һ�δε����¼�С
		for (int j = 0; j < NodeNum; ++j)
			if (Edge[v][j] != 0 && visited[j] == 0 && dist[v] + Edge[v][j] < dist[j])
			{
				dist[j] = dist[v] + Edge[v][j];
				path[j] = v;
			}

		//Ѱ����һ�������ʵĵ�(δ���ʹ���dist��С���Ǹ���)
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