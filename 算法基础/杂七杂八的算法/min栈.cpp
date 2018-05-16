#include <stack>
using namespace std;

class Solution
{
public:
	void push(int value)
	{
		val_stack.push(value);
		if (min_stack.empty())
			min_stack.push(value);
		else
		{
			int t = min_stack.top();
			min_stack.push(t > value ? value : t);
		}
	}
	void pop()
	{
		val_stack.pop();
		min_stack.pop();
	}
	int top()
	{
		return val_stack.top();
	}
	int min()
	{
		return min_stack.top();
	}
	stack<int>val_stack;
	stack<int>min_stack;
};