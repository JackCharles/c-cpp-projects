//反转链表

ListNode* ReverseList(ListNode* pHead)
{
	if(pHead == NULL)
		return NULL;
	else if(pHead->next == NULL)
		return pHead;
	
	ListNode* pre = pHead;
	ListNode* cuur = pHead->next;
	ListNode* res = NULL;
	pHead->next = NULL;
	while(cuur!=NULL)
	{
		if(cuur->next==NULL)
			res = cuur;
		ListNode* temp = cuur->next;
		cuur->next = pre;
		pre = cuur;
		cuur = temp;
	}
	return res;
}