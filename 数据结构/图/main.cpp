#include <iostream>
#include <stack>
#include <queue>
using namespace std;

typedef struct EdgeNode//边结点
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

typedef struct VertexNode//顶点表结点
{
    int VerName;
    pSEN next;
} SVN, *pSVN;


class Graph
{
public:
    Graph(int v_num, int g_type);                //顶点个数，图的类型1有向图,0无向图
    void CreateGraph();
    int GetCost(int vf, int vt);                //起点,终点,返回权值
    bool InsertEdge(int vf, int vt, int w);     //起点,终点,权值
    bool DeleteEdge(int vf, int vt);
    int GetFirstNeighbor(int v);

    void DeepFirstSearch();
    void BreadthFirstSearch();

    void OutPutTest();                           //测试用
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
    }//初始化顶点表
}

void Graph::CreateGraph()
{
    cout << "输入每条边起点、终点、权值(顶点从0开始,3个0结束):" << endl;
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

        if(type == 0)//如果是无向图才做这一步
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
        }/*无向图*/
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
    return -2;//如果边不存在返回-2,权值正无穷
}

bool Graph::InsertEdge(int vf, int vt, int w)
{

    if(vf > graphsize-1 || vf < 0 || vt > graphsize-1 || vt < 0)
        return false;//插入超范围
    if(GetCost(vf, vt) != -2)
        return false;//待插入边已存在

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
        return false;//删除超范围
    if(GetCost(vf, vt) == -1)
        return false;//待删除边不存在

    pSEN p = head[vf].next;
    pSEN q = p->next; //p->q
    if(p->VerAdj == vt)//如果第一个边结点就是
    {
        head[vf].next = p->next;
        delete p;
    }
    else                //遍历后续结点查找删除
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

    cout<<"请输入图的顶点个数和图的类型(1.有向图,0.无向图):";
    cin>>w>>v;
    Graph *g = new Graph(w, v);//顶点数，类型
    g->CreateGraph();
    cout<<"图创建完成,现在整个图是:"<<endl;
    g->OutPutTest();
    cout<<endl<<endl;





    cout<<"请输入要查找权值的边:";
    cin>>vf>>vt;
    w=g->GetCost(vf,vt);
    if(w==-1)
        cout<<"查找失败,输入的顶点超范围!"<<endl;
    else if(w==-2)
        cout<<"边<"<<vf<<","<<vt<<">的权值是∞!"<<endl;
    else
        cout<<"边<"<<vf<<","<<vt<<">的权值是:"<<w<<endl;
    cout<<endl<<endl;





    cout<<"请输入待插入的边和权值:";
    cin>>vf>>vt>>w;
    if(g->InsertEdge(vf, vt, w))
    {
        cout<<"插入成功,现在整个图是:"<<endl;
        g->OutPutTest();
    }
    else
        cout<<"插入失败,输入的顶点超范围或者这条边已存在!"<<endl;
    cout<<endl<<endl;


    cout<<"请输入待删除的边:";
    cin>>vf>>vt;
    if(g->DeleteEdge(vf, vt))
    {
        cout<<"删除成功,现在整个图是:"<<endl;
        g->OutPutTest();
    }
    else
        cout<<"删除失败,输入的顶点超范围或者这条边不存在!"<<endl;
    cout<<endl<<endl;


    cout<<"请输入待查找第一个邻接顶点的点:";
    cin>>vf;
    v=g->GetFirstNeighbor(vf);
    if(v==-1)
    {
        cout<<"输入的顶点超范围或者其邻接顶点不存在!"<<endl;
    }
    else
    {
        cout<<"顶点"<<vf<<"的邻接顶点是:"<<v<<endl;
    }
    cout<<endl<<endl;

    cout<<"深度优先遍历是:";
    g->DeepFirstSearch();
    cout<<endl;

    cout<<"广度优先遍历是:";
    g->BreadthFirstSearch();
    cout<<endl;


    return 0;
}
