#include <iostream>
#include <stack>
using namespace std;

#define N 9

struct Edge
{
	int head;
	int tail;
};

int TopoOrder(int AOV[][N], int Result[], int NodeNum)
{
	if (NodeNum <= 0)
		return -1;

	//InCount记录每个点的入度
	int *InCount = new int[NodeNum];
	for (int i = 0; i < NodeNum; ++i)
		InCount[i] = 0;
	//初始化化各顶点 [入度]
	for (int i = 0; i < NodeNum; ++i)
		for (int j = 0; j < NodeNum; ++j)
			if (AOV[j][i] != 0)
				InCount[i]++;

	//创建一个栈，栈中保存入度为0的点
	stack<int> s;
	//初始化栈，将入度为0的点输出
	for (int i = 0; i < NodeNum; ++i)
		if (InCount[i] == 0)
			s.push(i);

	//拓扑排序
	for (int i = 0; i < NodeNum; ++i)
	{
		//如果栈在所有点输出完成之前就为空，说明有环
		if (s.empty())
		{
			cout << "There is a cycle in network!" << endl;
			delete[] InCount;
			return -1;
		}
		else
		{
			//弹出一点，并访问该点
			int v = s.top();
			s.pop();
			Result[i] = v;

			//遍历v的邻接顶点，将其入度-1，为0则压栈
			for (int j = 0; j < NodeNum; ++j)
				if (AOV[v][j] != 0)
				{
					--InCount[j];
					if (InCount[j] == 0)
						s.push(j);
				}
		}
	}

	delete[] InCount;
	return 0;
}

//成功返回关键路径上顶点数，失败返回-1
int CriticalPath(int AOE[][N], Edge Result[], int NodeNum)
{
	if (NodeNum <= 0)
		return -1;
	int *TopoSec = new int[NodeNum];
	if (TopoOrder(AOE, TopoSec, NodeNum) == 0)
	{
		//事件（顶点）最早发生时间ve[0] = 0, ve[j] = max{ve[i] + w(i,j) | e<i,j> in E(G)}
		int* ve = new int[NodeNum];
		//初始化(求最大，初始化成最小)
		for (int i = 0; i < NodeNum; ++i)
			ve[i] = 0;
		//计算事件最早发生时间
		for (int i = 0; i < NodeNum; ++i)
		{
			int k = TopoSec[i];//拓扑排序顺序
			for (int j = 0; j < NodeNum; ++j)
				if (AOE[k][j] != 0 && ve[k] + AOE[k][j] > ve[j])
					ve[j] = ve[k] + AOE[k][j];
		}

		//事件（顶点）最晚发生时间vl[n-1] = ve[n-1], vl[j] = min{vl[k] - w(j,k) | e<j,k> in E(G)}
		int* vl = new int[NodeNum];
		//初始化(求最小初始化成最大)
		for (int i = 0; i < NodeNum; ++i)
			vl[i] = ve[NodeNum - 1];
		//计算事件最晚发生时间
		for (int i = NodeNum - 1; i > -1; --i)
		{
			int k = TopoSec[i];//拓扑排序逆序
			for (int j = 0; j < NodeNum; ++j)
				if (AOE[k][j] != 0 && vl[j] - AOE[k][j] < vl[k])
					vl[k] = vl[j] - AOE[k][j];
		}

		//求各活动的最早和最晚开始时间，如果e[i]==l[i]则该活动为关键活动
		//e(j) = ve[i], l(j) = vl[k]-w(i,k)  其中路径如图 O(i)--(j)--O(k)
		int e, l, index=0;
		for (int i = 0; i < NodeNum; ++i)
		{
			int k = TopoSec[i];//按拓扑排序遍历
			for (int j = 0; j < NodeNum; ++j)
				if (AOE[k][j] != 0)
				{
					e = ve[k];
					l = vl[j] - AOE[k][j];
					if (l == e)//关键路径
					{
						Result[index].head = k;
						Result[index++].tail = j;
					}
				}
		}

		delete[] ve;
		delete[] vl;
		delete[] TopoSec;
		return index;
	}	

	delete[] TopoSec;
	return -1;
}


int main()
{
	int G[N][N] = {
		{0, 6, 4, 5, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 2, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 9, 8, 0},
		{0, 0, 0, 0, 0, 0, 0, 4, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 4},
		{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};

	Edge Res[N];
	int n = CriticalPath(G, Res, N);
	if (n != -1)
		for (int i = 0; i < n; ++i)
			cout << Res[i].head << "---->" << Res[i].tail << endl;

	return 0;
}