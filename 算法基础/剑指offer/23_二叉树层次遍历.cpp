
vector<int> PrintFromTopToBottom(TreeNode* root)
{
	vector<int> res;
	queue<TreeNode*> q;
	if(root!=NULL)
	{
		q.push(root);
		
		while(!q.empty())
		{
			TreeNode* t = q.front();
			q.pop();
			res.push_back(t->val);
			if(t->left!=NULL)
				q.push(t->left);
			if(t->right!=NULL)
				q.push(t->right);
		}
	}
	
	return res;
}