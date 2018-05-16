

bool IsPopOrder(vector<int> pushV,vector<int> popV)
{
	bool flag = true;
	stack<int> a;
	int j = 0;
	int len = pushV.size();
	for(int i=0; i<len; i++)
	{
		if(pushV[i]!=popV[j])
			a.push(pushV[i]);
		else
			++j;
	}

	while(!a.empty())
	{
		if(a.top()!=popV[j])
		{
			flag=false;
			break;
		}

		a.pop();
		j++;
	}
	return flag;
}