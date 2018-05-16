//方法一：分别用中根遍历返回左边链和右边链，
//然后与root连接在一起即可，注意此过程返回，
//双向链表的左边头结点，因此要找到左边链的
//尾结点与root相连，右边链头结点直接与root
//相连，然后返回左边链头结点即可。

TreeNode* Convert(TreeNode* root)
{
	if (root == NULL)
		return NULL;
	TreeNode *LeftTree = Convert(root->left);
	if (LeftTree == NULL)
		LeftTree = root;
	else
	{
		TreeNode* p = LeftTree;
		while (p->right != NULL)
			p = p->right;
		p->right = root;
		root->left = p;
	}

	TreeNode* RightTree = Convert(root->right);
	root->right = RightTree;
	if (RightTree != NULL)
		RightTree->left = root;

	return LeftTree;
}

//方法二：中根遍历后将结点指针存到vector中，然后在连接

void InOrder(TreeNode* root, vector<TreeNode*> &v)
{
	if (root == NULL)
		return;
	InOrder(root->left, v);
	v.push_back(root);
	InOrder(root->right, v);
}

TreeNode* Convert(TreeNode* root)
{
	if (root == NULL)
		return NULL;
	vector<TreeNode*> v;
	InOrder(root, v);
	TreeNode *head = NULL, *p = NULL;
	for (int i = 0; i < v.size()-1; i++)
	{
		v[i]->right = v[i + 1];
		v[i + 1]->left = v[i];
	}

	return v[0];
}