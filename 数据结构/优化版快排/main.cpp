#include <iostream>
#define N 10000000
using namespace std;


void QSort(int R[], int m, int n)
{
    if(m < n)
    {
        int temp = R[m + 1];
        R[m + 1] = R[(n + m) / 2];
        R[(n + m) / 2] = temp;

        if(R[m + 1] > R[n])
        {
            temp = R[n];
            R[n] = R[m + 1];
            R[m + 1] = temp;
        }
        if(R[m] > R[n])
        {
            temp = R[n];
            R[n] = R[m];
            R[m] = temp;
        }
        if(R[m + 1] > R[m])
        {
            temp = R[m + 1];
            R[m + 1] = R[m];
            R[m] = temp;
        }
        /**************以上部分是为了找一个较好的基准，保证文件划分具有随机性***********/

        int i = m, j = n + 1;
        while(i < j)
        {
            i += 1;
            while(R[i] < R[m])
                i++;
            j -= 1;
            while(R[j] > R[m])
                j--;
            if(i < j)
            {
                temp = R[i];
                R[i] = R[j];
                R[j] = temp;
            }

        }
        temp = R[m];
        R[m] = R[j];
        R[j] = temp;

        QSort(R, m, j - 1);
        QSort(R, j + 1, n);
    }
}





int BSearch(int n, int k, int a[]) //折半查找
{
    int s = 0, e = n - 1;
    int i = (s + e) / 2;

    while(a[i] != k && s < e)
    {
        if(a[i] > k)
        {
            e = i - 1;
        }
        else
        {
            s = i + 1;
        }
        i = (s + e) / 2;
    }
    if(s <= e)
        return i;
    else
        return -1;
}




int main()
{
    int *num = new int[N];
    for(int i=0;i<N;i++)
    {
        num[i]=N-i;
    }


    QSort(num, 0, N - 1);

    cout<<num[0]<<"  "<<num[N-1];

    /*int *R, n;
    cout << "输入待排序元素个数:";
    cin >> n;
    R = new int[n];
    for(int i = 0; i < n; i++)
        cin >> R[i];

    QSort(R, 0, n - 1);

    for(int i = 0; i < n; i++)
        cout << R[i] << " ";

    cout << endl << "请输入待查找数据:";
    int k;
    cin >> k;
    int s = BSearch(n, k, R);
    if(s != -1)
    {
        cout << "查找成功,已找到数据" << R[s] << ",其下标是:" << s << endl;
    }
    else
    {
        cout << "查找失败,不存在数据" << k << endl;
    }
    */
    return 0;
}
