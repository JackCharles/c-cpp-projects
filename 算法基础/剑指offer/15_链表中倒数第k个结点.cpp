
//获取倒数第k个节点
ListNode* FindKthToTail(ListNode* pListHead, int k)
{
	if(pListHead==NULL || k<1)
		return NULL;
	
	ListNode* p = pListHead;
	for(int i=0;i<k-1;i++)
	{
		if(p->next==NULL)
			return NULL;
		p = p->next;
	}
	
	ListNode* res = pListHead;
	while(p->next!=NULL)
	{
		p = p->next;
		res = res->next;
	}
	
	return res;
}