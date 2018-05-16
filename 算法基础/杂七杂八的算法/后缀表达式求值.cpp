#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

int evalRPN(vector<string> &tokens)
{
	if (tokens.size() == 0)
		return 0;
	stack<int> s;
	int len = tokens.size();
	for (int i = 0; i < len; i++)
	{
		string t = tokens[i];
		if (t == "+" || t == "-" || t == "*" || t == "/")
		{
			int op2 = s.top();
			s.pop();
			int op1 = s.top();
			s.pop();
			if (t == "+")
				s.push(op1 + op2);
			else if (t == "-")
				s.push(op1 - op2);
			else if (t == "*")
				s.push(op1 * op2);
			else
				s.push(op1 / op2);
		}
		else
			s.push(atoi(t.c_str()));
	}
	return s.top();
}

int main()
{
	vector<string> a = { "2", "1", "+", "3", "*" };
	cout << evalRPN(a);
	return 0;
}