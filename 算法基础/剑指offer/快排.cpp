#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

//快排划分
int Partation(int* numbers, int start, int end)
{
    if(numbers==NULL||start>=end)
        return start;

	int mid = (start+end)/2;
	if(numbers[start]>numbers[mid])
		swap(numbers+start, numbers+mid);
	if(numbers[start]>numbers[end])
		swap(numbers+start, numbers+end);
	if(numbers[mid]>numbers[end])
		swap(numbers+mid, numbers+end);
	swap(numbers+start, numbers+mid);
	int x = numbers[start];
	
	int i = start, j = end+1;
	while(i<j)
	{
		++i;
		while(numbers[i]<=x && i<=end)
			++i;
		--j;
		while(numbers[j]>=x && j>start)
			--j;
		if(i<j)
			swap(numbers+i, numbers+j);
	}
	swap(numbers+start, numbers+j);
	return j;
}


//快排
void QuikSort(int *numbers, int start, int end)
{
    if(numbers!=NULL && start<end)
    {
        int index = Partation(numbers, start, end);
        if(index>start)
            QuikSort(numbers, start, index-1);
        if(index<end)
            QuikSort(numbers, index+1, end);
    }
}

//查找出现超过一半的数字O(NlogN)
int MoreThanHalfNum(int *numbers, int length)
{
    if(numbers==NULL || length<=0)
        return 0;
    int middle = length >> 1;
    int end = length-1;
    int start = 0;
    int index = Partation(numbers, start, end);
    while(index!=middle)
    {
        if(index>middle)
        {
            end = index-1;
            index = Partation(numbers, start, end);
        }
        else
        {
            start = index+1;
            index = Partation(numbers, start, end);
        }
		cout<<index<<endl;
    }

    int result = numbers[middle];

    int times = 0;
    for(int i=0; i<length; i++)
        if(numbers[i]==result)
            times++;
    if(times*2<=length)
        result = 0;

    return result;
}

int main()
{
    int test[] = {2,1,4,2,1,1,1,2,3,1,1};
    int res = MoreThanHalfNum(test, 11);
	cout<<"The more than half number is: "<<res<<endl;
	QuikSort(test, 0, 10);
	for(int i=0; i<11; i++)
		cout<<test[i]<<" ";
    return 0;
}
