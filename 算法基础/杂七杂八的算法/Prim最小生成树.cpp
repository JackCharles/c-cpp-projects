#include <iostream>
using namespace std;

#define N 6 //顶点数
#define MAX 0x7FFFFFFF //有符号int最大值

//邻接矩阵
int edge[N][N] = {
	{0, 1, 4, 7, 0, 0},
	{1, 0, 4, 0, 0, 2},
	{4, 4, 0, 2, 3, 5},
	{7, 0, 2, 0, 6, 0},
	{0, 0, 3, 6, 0, 3},
	{0, 2, 5, 0, 3, 0}
};

//closedge结构：每个顶点一个closedge,U中的closedge中
//只有Vex字段有效，用于标识此点已经处理完成。V中closedge
//中Lowcost表示该点到U中的一个[最短]路径，Vex记录这条路径
//在U中的端点。
struct CLE
{
	int Vex;
	int Lowcost;
};

//MST结构记录选出来的边，由这些边构成最小生成树
struct MST
{
	int head;//边的起始点
	int tail;//边的结束点
	int cost;//权值
};


//普里姆算法，求最小生成树(支撑树)，它将顶点分为两个集合U和V
//U表示处理完的点，V表示剩余未处理的点，每次只需要在V中找一个
//到集合U的权值最小的点加入U中，直到所有点加入U中即可。
void Prim(int Edge[][N], MST* Result, int NodeNum)
{
	if (NodeNum <= 0)
		return;

	//初始化邻接矩阵,将0全部改为MAX，方便下面查找最小路径
	for (int i = 0; i < NodeNum; ++i)
		for (int j = 0; j < NodeNum; ++j)
			if (Edge[i][j] == 0)
				Edge[i][j] = MAX;

	//初始化closedge结构,每个顶点一个
	CLE *closedge = new CLE[NodeNum];
	for (int i = 0; i < NodeNum; ++i)
	{
		//初始选择0号点在U中，其余顶点到U中的距离就是到0点的距离
		closedge[i].Lowcost = Edge[0][i];
		closedge[i].Vex = 0;//U中端点全是0号
	}
	closedge[0].Vex = -1;//-1代表0点已经加入U中
	int count = 1;//U中顶点个数

	//构造最小支撑树
	for (int i = 1; i < NodeNum; ++i)//将剩余的NodeNum-1个点加入U中
	{
		int MinLowCost = MAX;//寻找V到U中最短路径的边，即找最小Lowcost
		int v = 0;//记录V中选中的点,最后为0则为没有找到

		for (int j = 0; j < NodeNum; ++j)//这儿只能从0开始遍历，因为V中剩余点没有规律
			if (closedge[j].Vex != -1 && closedge[j].Lowcost < MinLowCost)
			{
				MinLowCost = closedge[j].Lowcost;
				v = j;
			}

		//将选中的V中的点v加入U中
		if (v != 0)
		{
			Result[count - 1].head = closedge[v].Vex + 1;
			Result[count - 1].tail = v + 1;
			Result[count - 1].cost = closedge[v].Lowcost;
			++count;
			closedge[v].Vex = -1;//将该点标记为在U中
		}

		//U中点发生变化，需要更新V中剩余点到U中点的最小距离
		//但由于这个变化只是由新加入的v引起的，所以只需要和
		//该点与v构成的边比较即可。
		for (int j = 0; j < NodeNum; ++j)
			if (closedge[j].Vex != -1 && closedge[j].Lowcost > Edge[v][j])
			{
				closedge[j].Lowcost = Edge[v][j];
				closedge[j].Vex = v;
			}
	}
	delete[] closedge;//千万别忘了
}

int main()
{
	MST Result[N - 1];
	Prim(&edge[0], Result, N);
	for (int i = 0; i < N - 1; ++i)
		cout << Result[i].head << "--" << Result[i].cost << "-->" << Result[i].tail << endl;
}