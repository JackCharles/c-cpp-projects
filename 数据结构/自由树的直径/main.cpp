#include <iostream>
#define max 10000
using namespace std;


class FreeTree
{
public:
    FreeTree(int n);
    ~FreeTree();
    void Create();
    void GetAllLength();
    int GetDiameter();

    void Test();

private:
    int size;
    int **edge;///邻接矩阵
    int **A;   ///两点之间最短路径
    int **path;///相应路径j的前一个顶点序号
};



FreeTree::FreeTree(int n)
{
    size=n;
    edge=new int*[size];
    A=new int*[size];
    path=new int*[size];
    for(int i=0; i<size; i++)
    {
        edge[i]=new int[size];
        A[i]=new int[size];
        path[i]=new int[size];
    }
}

FreeTree::~FreeTree()
{
    for(int i=0;i<size;i++)
    {
        delete[] path[i];
        delete[] A[i];
        delete[] edge[i];
    }
    delete [] path;
    delete [] A;
    delete [] edge;
}

void FreeTree::Create()
{
    int temp;
    for(int i=0; i<size; i++)
    {
        edge[i][i]=0;
        for(int j=i+1; j<size; j++)
        {
            cin>>temp;
            if(temp==-1)
                edge[i][j]=edge[j][i]=max;
            else
                edge[i][j]=edge[j][i]=temp;
        }
    }
}


void FreeTree::Test()
{
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
            cout<<edge[i][j]<<" ";
        cout<<endl;
    }
        for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
            cout<<A[i][j]<<" ";
        cout<<endl;
    }
}

void FreeTree::GetAllLength()
{
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
        {
            A[i][j]=edge[i][j];
            if(i!=j&&A[i][j]<max)
                path[i][j]=i;
            else
                path[i][j]=-1;
        }

    for(int k=0; k<size; k++)
    {
        for(int i=0; i<size; i++)
        {
            if(i!=k)
                for(int j=0; j<size; j++)
                    if(j!=k&&j!=i&&A[i][k]<max&&A[k][j]<max&&(A[i][k]+A[k][j]<A[i][j]))
                    {
                        A[i][j]=A[i][k]+A[k][j];
                        path[i][j]=path[k][j];
                    }
        }
    }

}


int FreeTree::GetDiameter()
{
    int n=A[0][0];
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(A[i][j]>n)
            n=A[i][j];
    return n;
}

int main()
{
    FreeTree G(4);
    cout<<"请输入邻接矩阵(正无穷用-1代替):"<<endl;
    G.Create();
    G.GetAllLength();
    cout<<"自由树直径是:"<<G.GetDiameter()<<endl;
    return 0;
}
