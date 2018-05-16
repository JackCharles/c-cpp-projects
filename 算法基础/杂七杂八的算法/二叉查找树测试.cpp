#include <iostream>
#include "bstree.h"

using namespace std;

int main()
{
	int a[20] = { 1,2,3,4,5,6,7,8,9,0,0,0};
	BSTree<int> bstree(a, 20);
	BSTNode<int>* ret = bstree.Search(0);
	if (ret != NULL)
		cout << ret->val << endl;
	bstree.Delete(4);
	bstree.Insert(1);
	bstree.Search(0);
	int len = bstree.GetNodeNum();
	if (len > 0)
	{
		int *res = new int[len];
		bstree.InOrder(res, len);
		for (int i = 0; i < len; ++i)
			cout << res[i] << " ";
		cout << endl;
		delete[] res;
	}
	return 0;
}