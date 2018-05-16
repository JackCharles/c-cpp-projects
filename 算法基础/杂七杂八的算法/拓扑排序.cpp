#include <iostream>
#include <stack>
using namespace std;

#define N 5

//拓扑排序：（1）找入度为0的点，并删除这些点及其出边
//         （2）重复上述过程直到所有点输出，或剩余点
//	          入度均不为0，则有环存在。
//实现时，用栈来保存入度为0的点，依次遍历栈中的点，并将
//后续入度为0的点压栈，如果栈为空，但点未完全输出则证明
//有环路存在。

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


int main()
{
	//有向图邻接矩阵
	int AOV[N][N] = {
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 0, 0, 1},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0}
	};

	int Result[N];
	if(!TopoOrder(AOV, Result, N))
	for (int i = 0; i < N; ++i)
		cout << Result[i] << " ";
	cout << endl;

	return 0;
}