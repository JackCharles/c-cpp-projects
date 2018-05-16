#include <iostream>
#include<string>
using namespace std;

int NormalMatch(string &Tstr, string &Mstr)
{
    int tLen=Tstr.length();
    int mLen=Mstr.length();
    int i=0,flag=0;
    while(i <=tLen-mLen)
    {
        int j = 0;
        while(Tstr[i] == Mstr[j] && j < mLen)
        {
            i++;
            j++;
        }
        if(j == mLen)
        {
            cout << "目标位置: " << i-mLen+1 << "  "<<i<<endl;
            flag=1;
        }
        i = i - j+1;
    }
    return flag;//是否查找成功
}


int main(int argv, char* argc[])
{
    string Tstr,Mstr;
    cin>>Tstr>>Mstr;

    if(!NormalMatch(Tstr,Mstr))
    {
        cout<<"查找失败,目标串中没有待查找的字符串!"<<endl;
    }

    return 0;
}
