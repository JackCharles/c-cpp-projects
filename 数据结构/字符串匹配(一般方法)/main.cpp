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
            cout << "Ŀ��λ��: " << i-mLen+1 << "  "<<i<<endl;
            flag=1;
        }
        i = i - j+1;
    }
    return flag;//�Ƿ���ҳɹ�
}


int main(int argv, char* argc[])
{
    string Tstr,Mstr;
    cin>>Tstr>>Mstr;

    if(!NormalMatch(Tstr,Mstr))
    {
        cout<<"����ʧ��,Ŀ�괮��û�д����ҵ��ַ���!"<<endl;
    }

    return 0;
}
