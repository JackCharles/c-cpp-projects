vector<vector<int> > FindPath(TreeNode* root,int expectNumber)
{
	vector<vector<int> > res;
	if(root!=NULL)
	{
		int curr = 0;
		vector<int> currpath;//记录遍历的路径
		FindPathRec(root, expectNumber, curr, currpath, res);
	}
	return res;
}


void FindPathRec(TreeNode* root,//就是在先根遍历基础上增加了路径记录与判断功能
                 int sum,
                 int curr,
                 vector<int> &currpath,
                 vector<vector<int> >& allpath)
{
	curr += root->val;
	currpath.push_back(root->val);

	//当前节点是叶子节点 且 路径之和也成立
	if(root->left==NULL && root->right==NULL && curr==sum)
		allpath.push_back(currpath);//将该条路径加入结果中

	//否则继续遍历其左右子树
	if(root->left!=NULL)
		FindPathRec(root->left, sum, curr, currpath, allpath);
	if(root->right!=NULL)
		FindPathRec(root->right, sum, curr, currpath, allpath);

	//当前节点处理完毕(成功 or 失败)，回朔到上一个结点，继续处理其兄弟结点(if exist)
	currpath.pop_back();
}