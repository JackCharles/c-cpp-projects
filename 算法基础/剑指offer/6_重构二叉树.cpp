#include <iostream>
using namespace std;

struct Node
{
	int val;
	Node *left;
	Node *right;
	Node(int v)
	{
		val = v;
		left = NULL;
		right = NULL;
	}
};

Node* RebuildTree(int* pre, int* in, int len)
{
	if(pre==NULL||in==NULL||len<=0)
		return NULL;
	
	int rootval = pre[0];
	Node* root = new Node(rootval);
	int i;
	for(i=0; i<len&&in[i]!=rootval; i++);
	if(i==len)
		return NULL;
	root->left = RebuildTree(&pre[1], in, i);
	root->right = RebuildTree(&pre[i+1], &in[i+1], len-i-1);
	
	return root;
}

void preOrder(Node* root)
{
	if(root == NULL)
		return;
	cout<<root->val<<" ";
	preOrder(root->left);
	preOrder(root->right);
}

int main()
{
	int pre[] = {1,2,4,7,3,5,6,8};
	int in[] = {4,7,2,1,5,3,8,6};
	Node* root = RebuildTree(pre, in, 8);
	
	preOrder(root);
	
	return 0;
}