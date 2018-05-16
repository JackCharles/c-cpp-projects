#include <iostream>
#define N 5
using namespace std;
int Queen[N];               //Queen[i]��ֵ��ʾ��i�лʺ����ڵ���

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


void QueenPlace(int hang)//�˴��Ĳ�����Ҫ�÷��õڼ��еĻʺ�(ÿ�����ҽ���һ��)��Ȼ���ڶ���һ�е�ÿһ��ȥ�ж��ܲ��ܷ�
{
    for(int lie = 0; lie < N; lie++)//����ÿһ�е�������(��ǰ���ܷ��ã��ҳ����н���������ٿ���һ��,������N^N)
    {
        if(CanPlace(hang, lie))
        {
            Queen[hang] = lie;
            if(hang == N - 1)//�����б������ˣ���һ���������
            {
                cout << "���÷���: ";
                for(int i = 0; i < N; ++i)
                    cout << Queen[i] << " ";
                cout<<endl;
            }
            else//��ǰ�з����ˣ���û�з�����������һ��
            {
                QueenPlace(hang + 1);
            }
        }/*--if--*/
    }/*--for--*/
}



int main()
{
    QueenPlace(0);//���ڸú����ǵݹ麯��,�����Զ�����,����ֻ�������ʼ��������0��
    return 0;
}
