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

	//InCount��¼ÿ��������
	int *InCount = new int[NodeNum];
	for (int i = 0; i < NodeNum; ++i)
		InCount[i] = 0;
	//��ʼ���������� [���]
	for (int i = 0; i < NodeNum; ++i)
		for (int j = 0; j < NodeNum; ++j)
			if (AOV[j][i] != 0)
				InCount[i]++;

	//����һ��ջ��ջ�б������Ϊ0�ĵ�
	stack<int> s;
	//��ʼ��ջ�������Ϊ0�ĵ����
	for (int i = 0; i < NodeNum; ++i)
		if (InCount[i] == 0)
			s.push(i);

	//��������
	for (int i = 0; i < NodeNum; ++i)
	{
		//���ջ�����е�������֮ǰ��Ϊ�գ�˵���л�
		if (s.empty())
		{
			cout << "There is a cycle in network!" << endl;
			delete[] InCount;
			return -1;
		}
		else
		{
			//����һ�㣬�����ʸõ�
			int v = s.top();
			s.pop();
			Result[i] = v;

			//����v���ڽӶ��㣬�������-1��Ϊ0��ѹջ
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

//�ɹ����عؼ�·���϶�������ʧ�ܷ���-1
int CriticalPath(int AOE[][N], Edge Result[], int NodeNum)
{
	if (NodeNum <= 0)
		return -1;
	int *TopoSec = new int[NodeNum];
	if (TopoOrder(AOE, TopoSec, NodeNum) == 0)
	{
		//�¼������㣩���緢��ʱ��ve[0] = 0, ve[j] = max{ve[i] + w(i,j) | e<i,j> in E(G)}
		int* ve = new int[NodeNum];
		//��ʼ��(����󣬳�ʼ������С)
		for (int i = 0; i < NodeNum; ++i)
			ve[i] = 0;
		//�����¼����緢��ʱ��
		for (int i = 0; i < NodeNum; ++i)
		{
			int k = TopoSec[i];//��������˳��
			for (int j = 0; j < NodeNum; ++j)
				if (AOE[k][j] != 0 && ve[k] + AOE[k][j] > ve[j])
					ve[j] = ve[k] + AOE[k][j];
		}

		//�¼������㣩������ʱ��vl[n-1] = ve[n-1], vl[j] = min{vl[k] - w(j,k) | e<j,k> in E(G)}
		int* vl = new int[NodeNum];
		//��ʼ��(����С��ʼ�������)
		for (int i = 0; i < NodeNum; ++i)
			vl[i] = ve[NodeNum - 1];
		//�����¼�������ʱ��
		for (int i = NodeNum - 1; i > -1; --i)
		{
			int k = TopoSec[i];//������������
			for (int j = 0; j < NodeNum; ++j)
				if (AOE[k][j] != 0 && vl[j] - AOE[k][j] < vl[k])
					vl[k] = vl[j] - AOE[k][j];
		}

		//���������������ʼʱ�䣬���e[i]==l[i]��ûΪ�ؼ��
		//e(j) = ve[i], l(j) = vl[k]-w(i,k)  ����·����ͼ O(i)--(j)--O(k)
		int e, l, index=0;
		for (int i = 0; i < NodeNum; ++i)
		{
			int k = TopoSec[i];//�������������
			for (int j = 0; j < NodeNum; ++j)
				if (AOE[k][j] != 0)
				{
					e = ve[k];
					l = vl[j] - AOE[k][j];
					if (l == e)//�ؼ�·��
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