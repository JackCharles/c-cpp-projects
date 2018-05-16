#include <iostream>
#include <ctime>
#include <queue>
using namespace std;

//(1)插入排序：时间O(n^2), 空间O(1),稳定排序
template<typename T>
void InsertSort(T* array, int num, int(*fun)(const T* a, const T* b))
{
	if (num < 1)
		return;

	T temp;
	int j;

	//将array[i]插入到前i个有序记录中
	for (int i = 1; i < num; ++i)
	{
		temp = array[i];
		j = i - 1;
		while (j > -1 && fun(&array[j], &temp) > 0)
		{
			array[j + 1] = array[j];
			--j;
		}
		array[j + 1] = temp;
	}
}

//(2)shell排序(插入排序变种):时间O(n^2), 空间O(1),不稳定排序
template<typename T>
void ShellSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	if (num < 1)
		return;

	for (int dk = num / 2; dk > 0; dk >>= 1)//直到分量为1
		//对在同组间隔为dk的元素排序
		for (int i = dk; i < num; ++i)//多组同时推进
		{
			//和他前一个间隔为dk元素比较,因为他前面是已经排好序的，
			//如果他和前一个位置正好，那么他在整个序列的位置正确，无需再变
			if (fun(&array[i], &array[i - dk]) < 0)
			{
				T t = array[i];
				int j = i - dk;//以分组为增量
				while (fun(&t, &array[j]) < 0 && j >= 0)
				{
					array[j + dk] = array[j];
					j -= dk;
				}

				array[j + dk] = t;
			}
		}
}

//(3)冒泡排序: 时间O(n^2), 空间O(1), 稳定排序
template<typename T>
void BubbleSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	if (num < 1)
		return;
	bool flag = true;
	int k = 1;
	while (flag)
	{
		flag = false;
		for (int i = 0; i < num - k; ++i)
			if (fun(&array[i], &array[i + 1]) > 0)
			{
				T t = array[i];
				array[i] = array[i + 1];
				array[i + 1] = t;
				flag = true;
			}
		++k;
	}
}

//(4)快速排序：时间O(nlogn), 空间O(logn), 不稳定排序
template<typename T>
void QuickSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	if (num <= 1)
		return;

	srand((unsigned)time(NULL));
	int x = rand() % num;
	T t = array[x];
	array[x] = array[0];
	array[0] = t;
	x = 0;

	int i = 0, j = num;//i从1开始，j从num-1开始
	while (i < j)
	{
		++i;//找比选定划分大的数
		while (i < num && fun(&array[i], &array[x]) < 0)
			++i;
		--j;//找比划分小的数
		while (j > 0 && fun(&array[j], &array[x]) > 0)
			--j;

		if (i < j)//找到这样的两个数就交换
		{
			t = array[i];
			array[i] = array[j];
			array[j] = t;
		}
	}
	//将划分放到中间
	t = array[j];
	array[j] = array[x];
	array[x] = t;

	if (j > 0)//左边还有
		QuickSort(array, j, fun);
	if (j < num - 1)//右边还有
		QuickSort(&array[j + 1], num - (j + 1), fun);

}

//(5)选择排序：时间O(n^2), 空间O(1), 不稳定排序
template<typename T>
void SelectSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	if (num < 1)
		return;
	for (int i = num - 1; i > 0; --i)
	{
		int key = 0;
		for (int j = 1; j < i; ++j)//在前i个中找第i大/小的元素，然后和i交换
			if (fun(&array[j], &array[key]) > 0)
				key = j;
		T t = array[key];
		array[key] = array[i];
		array[i] = t;
	}
}

//(6)堆排序：时间O(nlogn), 空间O(1), 不稳定排序
//重建堆
template<typename T>
void Restore(T *tree, int root, int n, int(*fun)(const T*a, const T*b))
{
	//tree就是传入的数组，root 为待重建的堆的根，n是元素个数
	int m, j = root;
	//从根一直到最后一个非叶结点,最后一个叶节点为n，其父节点为n/2取地板
	while (j <= (n / 2))
	{
		//如果所遍历结点有左右子结点(2*j<n保证)，找到其中较大的那个子结点编号
		if (2 * j < n && fun(&tree[2 * j], &tree[2 * j + 1]) < 0)
			m = 2 * j + 1;//右孩子较大
		else//左孩子较大，或者只有左孩子(while条件保证j一定有左孩子)
			m = 2 * j;
		//判断root需不需要交换
		if (fun(&tree[j], &tree[m]) < 0)
		{
			T t = tree[j];
			tree[j] = tree[m];
			tree[m] = t;
			j = m;//如果交换了只会影响根为m的这个子树，因此只需要更新m子树即可
		}
		//当前堆已经排好序，直接结束重建
		else j = n;
	}
}
//堆排序
template<typename T>
void HeapSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	//由于要利用2*i和2*i+1访问叶子结点，故i不能为0
	int *copy = new int[num + 1];
	for (int i = 1; i <= num; ++i)
		copy[i] = array[i - 1];

	//初始建堆，自下而上建堆，当建立以i为根的堆时
	//以2i,2i+1为根的堆都以建立完毕，i从最后一个非叶结点开始
	for (int i = num / 2; i >= 1; i--)
		Restore(copy, i, num, fun);

	for (int i = num; i > 1; i--)
	{
		//将堆顶元素换到堆尾，并重建不包含num-i+1个堆尾元素的堆
		//相当于每次将最大(小)值换到第i个位置上，并重建i以前的堆
		T t = copy[1];
		copy[1] = copy[i];
		copy[i] = t;
		//root = 1，i-1个元素
		Restore(copy, 1, i - 1, fun);
	}

	for (int i = 1; i <= num; ++i)
		array[i - 1] = copy[i];
	delete[] copy;
}

//(7)归并排序：时间O(nlogn), 空间O(n),稳定排序
//合并两个子序列low-mid, mid+1~high
template<typename T>
void Merge(T* array, int low, int mid, int high, int(*fun)(const T*a, const T*b))
{
	int *temp = new int[high - low + 1];
	int i = low, j = mid + 1, index = 0;
	while (i <= mid && j <= high)
	{
		if (func(&array[i], &array[j]) < 0)
			temp[index++] = array[i++];
		else
			temp[index++] = array[j++];
	}
	if (i > mid)//后半部分可能没合并完
		for (; j <= high; ++j)
			temp[index++] = array[j];
	else//前半部分可能没合并完
		for (; i <= mid; ++i)
			temp[index++] = array[i];
	//合并结果写入原数组
	for (index = low; index <= high; ++index)
		array[index] = temp[index - low];
	delete[] temp;
}
//合并
template<typename T>
void MergeSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	if (num > 1)
	{
		int mid = num / 2;
		MergeSort(array, mid, fun);//左半部分排序
		MergeSort(&array[mid], num - mid, fun);//右半部分排序
		Merge(array, 0, mid - 1, num - 1, fun);//合并排好序的两部分
	}
	int test = 6;
}

//(8)基数排序(桶排序)：时间O(np),空间O(基数m)
int GetBit(int n, int k)
{
	int res = 0;
	for (int i = 0; i < k; ++i)
	{
		res = n % 10;
		n /= 10;
	}
	return res;
}
void RadixSort(int* array, int num, int p)
{
	if (num < 1)
		return;

	queue<int> q[10];//此处只实现对正整数排序，基数=10
	queue<int> temp;
	for (int i = 0; i < num; ++i)
		temp.push(array[i]);
	int t, s = 1;
	while (s <= p)
	{
		//分桶
		for (int i = 0; i < num; ++i)
		{
			t = temp.front();
			temp.pop();
			q[GetBit(t, s)].push(t);
		}

		//合桶
		for (int i = 0; i < 10; ++i)
			while (!q[i].empty())
			{
				temp.push(q[i].front());
				q[i].pop();
			}
		++s;
	}

	t = 0;
	while (!temp.empty())
	{
		array[t++] = temp.front();
		temp.pop();
	}
}
//值分布，就类似哈希表方式


int func(const int *a, const int *b)
{
	return (*a - *b);
}

int main()
{
	int n = 10;
	int a[] = { 3,91,5,2,884,129,745,448,96,10 };
	RadixSort(a, n, 3);
	for (int i = 0; i < n; ++i)


		cout << a[i] << " ";
}