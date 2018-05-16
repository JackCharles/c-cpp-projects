#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct EdgeNode
{
    int weight;
    int NodeName;
    EdgeNode* next;
};

struct HeadNode
{
    int HeadName;
    EdgeNode* next;
};

void CreateGraph(HeadNode head[], int n)
{
    EdgeNode** rear = new EdgeNode*[n];
    for(int i=0; i<n; i++)
    {
        head[i].HeadName = i; //start with num 0;
        head[i].next = NULL;
        rear[i] = NULL;
    }
    cout<<"Input edge([from] [to] [weight], and 0 0 0 is stop flag):"<<endl;
    int f,t,w;
    cin>>f>>t>>w;
    while(f!=0||t!=0)
    {
        EdgeNode *p = new EdgeNode;
        p->next = NULL;
        p->NodeName = t;
        p->weight = w;
        if(rear[f]==NULL)
        {
            head[f].next = p;
            rear[f] = p;
        }
        else
        {
            rear[f]->next = p;
            rear[f] = p;
        }
        cin>>f>>t>>w;
    }
}


void TestOutput(HeadNode head[], int n)
{
    EdgeNode* p = NULL;
    for(int i=0; i<n; i++)
    {
        cout<<"["<<head[i].HeadName<<"] -> ";
        p=head[i].next;
        while(p!=NULL)
        {
            cout<<"["<<p->NodeName<<"] -> ";
            p=p->next;
        }

        cout<<"NULL"<<endl;
    }
}


void DeepFirstSearch(HeadNode head[], int n)
{
    stack<int> s;
    int *visited = new int[n];
    for(int i=0; i<n; i++)
    {
        visited[i]=0;
    }

    s.push(head[0].HeadName);
    visited[0]=1;
    while(!s.empty())
    {
        int j = s.top();
        s.pop();
        cout<<j;//j has been visited
        EdgeNode *p = head[j].next;
        while(p!=NULL)
        {
            if(visited[p->NodeName]==0)
            {
                s.push(p->NodeName);
                visited[p->NodeName]=1;
            }
            p=p->next;
        }
    }
    cout<<endl;
    delete[] visited;
}

void DeepFirstSearch2(HeadNode head[], int node, int visited[])
{
    cout<<node;
    visited[node] = 1;
    EdgeNode *p = head[node].next;
    while(p!=NULL)
    {
        if(visited[p->NodeName]==0)
            DeepFirstSearch2(head,p->NodeName,visited);
        p=p->next;
    }
}

void BrandFirstSearch(HeadNode head[],int n)
{
    queue<int> q;
    int visited[50]= {0};
    q.push(head[0].HeadName);
    visited[0]=1;
    while(!q.empty())
    {
        int j = q.front();
        q.pop();
        cout<<j;
        EdgeNode*p = head[j].next;
        while(p!=NULL)
        {
            if(visited[p->NodeName]==0)
            {
                q.push(p->NodeName);
                visited[p->NodeName]=1;
            }
            p=p->next;
        }
    }

    cout<<endl;
}

void TopoOrder(HeadNode head[],int n)
{
    int ncount[50] = {0};//��¼���е�����
    for(int i=0; i<n; i++)//��ȡÿ��������
    {
        EdgeNode *p = head[i].next;
        while(p!=NULL)
        {
            ++ncount[p->NodeName];
            p=p->next;
        }
    }
    int top = -1;//ջ��ָ��
    for(int i=0; i<n; i++)//��ʼ��ջ�����������Ϊ0�Ľڵ���ջ
    {
        if(ncount[i]==0)
        {
            ncount[i] = top;
            top = i;
        }
    }
    int tcount = 0;
    while(top!=-1)//whileջ�ǿ�
    {
        int j = top;//��ջ
        top = ncount[top];
        cout<<j;
        ++tcount;

        EdgeNode *p = head[j].next;
        while(p!=NULL)//��������ָ��Ľڵ㣬��������ȼ�һ���൱��ɾ���ߣ���������Ϊ0����ѹջ��
        {
            --ncount[p->NodeName];
            if(ncount[p->NodeName]==0)
            {
                ncount[p->NodeName]=top;
                top = p->NodeName;
            }
            p=p->next;
        }
    }

    if(tcount!=n)
        cout<<"There is a cycle in network!";
    cout<<endl;

}

int main()
{
    cout<<"Input vertex number: ";
    int n;
    cin>>n;
    HeadNode* head = new HeadNode[n];
    CreateGraph(head, n);
    TestOutput(head, n);
    DeepFirstSearch(head,n);
    int visited[50]= {0};
    DeepFirstSearch2(head,0,visited);
    cout<<endl;
    BrandFirstSearch(head,n);
    TopoOrder(head,n);
}
