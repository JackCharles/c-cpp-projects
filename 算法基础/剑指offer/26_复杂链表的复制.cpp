#include<map>
#include <iostream>
using namespace std;

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};


//方法一：额外创建O(n)的哈希表保存复制前后的键值对<N,N'>

RandomListNode* CloneA(RandomListNode* pHead)
{
	if(pHead == NULL)
		return NULL;
	
    map<RandomListNode*, RandomListNode*> m;
	RandomListNode *newhead = NULL, *q = NULL;
	RandomListNode *p = pHead;
	while(p!=NULL)
	{	
		if(newhead == NULL)
		{
			newhead = new RandomListNode(p->label);
			q = newhead;
			//m.insert(pair<RandomListNode*, RandomListNode*>(p,q));
			m[p] = q;
		}
		else
		{
			q->next = new RandomListNode(p->label);
			q = q->next;
			//m.insert(pair<RandomListNode*, RandomListNode*>(p,q));
			m[p] = q;
		}
		p = p->next;
	}
	

	p = pHead;
	q = newhead;
	while(p!=NULL)
	{
		if(p->random!=NULL)
			q->random = m[p->random];
		p = p->next;
		q = q->next;
	}
	
	return newhead;
}

//方法二：将新复制的结点连接在原结点之后，
//然后根据原来链表指针确定新链表指针的位置，
//最后将新复制的链表拆分出来


RandomListNode* CloneB(RandomListNode* pHead)
{
	if(pHead == NULL)
		return NULL;
	
	//step1 复制链表
	RandomListNode *p = pHead, *q = NULL;
	while(p!=NULL)
	{
		q = new RandomListNode(p->label);
		q->next = p->next;
		p->next = q;
		p = q->next;
	}
	
	//step2 复制random指针
	p = pHead;
	while(p!=NULL)
	{
		q = p->next;
		if(p->random!=NULL)
			q->random = p->random->next;
		p = q->next;
	}
	
	//step3 拆分出新复制的链表
	RandomListNode *newhead;
	newhead = p = pHead->next;
	
	while(p->next!=NULL)
	{
		p->next = p->next->next;
		p = p->next;
	}
	
	return newhead;
}



int main()
{
	RandomListNode*head = NULL, *rear = NULL;
	for(int i=1;i<=5;i++)
	{
		RandomListNode* p = new RandomListNode(i);
		if(head == NULL)
		{
			head = p;
			rear = p;
		}
		else
		{
			rear->next = p;
			rear = p;
		}
	}
	//{1,2,3,4,5,3,5,#,2,#}
	head->random = head->next->next;
	head->next->random = head->next->next->next->next;
	head->next->next->next->random = head->next; 
	
	RandomListNode* a = CloneB(head);
	RandomListNode *x = a;
	while(x!=NULL)
	{
		cout<<x->label<<",";
		x = x->next;
	}
	x = a;
	cout<<endl;
	while(x!=NULL)
	{
		if(x->random!=NULL)
			cout<<x->random->label<<",";
		else
			cout<<"#"<<",";
		x = x->next;
	}
	
	return 0;	
}