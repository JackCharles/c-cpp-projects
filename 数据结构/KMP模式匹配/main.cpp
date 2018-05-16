#include <iostream>
#include <string>

using namespace std;

string strTar, strMod; //目标字符串，模式字符串

void Next(const string&sM, int next[])
{
    int i = 0;
    int k = -1;
    next[0] = -1;

    while(i < (int)sM.length())
    {
        if(k == -1 || sM[k] == sM[i])//如果下一个前后都相等,下一个next值（最大长度）加1
        {
            i++;
            k++;
            next[i] = k;
        }
        else        //从上一个next值(前后相等串的最大长度)开始检查
        {
            k = next[k];
        }
    }
}

int main()
{
    cout << "请输入目标字符串和模式字符串:" << endl;
    cin >> strTar;
    cin >> strMod;
    int next[strMod.length()];
    Next(strMod, next);

    int i = 0, j = 0, flag = 0; //i Tar,j Mod,flag Success or fail
    while(i < (int)strTar.length() && j < (int)strMod.length())
    {
        if(strTar[i] == strMod[j])
        {
            i++;
            j++;
        }               //如果匹配成功则继续向后匹配
        else if(j == 0) //如果第一次就匹配失败则，目标串指针向后移，此处不可将判断条件换成i(Tar)==0,因为如果不是第一次
        {
            //匹配(i不在首位置)则i不是0，但j一定是0
            i++;
        }
        else            //匹配到中间某处失败,根据next函数模式串向前移动next[模式串失败位置-1]的下一个位置(跳过前后重复的子串)
        {
            j = next[j - 1] + 1;
        }

        if(j == (int)strMod.length()) //输出时目标串从1开始计数直接与模式串长度比较
        {
            cout << "在第" << i - (int)strMod.length() + 1 << "个字符处匹配成功!" << endl; //输出匹配成功的字符串起始位置
            j = 0;
            flag = 1;
        }
    }
    if(flag == 0)
        cout << "匹配失败!" << endl;

    return 0;
}
