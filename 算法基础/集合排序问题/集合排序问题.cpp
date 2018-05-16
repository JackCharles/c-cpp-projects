#include <iostream>
using namespace std;

int main()
{
    int m,n;
    cin>>m;
    int *s1 = new int[m];
    for(int i=0;i<m;i++)
        cin>>s1[i];

    cin>>n;
    int *s2 = new int[n];
    for(int i=0;i<n;i++)
        cin>>s2[i];

    int *pos = new int[n];//初始为0号位置
    for(int i=0;i<n;i++)
        pos[i] = 0;

    int *posnum = new int[n];
    for(int i=0;i<n;i++)
        posnum[i]=m+1-pos[0];


    int flag = 1;
    int i;
    while(flag)
    {
        for(i=0;i<n;i++)
            cout<<pos[i]<<" ";
        cout<<endl;

        for(i=n-1;i>-1;i--)
        {
            if(posnum[i]-1==0)
            {
                for(int j=i;j<n;j++)
                {
                    pos[j]=pos[i-1]+1;
                    posnum[j]=m+1-pos[j];
                }
                continue;
            }
            else
            {
                posnum[i]--;
                pos[i]++;
                break;
            }
        }
        if(i==-1)
            flag = 0;
    }

    cout<<"stop";
    delete[] pos;
    delete[] posnum;
    delete[] s1;
    delete[] s2;
}
