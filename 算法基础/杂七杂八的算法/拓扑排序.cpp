#include <iostream>
#include <stack>
using namespace std;

#define N 5

//�������򣺣�1�������Ϊ0�ĵ㣬��ɾ����Щ�㼰�����
//         ��2���ظ���������ֱ�����е��������ʣ���
//	          ��Ⱦ���Ϊ0�����л����ڡ�
//ʵ��ʱ����ջ���������Ϊ0�ĵ㣬���α���ջ�еĵ㣬����
//�������Ϊ0�ĵ�ѹջ�����ջΪ�գ�����δ��ȫ�����֤��
//�л�·���ڡ�

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


int main()
{
	//����ͼ�ڽӾ���
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