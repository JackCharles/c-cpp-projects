#include <iostream>
#include <vector>

using namespace std;

int FindGreatestSumOfSubArray(vector<int> array)
{
	int len = array.size();
	if(len == 0)
		return 0;
	int max_sum = 0x80000000;//最小的负数第32位为1,其余为0
	int curr_sum = 0;
	for(int i=0;i<len;++i)
	{
		if(curr_sum<0)//当前和小于0，只会将array[i]拖小，因此直接抛弃前面部分
			curr_sum = array[i];
		else
			curr_sum += array[i];
		if(curr_sum>max_sum)//记录整个过程中出现的最大值
			max_sum = curr_sum;
	}
	
	return max_sum;
}