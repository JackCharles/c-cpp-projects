//后进先出，相当于栈，用递归实现较为简洁

void printList(ListNode* head)
{
	if(head!=NULL)
	{
		if(head->next!=NULL)
			printList(head->next);
		printf("%d\t",head->val);
	}
}