#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
// Definition for binary tree
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right, *next;
	TreeNode(int x) : val(x), left(NULL), right(NULL)
	{
	}
};
int PreOrder(TreeNode* root, int n);
int sumNumbers(TreeNode *root)
{
	int res = 0;
	res = PreOrder(root, res);
	return res;
}

int PreOrder(TreeNode* root, int n)
{
	if (root == NULL)
	{
		return 0;
	}
	n = n * 10 + root->val;
	if (root->left == NULL && root->right == NULL)
		return n;
	return PreOrder(root->left, n) + PreOrder(root->right, n);
}


void CreateTree(TreeNode *&root)
{
	char ch;
	cin >> ch;
	if (ch == '#')
	{
		root = NULL;
	}
	else
	{
		root = new TreeNode(ch - '0');
		CreateTree(root->left);
		CreateTree(root->right);
	}
}

typedef TreeNode TreeLinkNode;
void connect(TreeLinkNode *root)
{
	if (root == NULL)
		return;
	queue<TreeLinkNode*> q;
	TreeLinkNode* now, *last;
	q.push(root);
	last = now = root;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		if (now->left)
			q.push(now->left);
		if (now->right)
			q.push(now->right);
		if (now == last)
		{
			now->next = NULL;
			last = q.back();
		}
		else
			now->next = q.front();
	}
}


void GetPathSum(TreeNode* root, vector<vector<int> > &path, vector<int> &t, int csum, int sum)
{
	if (root == NULL)
		return;
	t.push_back(root->val);
	csum += root->val;
	if (root->left == NULL && root->right == NULL)
	{
		if (csum == sum)
			path.push_back(t);
		t.erase(--t.end());
		return;
	}
	GetPathSum(root->left, path, t, csum, sum);
	GetPathSum(root->right, path, t, csum, sum);

	t.erase(--t.end());
}

vector<vector<int> > pathSum(TreeNode *root, int sum)
{
	vector<vector<int> >path;
	vector<int> t;
	int csum = 0;
	GetPathSum(root, path, t, csum, sum);
	return path;
}



bool hasPathSum(TreeNode *root, int sum)
{
	if (root == NULL)
		return false;
	if (root->left == NULL && root->right == NULL && sum == root->val)
		return true;
	return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
}


bool IsBalanced(TreeNode*root, int &depth)
{
	//树为空，高度为0，且平衡
	if (root == NULL)
	{
		depth = 0;
		return true;
	}

	int left, right;
	//只有左右子树都是平衡的，且高度差在[-1,1]之间才是平衡树
	if (IsBalanced(root->left, left) && IsBalanced(root->right, right))
	{
		int diff = left - right;
		if (diff >= -1 && diff <= 1)
		{
			//树的高度为左右子树高度的最大值
			depth = (left > right ? left : right) + 1;
			return true;
		}
	}

	return false;
}
bool isBalanced(TreeNode *root)
{
	int depth = 0;
	return IsBalanced(root, depth);
}


vector<vector<int> > levelOrderBottom(TreeNode *root)
{
	vector<vector<int> > v;
	vector<int> t;
	if (root == NULL)
		return v;
	queue<TreeNode*> q;
	TreeNode* now, *last;
	q.push(root);
	last = now = root;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		t.push_back(now->val);
		if (now->left)
			q.push(now->left);
		if (now->right)
			q.push(now->right);
		if (now == last)
		{
			v.push_back(t);
			t.clear();
			last = q.back();
		}
	}
	reverse(v.begin(), v.end());
	return v;
}


TreeNode *Build(int* in, int *post, int len)
{
	if (len == 0)
		return NULL;
	TreeNode* head = new TreeNode(post[len - 1]);
	int i;
	for (i = 0; in[i] != post[len - 1]; i++);

	head->left = Build(in, post, i);
	head->right = Build(&in[i + 1], &post[i], len - i - 1);
	return head;
}

TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
{
	return Build(inorder.data(), postorder.data(), inorder.size());
}

int maxDepth(TreeNode *root)
{
	if (root == NULL)
		return 0;
	int l = maxDepth(root->left);
	int r = maxDepth(root->right);

	return (l > r ? l : r) + 1;
}


bool SSymmetricHelper(TreeNode* left, TreeNode*right)
{
	if (left == NULL && right == NULL)
		return true;
	else if ((left == NULL&& right != NULL) || (left != NULL&& right == NULL) || (left->val != right->val))
		return false;
	return SSymmetricHelper(left->right, right->left) && SSymmetricHelper(left->left, right->right);
}

bool isSymmetric(TreeNode *root)
{
	if (root == NULL)
		return true;
	return SSymmetricHelper(root->left, root->right);
}

bool isSameTree(TreeNode *p, TreeNode *q)
{
	if (p == NULL && q == NULL)
		return true;
	else if ((p == NULL && q != NULL) || (p != NULL && q == NULL) || (p->val != q->val))
		return false;

	return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);

}


class Solution
{
public:
	int m1 = 0, m2 = 0, t1, t2 = 0, t = 0;
	TreeNode*n1, *n2, *nt;
	void FindMistakes(TreeNode *root)
	{
		if (root == NULL)
			return;
		FindMistakes(root->left);
		t1 = t2;
		t2 = root->val;
		if (t1 > t2)
		{
			if (t == 0)
			{
				m1 = t1;
				m2 = t2;
				n1 = nt;
				n2 = root;
				t++;
			}
			else
			{
				m2 = t2;
				n2 = root;
			}
		}
		nt = root;
		FindMistakes(root->right);
	}
	void recoverTree(TreeNode *root)
	{
		if (root == NULL)
			return;
		FindMistakes(root);
		n1->val = m2;
		n2->val = m1;
	}
};

void PreOrder(TreeNode* root)
{
	if (root == NULL)
		return;
	PreOrder(root->left);
	cout << root->val << " ";
	PreOrder(root->right);
}


//532##6##84##9##

string reverseString(string iniString)
{
	int len = iniString.size();
	char t;
	for (int i = 0; i < len / 2; ++i)
	{
		t = iniString[i];
		iniString[i] = iniString[len - 1 - i];
		iniString[len - 1 - i] = t;
	}

	return iniString;
}
/*
 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15 16

旋转90

13  9 5 1
14 10 6 2
15 11 7 3
16 12 8 4

*/


vector<vector<int> > transformImage(vector<vector<int> > mat, int n)
{
	int t;
	//上下交换
	for (int i = 0; i < n / 2; i++)
	{
		for (int j = 0; j < n; j++)
		{
			t = mat[i][j];
			mat[i][j] = mat[n - i - 1][j];
			mat[n - i - 1][j] = t;
		}
	}
	//主对角线交换
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			t = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = t;
		}
	}
	return mat;
}

int test()
{
	int n, m, A, B;
	char op;

	while (cin >> n >> m)
	{
		int *stu = new int[n];
		for (int i = 0; i < n; i++)
			cin >> stu[i];
		for (int i = 0; i < m; i++)
		{
			cin >> op >> A >> B;
			if (op == 'Q')
			{
				if (A > B)
				{
					int t = A;
					A = B;
					B = t;
				}
				int max = stu[A - 1];
				for (int j = A - 1; j <= B - 1; j++)
					if (stu[j] > max)
						max = stu[j];
				cout << max << endl;
			}
			else
			{
				stu[A - 1] = B;
			}
		}

		delete[] stu;
	}

	return 0;
}


