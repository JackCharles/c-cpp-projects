#include <iostream>
#include <string>

using namespace std;

string strTar, strMod; //Ŀ���ַ�����ģʽ�ַ���

void Next(const string&sM, int next[])
{
    int i = 0;
    int k = -1;
    next[0] = -1;

    while(i < (int)sM.length())
    {
        if(k == -1 || sM[k] == sM[i])//�����һ��ǰ�����,��һ��nextֵ����󳤶ȣ���1
        {
            i++;
            k++;
            next[i] = k;
        }
        else        //����һ��nextֵ(ǰ����ȴ�����󳤶�)��ʼ���
        {
            k = next[k];
        }
    }
}

int main()
{
    cout << "������Ŀ���ַ�����ģʽ�ַ���:" << endl;
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
        }               //���ƥ��ɹ���������ƥ��
        else if(j == 0) //�����һ�ξ�ƥ��ʧ����Ŀ�괮ָ������ƣ��˴����ɽ��ж���������i(Tar)==0,��Ϊ������ǵ�һ��
        {
            //ƥ��(i������λ��)��i����0����jһ����0
            i++;
        }
        else            //ƥ�䵽�м�ĳ��ʧ��,����next����ģʽ����ǰ�ƶ�next[ģʽ��ʧ��λ��-1]����һ��λ��(����ǰ���ظ����Ӵ�)
        {
            j = next[j - 1] + 1;
        }

        if(j == (int)strMod.length()) //���ʱĿ�괮��1��ʼ����ֱ����ģʽ�����ȱȽ�
        {
            cout << "�ڵ�" << i - (int)strMod.length() + 1 << "���ַ���ƥ��ɹ�!" << endl; //���ƥ��ɹ����ַ�����ʼλ��
            j = 0;
            flag = 1;
        }
    }
    if(flag == 0)
        cout << "ƥ��ʧ��!" << endl;

    return 0;
}
