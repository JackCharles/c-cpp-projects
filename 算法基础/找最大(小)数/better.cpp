#include <iostream>
#include <time.h>
#include <stack>
#define N 100000000
using namespace std;

int main(int argc, char* argv[])
{
    int *num=new int[N];
    for(int i=0;i<N;i++)
    {
        num[i]=i;
    }
    clock_t t1 = clock();
    int maxn = num[0];//maxn.minx的值具有方向性，必须保证其值的改变是有效的
    int minn = num[0];
    stack<int> s;
    s.push(0);
    s.push(N-1);
    while(!s.empty())
    {
        int j = s.top();//big
        s.pop();
        int i = s.top();//small
        s.pop();
        int tmax, tmin, flag = 0; //flag用于标志这一轮是否需要更新maxn,minx
        if(i == j)                //如果tmax,tmin没有有效赋值，则更新maxn就会无效
        {
            tmax = tmin = num[i];
            flag = 1;
        }
        else if(i == (j - 1))
        {
            if(num[i] < num[j])
            {
                tmin = num[i];
                tmax = num[j];
            }
            else
            {
                tmin = num[j];
                tmax = num[i];
            }
            flag = 1;
        }
        else
        {
            int mid = (i + j) / 2;
            s.push(i);
            s.push(mid);
            s.push(mid + 1);
            s.push(j);
        }

        if(flag)
        {
            if(tmax > maxn)
                maxn = tmax;
            if(tmin < minn)
                minn = tmin;
        }
    }
    clock_t t2 = clock();
    cout << "max: " << maxn << endl;
    cout << "min: " << minn << endl;
    cout << "use time:"<<(t2-t1)/1000.0<<endl;

}
