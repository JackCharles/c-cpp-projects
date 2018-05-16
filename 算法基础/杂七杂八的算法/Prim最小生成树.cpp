#include <iostream>
using namespace std;

#define N 6 //������
#define MAX 0x7FFFFFFF //�з���int���ֵ

//�ڽӾ���
int edge[N][N] = {
	{0, 1, 4, 7, 0, 0},
	{1, 0, 4, 0, 0, 2},
	{4, 4, 0, 2, 3, 5},
	{7, 0, 2, 0, 6, 0},
	{0, 0, 3, 6, 0, 3},
	{0, 2, 5, 0, 3, 0}
};

//closedge�ṹ��ÿ������һ��closedge,U�е�closedge��
//ֻ��Vex�ֶ���Ч�����ڱ�ʶ�˵��Ѿ�������ɡ�V��closedge
//��Lowcost��ʾ�õ㵽U�е�һ��[���]·����Vex��¼����·��
//��U�еĶ˵㡣
struct CLE
{
	int Vex;
	int Lowcost;
};

//MST�ṹ��¼ѡ�����ıߣ�����Щ�߹�����С������
struct MST
{
	int head;//�ߵ���ʼ��
	int tail;//�ߵĽ�����
	int cost;//Ȩֵ
};


//����ķ�㷨������С������(֧����)�����������Ϊ��������U��V
//U��ʾ������ĵ㣬V��ʾʣ��δ����ĵ㣬ÿ��ֻ��Ҫ��V����һ��
//������U��Ȩֵ��С�ĵ����U�У�ֱ�����е����U�м��ɡ�
void Prim(int Edge[][N], MST* Result, int NodeNum)
{
	if (NodeNum <= 0)
		return;

	//��ʼ���ڽӾ���,��0ȫ����ΪMAX���������������С·��
	for (int i = 0; i < NodeNum; ++i)
		for (int j = 0; j < NodeNum; ++j)
			if (Edge[i][j] == 0)
				Edge[i][j] = MAX;

	//��ʼ��closedge�ṹ,ÿ������һ��
	CLE *closedge = new CLE[NodeNum];
	for (int i = 0; i < NodeNum; ++i)
	{
		//��ʼѡ��0�ŵ���U�У����ඥ�㵽U�еľ�����ǵ�0��ľ���
		closedge[i].Lowcost = Edge[0][i];
		closedge[i].Vex = 0;//U�ж˵�ȫ��0��
	}
	closedge[0].Vex = -1;//-1����0���Ѿ�����U��
	int count = 1;//U�ж������

	//������С֧����
	for (int i = 1; i < NodeNum; ++i)//��ʣ���NodeNum-1�������U��
	{
		int MinLowCost = MAX;//Ѱ��V��U�����·���ıߣ�������СLowcost
		int v = 0;//��¼V��ѡ�еĵ�,���Ϊ0��Ϊû���ҵ�

		for (int j = 0; j < NodeNum; ++j)//���ֻ�ܴ�0��ʼ��������ΪV��ʣ���û�й���
			if (closedge[j].Vex != -1 && closedge[j].Lowcost < MinLowCost)
			{
				MinLowCost = closedge[j].Lowcost;
				v = j;
			}

		//��ѡ�е�V�еĵ�v����U��
		if (v != 0)
		{
			Result[count - 1].head = closedge[v].Vex + 1;
			Result[count - 1].tail = v + 1;
			Result[count - 1].cost = closedge[v].Lowcost;
			++count;
			closedge[v].Vex = -1;//���õ���Ϊ��U��
		}

		//U�е㷢���仯����Ҫ����V��ʣ��㵽U�е����С����
		//����������仯ֻ�����¼����v����ģ�����ֻ��Ҫ��
		//�õ���v���ɵı߱Ƚϼ��ɡ�
		for (int j = 0; j < NodeNum; ++j)
			if (closedge[j].Vex != -1 && closedge[j].Lowcost > Edge[v][j])
			{
				closedge[j].Lowcost = Edge[v][j];
				closedge[j].Vex = v;
			}
	}
	delete[] closedge;//ǧ�������
}

int main()
{
	MST Result[N - 1];
	Prim(&edge[0], Result, N);
	for (int i = 0; i < N - 1; ++i)
		cout << Result[i].head << "--" << Result[i].cost << "-->" << Result[i].tail << endl;
}