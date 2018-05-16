#include <iostream>
#define N 5
using namespace std;
int Queen[N];               //Queen[i]的值表示第i行皇后所在的列

bool CanPlace(int nowHang, int nowLie)
{
    int preHang = 0;
    while(preHang < nowHang)
    {
        if(Queen[preHang] == nowLie || Queen[preHang] - nowLie == preHang - nowHang || Queen[preHang] - nowLie == nowHang - preHang)
            return false;
        preHang++;
    }
    return true;
}


void QueenPlace(int hang)//此处的参数是要该放置第几行的皇后(每行有且仅有一个)，然后在对这一行的每一列去判断能不能放
{
    for(int lie = 0; lie < N; lie++)//遍历每一行的所有列(当前列能放置，找出所有解决方案后再看下一列,最多遍历N^N)
    {
        if(CanPlace(hang, lie))
        {
            Queen[hang] = lie;
            if(hang == N - 1)//所有行遍历完了，有一个解决方案
            {
                cout << "可用方案: ";
                for(int i = 0; i < N; ++i)
                    cout << Queen[i] << " ";
                cout<<endl;
            }
            else//当前行放完了，并没有放满，进行下一行
            {
                QueenPlace(hang + 1);
            }
        }/*--if--*/
    }/*--for--*/
}



int main()
{
    QueenPlace(0);//由于该函数是递归函数,行数自动增加,这里只需给出初始行数即第0行
    return 0;
}
