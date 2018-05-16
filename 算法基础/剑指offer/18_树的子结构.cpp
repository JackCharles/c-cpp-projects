
//在树A中查找与树B根节点相同的结点
bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
{
	bool result = false;
	
	if(pRoot1!=NULL && pRoot2!=NULL)
	{
		if(pRoot1->val == pRoot2->val)//树A的根节点等于树B的根节点
			result = DoesTree1HaveTree2(pRoot1, pRoot2);//判断它的子树是否含有B树的结构
		if(!result)//如果根不一样，或者没有B树子结构
			result = HasSubtree(pRoot1->left, pRoot2);//继续查找A的左子树
		if(!result)
			result = HasSubtree(pRoot1->right, pRoot2);//查找A的右子树
	}
	
	return result;
}

//判断是否含有子结构
bool DoesTree1HaveTree2(TreeNode* pRoot1, TreeNode* pRoot2)
{
	if(pRoot2 == NULL)
		return true;
	if(pRoot1 == NULL)
		return false;
	if(pRoot1->val != pRoot2->val)//子结构的条件是根节点相等，然后左右子结点相等，直到
		return false;//B树遍历完true，或A树遍历完false
	return DoesTree1HaveTree2(pRoot1->left, pRoot2->left) &&
		DoesTree1HaveTree2(pRoot1->right, pRoot2->right);
}