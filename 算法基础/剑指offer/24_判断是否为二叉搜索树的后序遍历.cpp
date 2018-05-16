//充分利用二叉搜索树性质

bool VerifySquenceOfBST(vector<int> sequence)
{
	int len = sequence.size();
	if(len<=0)
		return false;
	int rootval = sequence[len-1];
	
	vector<int> left, right;
	int i = 0;
	for( ; i<len-1 && sequence[i]<=rootval ;i++)
		left.push_back(sequence[i]);
	//此时i是>rootval 的第一个元素,右边的元素都应比rootval大
	
	for(int j=i;j<len-1;j++)
	{
		if(sequence[j]<rootval)//右子树元素有叛徒
			return false;
		right.push_back(sequence[j]);
	}
	bool flag = true;
	if(i>0)//有左子树
		flag = VerifySquenceOfBST(left);
	if(i<len-1)//有右子树
		flag = flag && VerifySquenceOfBST(right);
	return flag;
}