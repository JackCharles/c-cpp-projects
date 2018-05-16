#include <iostream>
#include <stack>
#include <queue>
using namespace std;

typedef struct EdgeNode//�߽��
{
    int VerAdj;
    int cost;
    EdgeNode*next;
    EdgeNode(int Ver, int w)
    {
        VerAdj = Ver;
        cost = w;
        next = NULL;
    }
    EdgeNode()
    {
        next = NULL;
    }
} SEN, *pSEN; //struct edge node,pointer of struct node

typedef struct VertexNode//�������
{
    int VerName;
    pSEN next;
} SVN, *pSVN;


class Graph
{
public:
    Graph(int v_num, int g_type);                //���������ͼ������1����ͼ,0����ͼ
    void CreateGraph();
    int GetCost(int vf, int vt);                //���,�յ�,����Ȩֵ
    bool InsertEdge(int vf, int vt, int w);     //���,�յ�,Ȩֵ
    bool DeleteEdge(int vf, int vt);
    int GetFirstNeighbor(int v);

    void DeepFirstSearch();
    void BreadthFirstSearch();

    void OutPutTest();                           //������
private:
    int graphsize;
    pSVN head;
    int type;
};

/***************************************************************/

Graph::Graph(int v_num, int g_type)
{
    graphsize = v_num;
    type = g_type;
    head = new SVN[graphsize];
    for(int i = 0; i < graphsize; i++)
    {
        head[i].VerName = i;
        head[i].next = NULL;
    }//��ʼ�������
}

void Graph::CreateGraph()
{
    cout << "����ÿ������㡢�յ㡢Ȩֵ(�����0��ʼ,3��0����):" << endl;
    int vf, vt, w;
    pSEN rear[graphsize];

    cin >> vf >> vt >> w;
    while(vf != 0 || vt!=0)
    {
        if(head[vf].next == NULL)
        {
            head[vf].next = new SEN(vt, w);
            rear[vf] = head[vf].next;
        }
        else
        {
            rear[vf]->next = new SEN(vt, w);
            rear[vf] = rear[vf]->next;
        }

        if(type == 0)//���������ͼ������һ��
        {
            if(head[vt].next == NULL)
            {
                head[vt].next = new SEN(vf, w);
                rear[vt] = head[vt].next;
            }
            else
            {
                rear[vt]->next = new SEN(vf, w);
                rear[vt] = rear[vt]->next;

            }
        }/*����ͼ*/
        cin >> vf >> vt >> w;
    }/*while*/
}

void Graph::OutPutTest()
{
    pSEN p[graphsize];
    for(int i = 0; i < graphsize; i++)
    {
        p[i] = head[i].next;
        cout << head[i].VerName<< ": ";
        while(p[i] != NULL)
        {
            cout << p[i]->VerAdj << "(" << p[i]->cost << ") -> ";
            p[i] = p[i]->next;
        }
        cout << "NULL" << endl;
    }
}

int Graph::GetCost(int vf, int vt)
{
    if(vf>graphsize-1||vt>graphsize-1||vf<0||vt<0)
        return -1;
    pSEN p = head[vf].next;
    while(p != NULL)
    {
        if(p->VerAdj == vt)
            return p->cost;
        p = p->next;
    }
    return -2;//����߲����ڷ���-2,Ȩֵ������
}

bool Graph::InsertEdge(int vf, int vt, int w)
{

    if(vf > graphsize-1 || vf < 0 || vt > graphsize-1 || vt < 0)
        return false;//���볬��Χ
    if(GetCost(vf, vt) != -2)
        return false;//��������Ѵ���

    pSEN p = head[vf].next;
    head[vf].next = new SEN(vt, w);
    head[vf].next->next = p;
    if(type == 0)
    {
        p = head[vt].next;
        head[vt].next = new SEN(vf, w);
        head[vt].next->next = p;
    }
    return true;
}

bool Graph::DeleteEdge(int vf, int vt)
{
    if(vf > graphsize-1 || vf < 0 || vt > graphsize-1 || vt < 0)
        return false;//ɾ������Χ
    if(GetCost(vf, vt) == -1)
        return false;//��ɾ���߲�����

    pSEN p = head[vf].next;
    pSEN q = p->next; //p->q
    if(p->VerAdj == vt)//�����һ���߽�����
    {
        head[vf].next = p->next;
        delete p;
    }
    else                //��������������ɾ��
    {
        while(q != NULL)
        {
            if(q->VerAdj == vt)
            {
                p->next = q->next;
                delete q;
                break;
            }
            p = p->next;
            q = q->next;
        }/*while*/
    }/*if-else*/

    if(type == 0)
    {
        p = head[vt].next;
        q = p->next; //p->q
        if(p->VerAdj == vf)
        {
            head[vt].next = p->next;
            delete p;
        }
        else
        {
            while(q != NULL)
            {
                if(q->VerAdj == vf)
                {
                    p->next = q->next;
                    delete q;
                    break;
                }
                p = p->next;
                q = q->next;
            }/*while*/
        }/*if-else*/
    }/*type==0*/
    return true;
}

int Graph::GetFirstNeighbor(int v)
{
    if(v > graphsize-1 || v < 0)
        return -1;
    else if(head[v].next==NULL)
        return -1;
    return head[v].next->VerAdj;
}

void Graph::DeepFirstSearch()
{
    stack<int> S;
    int visited[graphsize];
    for(int i = 0; i < graphsize; i++)
        visited[i] = 0;

    S.push(0);
    visited[0] = 1;

    while(!S.empty())
    {
        int v = S.top();
        S.pop();
        cout << v << " ";
        pSEN p = head[v].next;
        while(p != NULL)
        {
            if(visited[p->VerAdj] == 0)
            {
                S.push(p->VerAdj);
                visited[p->VerAdj] = 1;
            }
            p = p->next;
        }
    }
}

void Graph::BreadthFirstSearch()
{
    queue<int>Q;
    int visited[graphsize];
    for(int i=0; i<graphsize; i++)
    {
        visited[i]=0;
    }
    Q.push(0);
    visited[0]=1;
    while(!Q.empty())
    {
        int v=Q.front();
        Q.pop();
        cout<<v<<" ";
        pSEN p=head[v].next;
        while(p!=NULL)
        {
            if(visited[p->VerAdj]==0)
            {
                Q.push(p->VerAdj);
                visited[p->VerAdj]=1;
            }
            p=p->next;
        }
    }
}


int main()
{
    int vf,vt,w,v;

    cout<<"������ͼ�Ķ��������ͼ������(1.����ͼ,0.����ͼ):";
    cin>>w>>v;
    Graph *g = new Graph(w, v);//������������
    g->CreateGraph();
    cout<<"ͼ�������,��������ͼ��:"<<endl;
    g->OutPutTest();
    cout<<endl<<endl;





    cout<<"������Ҫ����Ȩֵ�ı�:";
    cin>>vf>>vt;
    w=g->GetCost(vf,vt);
    if(w==-1)
        cout<<"����ʧ��,����Ķ��㳬��Χ!"<<endl;
    else if(w==-2)
        cout<<"��<"<<vf<<","<<vt<<">��Ȩֵ�ǡ�!"<<endl;
    else
        cout<<"��<"<<vf<<","<<vt<<">��Ȩֵ��:"<<w<<endl;
    cout<<endl<<endl;





    cout<<"�����������ıߺ�Ȩֵ:";
    cin>>vf>>vt>>w;
    if(g->InsertEdge(vf, vt, w))
    {
        cout<<"����ɹ�,��������ͼ��:"<<endl;
        g->OutPutTest();
    }
    else
        cout<<"����ʧ��,����Ķ��㳬��Χ�����������Ѵ���!"<<endl;
    cout<<endl<<endl;


    cout<<"�������ɾ���ı�:";
    cin>>vf>>vt;
    if(g->DeleteEdge(vf, vt))
    {
        cout<<"ɾ���ɹ�,��������ͼ��:"<<endl;
        g->OutPutTest();
    }
    else
        cout<<"ɾ��ʧ��,����Ķ��㳬��Χ���������߲�����!"<<endl;
    cout<<endl<<endl;


    cout<<"����������ҵ�һ���ڽӶ���ĵ�:";
    cin>>vf;
    v=g->GetFirstNeighbor(vf);
    if(v==-1)
    {
        cout<<"����Ķ��㳬��Χ�������ڽӶ��㲻����!"<<endl;
    }
    else
    {
        cout<<"����"<<vf<<"���ڽӶ�����:"<<v<<endl;
    }
    cout<<endl<<endl;

    cout<<"������ȱ�����:";
    g->DeepFirstSearch();
    cout<<endl;

    cout<<"������ȱ�����:";
    g->BreadthFirstSearch();
    cout<<endl;


    return 0;
}
