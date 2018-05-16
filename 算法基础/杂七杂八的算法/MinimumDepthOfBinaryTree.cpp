//Minimum Depth of Binary Tree
#include <iostream>
#include <queue>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left, *right;
};

int run(TreeNode *root)
{
	if (root == NULL)
		return 0;

	int LeftDepth = run(root->left);
	int RightDepth = run(root->right);

	if (LeftDepth == 0)//深度为0是无效的
		return RightDepth + 1;
	else if (RightDepth == 0)
		return LeftDepth + 1;

	return (LeftDepth < RightDepth ? LeftDepth : RightDepth) + 1;
}


int run(TreeNode *root)
{
	//采用广度优先搜索，或者层序遍历，找到的第一个叶节点的深度即是最浅。
	if (root == NULL)
		return 0;
	queue<TreeNode*> q;
	TreeNode *last, *now;
	int level = 1;
	q.push(root);
	last = now = root;

	while (!q.empty())
	{
		now = q.front();
		q.pop();
		if (now->left == NULL && now->right == NULL)
			return level;
		else
		{
			if (now->left)
				q.push(now->left);
			if (now->right)
				q.push(now->right);
			if (now == last)
			{
				level++;
				last = q.back();
			}
		}
	}
}