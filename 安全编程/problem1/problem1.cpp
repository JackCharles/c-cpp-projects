#include <iostream>
#include <windows.h>

using namespace std;

double e = 0;
double pi = 0;

double func1(int n)
{
    if(n == 0 || n == 1)
    { return 1; }
    int res = 1;
    for(int i = 1; i <= n; i++)
    { res *= i; }
    return 1.0 / res;
}

DWORD WINAPI calc_e(LPVOID arg)
{
    int i = 0;
    double x = func1(i);
    while(x > 0.000001)
    {
        i++;
        e += x;
        x = func1(i);
    }
}

DWORD WINAPI calc_pi(LPVOID arg)
{
    double t = 0;
    int flag = 1, i = 1;
    double x = 1.0 / i;
    while(x > 0.000001)
    {
        i += 2;
        t += x * flag;
        flag = -flag;
        x = 1.0 / i;
    }
    pi = 4.0 * t;
}

int main()
{
    HANDLE he = CreateThread(NULL, 0, calc_e, NULL, 0, NULL);
    HANDLE hpi = CreateThread(NULL, 0, calc_pi, NULL, 0, NULL);

    if(he == NULL || hpi == NULL)
    {
        cout << "Create thread failed." << endl;
        return 1;
    }

    WaitForSingleObject(he, INFINITE);
    WaitForSingleObject(hpi, INFINITE);
    CloseHandle(he);
    CloseHandle(hpi);

    double result = e * pi;
    cout << "e * pi = " << result << endl;

    return 0;
}
