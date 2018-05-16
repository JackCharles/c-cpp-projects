#include <iostream>
#include <ctime>
#include <queue>
using namespace std;

//(1)��������ʱ��O(n^2), �ռ�O(1),�ȶ�����
template<typename T>
void InsertSort(T* array, int num, int(*fun)(const T* a, const T* b))
{
	if (num < 1)
		return;

	T temp;
	int j;

	//��array[i]���뵽ǰi�������¼��
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

//(2)shell����(�����������):ʱ��O(n^2), �ռ�O(1),���ȶ�����
template<typename T>
void ShellSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	if (num < 1)
		return;

	for (int dk = num / 2; dk > 0; dk >>= 1)//ֱ������Ϊ1
		//����ͬ����Ϊdk��Ԫ������
		for (int i = dk; i < num; ++i)//����ͬʱ�ƽ�
		{
			//����ǰһ�����ΪdkԪ�رȽ�,��Ϊ��ǰ�����Ѿ��ź���ģ�
			//�������ǰһ��λ�����ã���ô�����������е�λ����ȷ�������ٱ�
			if (fun(&array[i], &array[i - dk]) < 0)
			{
				T t = array[i];
				int j = i - dk;//�Է���Ϊ����
				while (fun(&t, &array[j]) < 0 && j >= 0)
				{
					array[j + dk] = array[j];
					j -= dk;
				}

				array[j + dk] = t;
			}
		}
}

//(3)ð������: ʱ��O(n^2), �ռ�O(1), �ȶ�����
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

//(4)��������ʱ��O(nlogn), �ռ�O(logn), ���ȶ�����
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

	int i = 0, j = num;//i��1��ʼ��j��num-1��ʼ
	while (i < j)
	{
		++i;//�ұ�ѡ�����ִ����
		while (i < num && fun(&array[i], &array[x]) < 0)
			++i;
		--j;//�ұȻ���С����
		while (j > 0 && fun(&array[j], &array[x]) > 0)
			--j;

		if (i < j)//�ҵ��������������ͽ���
		{
			t = array[i];
			array[i] = array[j];
			array[j] = t;
		}
	}
	//�����ַŵ��м�
	t = array[j];
	array[j] = array[x];
	array[x] = t;

	if (j > 0)//��߻���
		QuickSort(array, j, fun);
	if (j < num - 1)//�ұ߻���
		QuickSort(&array[j + 1], num - (j + 1), fun);

}

//(5)ѡ������ʱ��O(n^2), �ռ�O(1), ���ȶ�����
template<typename T>
void SelectSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	if (num < 1)
		return;
	for (int i = num - 1; i > 0; --i)
	{
		int key = 0;
		for (int j = 1; j < i; ++j)//��ǰi�����ҵ�i��/С��Ԫ�أ�Ȼ���i����
			if (fun(&array[j], &array[key]) > 0)
				key = j;
		T t = array[key];
		array[key] = array[i];
		array[i] = t;
	}
}

//(6)������ʱ��O(nlogn), �ռ�O(1), ���ȶ�����
//�ؽ���
template<typename T>
void Restore(T *tree, int root, int n, int(*fun)(const T*a, const T*b))
{
	//tree���Ǵ�������飬root Ϊ���ؽ��Ķѵĸ���n��Ԫ�ظ���
	int m, j = root;
	//�Ӹ�һֱ�����һ����Ҷ���,���һ��Ҷ�ڵ�Ϊn���丸�ڵ�Ϊn/2ȡ�ذ�
	while (j <= (n / 2))
	{
		//�������������������ӽ��(2*j<n��֤)���ҵ����нϴ���Ǹ��ӽ����
		if (2 * j < n && fun(&tree[2 * j], &tree[2 * j + 1]) < 0)
			m = 2 * j + 1;//�Һ��ӽϴ�
		else//���ӽϴ󣬻���ֻ������(while������֤jһ��������)
			m = 2 * j;
		//�ж�root�費��Ҫ����
		if (fun(&tree[j], &tree[m]) < 0)
		{
			T t = tree[j];
			tree[j] = tree[m];
			tree[m] = t;
			j = m;//���������ֻ��Ӱ���Ϊm��������������ֻ��Ҫ����m��������
		}
		//��ǰ���Ѿ��ź���ֱ�ӽ����ؽ�
		else j = n;
	}
}
//������
template<typename T>
void HeapSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	//����Ҫ����2*i��2*i+1����Ҷ�ӽ�㣬��i����Ϊ0
	int *copy = new int[num + 1];
	for (int i = 1; i <= num; ++i)
		copy[i] = array[i - 1];

	//��ʼ���ѣ����¶��Ͻ��ѣ���������iΪ���Ķ�ʱ
	//��2i,2i+1Ϊ���ĶѶ��Խ�����ϣ�i�����һ����Ҷ��㿪ʼ
	for (int i = num / 2; i >= 1; i--)
		Restore(copy, i, num, fun);

	for (int i = num; i > 1; i--)
	{
		//���Ѷ�Ԫ�ػ�����β�����ؽ�������num-i+1����βԪ�صĶ�
		//�൱��ÿ�ν����(С)ֵ������i��λ���ϣ����ؽ�i��ǰ�Ķ�
		T t = copy[1];
		copy[1] = copy[i];
		copy[i] = t;
		//root = 1��i-1��Ԫ��
		Restore(copy, 1, i - 1, fun);
	}

	for (int i = 1; i <= num; ++i)
		array[i - 1] = copy[i];
	delete[] copy;
}

//(7)�鲢����ʱ��O(nlogn), �ռ�O(n),�ȶ�����
//�ϲ�����������low-mid, mid+1~high
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
	if (i > mid)//��벿�ֿ���û�ϲ���
		for (; j <= high; ++j)
			temp[index++] = array[j];
	else//ǰ�벿�ֿ���û�ϲ���
		for (; i <= mid; ++i)
			temp[index++] = array[i];
	//�ϲ����д��ԭ����
	for (index = low; index <= high; ++index)
		array[index] = temp[index - low];
	delete[] temp;
}
//�ϲ�
template<typename T>
void MergeSort(T* array, int num, int(*fun)(const T*a, const T*b))
{
	if (num > 1)
	{
		int mid = num / 2;
		MergeSort(array, mid, fun);//��벿������
		MergeSort(&array[mid], num - mid, fun);//�Ұ벿������
		Merge(array, 0, mid - 1, num - 1, fun);//�ϲ��ź����������
	}
	int test = 6;
}

//(8)��������(Ͱ����)��ʱ��O(np),�ռ�O(����m)
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

	queue<int> q[10];//�˴�ֻʵ�ֶ����������򣬻���=10
	queue<int> temp;
	for (int i = 0; i < num; ++i)
		temp.push(array[i]);
	int t, s = 1;
	while (s <= p)
	{
		//��Ͱ
		for (int i = 0; i < num; ++i)
		{
			t = temp.front();
			temp.pop();
			q[GetBit(t, s)].push(t);
		}

		//��Ͱ
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
//ֵ�ֲ��������ƹ�ϣ��ʽ


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