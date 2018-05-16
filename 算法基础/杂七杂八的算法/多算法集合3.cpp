bool hasPathSum(TreeNode *root, int sum)
{
​	if(root==NULL)
		return false;
	return func(root, sum, 0);
}
​
​bool func(Node* root, int sum, int curr)
{
	if(root==NULL)
		return false;

	curr += root->val;
	if(curr==sum && root->left==NULL && root->right==NULL)
		return true;
	else
		return func(root->left, sum, curr) || func(root->right, sum, curr);
}