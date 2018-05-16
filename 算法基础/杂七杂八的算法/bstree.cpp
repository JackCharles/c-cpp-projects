#pragma once
#include <iostream>
#include <ctime>

using namespace std;

template <typename T>
class BSTNode
{
public:

	BSTNode(const T& value, BSTNode<T> *leftptr = NULL, BSTNode<T> *rightptr = NULL)
		:val(value), left(leftptr), right(rightptr)
	{
	}
	T val;
	BSTNode<T> *left, *right;
};

template <typename T>
class BSTree
{
public:
	BSTree():root(NULL),NodeNum(0)
	{
		cout << "The default constructor is called successfully!" << endl;
	}
	BSTree(const T* const array, int num);
	BSTree(const BSTree<T>& tree);
	~BSTree();

	BSTNode<T>* Search(const T& key);
	bool Insert(const T& key);
	T Delete(const T& key);
	inline int GetNodeNum()
	{
		return NodeNum;
	}
	void InOrder(T* result, int length);

private:
	int NodeNum;
	BSTNode<T> *root;
	void DeleteTree(BSTNode<T> *root);
};


template <typename T>
BSTree<T>::BSTree(const BSTree<T>& tree)
{
	this->root = tree.root;
	this->NodeNum = tree.GetNodeNum();
	cout << "The copy constructor is called successfully!" << endl;
}

template<typename T>
BSTree<T>::BSTree(const T* const array, int num):root(NULL)
{
	if (num < 1)
		cout << "Illegal parameters, the array length must grater than 0!" << endl;
	else
	{
		srand(unsigned(time(NULL)));
		int k = rand() % num;
		root = new BSTNode<T>(array[k]);
		NodeNum = 1;

		for (int i = 0; i < num; ++i)
			if (i != k)
				if (!Insert(array[i]))
					cout << "The duplicate value <" << array[i] << "> is ignored!" << endl;
		cout << "The constructor is called successfully, and a tree with "
			<< NodeNum << " nodes was created!" << endl;
	}
}

template <typename T>
BSTree<T>::~BSTree()
{
	if (root == NULL)
		return;
	DeleteTree(root);
	NodeNum = 0;
	cout << "Destructor is called successfully." << endl;
}

template<typename T>
BSTNode<T>* BSTree<T>::Search(const T& key)
{
	if (root == NULL)
	{
		cout << "Can not find the key " << key << " !" << endl;
		return NULL;
	}

	BSTNode<T> *p = root;
	while (p != NULL)
	{
		if (p->val == key)
			return p;
		if (key < p->val)
			p = p->left;
		else
			p = p->right;
	}
	if (p == NULL)
		cout << "Can not find the key " << key << " !" << endl;
	return p;
}

template <typename T>
bool BSTree<T>::Insert(const T& key)
{
	if (root == NULL)
	{
		root = new BSTNode<T>(key);
		return true;
	}

	BSTNode<T> *t = root;
	while (t != NULL)
	{
		if (t->val == key)
		{
			cout << "The key to be inserted is alreday exists!" << endl;
			return false;
		}

		else if (key < t->val)
		{
			if (t->left == NULL)
			{
				t->left = new BSTNode<T>(key); NodeNum++;
				return true;
			}
			t = t->left;
		}
		else
		{
			if (t->right == NULL)
			{
				t->right = new BSTNode<T>(key); NodeNum++;
				return true;
			}
			t = t->right;
		}
	}
	return false;
}

template<typename T>
T BSTree<T>::Delete(const T & key)
{
	BSTNode<T>* t = NULL, *q = NULL;
	if (root == NULL || (q = Search(key)) == NULL)
	{
		cout << "The key to be deleted is not exists in this tree." << endl;
		return NULL;
	}

	if (q->right == NULL)
		t = q->left;
	else
	{
		t = q->right;
		if (t->left == NULL)
			t->left = q->left;
		else
		{
			BSTNode<T> *r = t;
			t = t->left;
			while (t->left != NULL)
			{
				r = t;
				t = t->left;
			}
			t->left = q->left;
			r->left = t->right;
			t->right = q->right;
		}
	}

	if (q == root)
		root = t;
	else
	{
		BSTNode<T>* father = root;
		while (1)
		{
			if (q->val < father->val)
			{
				if (father->left == q)
				{
					father->left = t;
					break;
				}
				father = father->left;
			}
			else
			{
				if (father->right == q)
				{
					father->right = t;
					break;
				}
				father = father->right;
			}
		}
	}
	T ret = q->val;
	delete q;
	NodeNum--;
	return ret;
}

template<typename T>
void InOrderCore(T * result, int &index, BSTNode<T> *root)
{
	if (root == NULL)
		return;
	InOrderCore(result, index, root->left);
	result[index++] = root->val;
	InOrderCore(result, index, root->right);
}

template<typename T>
void BSTree<T>::InOrder(T * result, int length)
{
	if (length < NodeNum)
	{
		cout << "The space for the return value is too small!" << endl;
		return;
	}
	int index = 0;
	InOrderCore(result, index, root);
}

template<typename T>
void BSTree<T>::DeleteTree(BSTNode<T>* root)
{
	if (root == NULL)
		return;
	DeleteTree(root->left);
	DeleteTree(root->right);
	delete root;
	root = NULL;
}
