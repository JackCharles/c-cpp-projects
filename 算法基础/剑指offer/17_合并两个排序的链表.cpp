//递归法

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if(pHead1==NULL)
		return pHead2;
	else if(pHead2==NULL)
		return pHead1;
	
	ListNode* pMergeHead = NULL;
	if(pHead1->val < pHead2->val)
	{
		pMergeHead = pHead1;
		pMergeHead->next = Merge(pHead1->next, pHead2);
	}
	else
	{
		pMergeHead = pHead2;
		pMergeHead->next = Merge(pHead1, pHead2->next);
	}
	
	return pMergeHead;
}

//一般法

ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if(pHead1==NULL)
		return pHead2;
	else if(pHead2==NULL)
		return pHead1;
	
	ListNode* pMergeHead = NULL;
	ListNode* p1 = NULL;
	ListNode* p2 = NULL;
	if(pHead1->val < pHead2->val)
	{
		pMergeHead = pHead1;
		p1 = pHead1;
		p2 = pHead2;
	}
	else
	{
		pMergeHead = pHead2;
		p1 = pHead2;
		p2 = pHead1;
	}
	
	//这才是核心
	while(p2!=NULL)
	{
		while(p1->next!=NULL)
		{
			if(p2->val>=p1->val&&p2->val<=p1->next->val)
			{
				ListNode* t = p2->next;
				p2->next = p1->next;
				p1->next = p2;
				p2 = t;
				break;
			}
			
			p1 = p1->next;
		}
		
		if(p1->next==NULL)
		{
			p1->next = p2;
			break;
		}
	
	}
	
	return pMergeHead;
}