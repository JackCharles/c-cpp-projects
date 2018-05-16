#include <iostream>
#include <vector>

using namespace std;

int MoreThanHalfNum_Solution(vector<int> numbers)
{
    int len = numbers.size();
    if(len == 0)
        return 0;

    int res = numbers[0];
    int times = 1;
    for(int i=0; i<len; ++i)
    {
        if(times==0)
        {
            res = numbers[i];
            times=1;
        }
        else if(numbers[i]==res)
            times++;
        else
            times--;
    }

    times = 0;
    for(int i=0; i<len; ++i)
        if(res==numbers[i])
            times++;
    if(times*2<=len)
        res = 0;
    return res;
}



int main()
{
    return 0;
}
