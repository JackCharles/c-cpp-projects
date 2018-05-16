#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <set>
using namespace std;

//Definition for undirected graph.
struct UndirectedGraphNode
{
	int label;
	vector<UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x)
	{
	};
};


UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node)
{
	if (node == NULL)
		return NULL;
	//DFS copy
	stack<UndirectedGraphNode*> s;
	map<int, UndirectedGraphNode*> m;//将复制的结点放到map中，以lable为key
	s.push(node);
	UndirectedGraphNode* copy = new UndirectedGraphNode(node->label);//返回点
	m[node->label] = copy;//map中放入第一个复制的结点
	while (!s.empty())//DFS
	{
		UndirectedGraphNode* p = s.top();
		s.pop();

		vector<UndirectedGraphNode*> neighbor = p->neighbors;
		//遍历p的邻居
		for (vector<UndirectedGraphNode*>::iterator it = neighbor.begin(); it < neighbor.end(); ++it)
		{
			if (m.count((*it)->label) == 0)//如果邻居结点还没有被复制
			{
				UndirectedGraphNode* t = new UndirectedGraphNode((*it)->label);//复制邻居
				m[(*it)->label] = t;//加入map
				s.push(*it);//邻居压栈，注意这里是压栈前已经访问，故弹栈后不再需要访问结点本身
			}

			//将当前节点对应复制结点，的邻居补充完整，这里vector只能加入新复制结点的指针
			m[p->label]->neighbors.push_back(m[(*it)->label]);
		}

	}
	return copy;
}


string minWindow(string S, string T)
{
	int slen = S.length(), tlen = T.length();
	multiset<char> s;
	int min = 99999;
	char *temp = new char[slen];
	char tstr[128] = { 0 };
	int index = 0;
	string res;
	for (int i = 0; i < slen; i++)
	{
		if (T.find(S[i]) != string::npos)
		{
			memset(tstr, 0, 128);
			for (int k = 0; k < tlen; ++k)
				tstr[T[k]]++;
			index = 0;
			for (int j = i; j < slen; j++)
			{
				temp[index] = S[j];
				index++;
				if (T.find(S[j]) != string::npos)
				{
					tstr[S[j]]--;
					bool flag = true;
					for (int k = 0; k < tlen; ++k)
						if (tstr[T[k]] > 0)
						{
							flag = false;
							break;
						}
					if (flag)
					{
						if (min > index)
						{
							min = index;
							res = string(temp, min);
						}
						break;
					}
				}
			}
		}
	}

	return res;
}


int main()
{
	string S = "a";
	string T = "a";
	string res = minWindow(S, T);
	cout << res;
	return 0;
}





class Solution
{
public:
	//维持一个窗口滑动，左边是left，右边是right，然后判断是否包含T
	string minWindow(string S, string T)
	{
		string result;
		if (!S.size() || !T.size())
		{
			return result;
		}

		map<char, int>Tmap; //存储T字符串里字符，便于与S匹配
		int left = 0;		//左边窗口,起始为0
		int count = 0;		//计数器，对窗口内T串字符数量进行计数,起始为0
							//装载T串
		int minlen = S.size() + 1;		//最小窗口，便于比较最后取最小的,初始化取最大
		for (int i = 0; i < T.size(); ++i)
		{
			Tmap[T[i]]++;
		}
		//移动右边窗口
		for (int right = 0; right < S.size(); ++right)
		{
			if (Tmap.find(S[right]) != Tmap.end())	//当窗口内部有T中的字符
			{
				if (Tmap[S[right]] > 0)
					count++;	//计数器+1
				Tmap[S[right]]--;	//去掉包含的，剩下都是没包含的
				while (count == T.size())//当窗口内有T的所有字符，就要开始移动左窗口啦
				{
					if (Tmap.find(S[left]) != Tmap.end())
					{
						//好了，这就是一个包含字符串的窗口范围：left ~ right, 
						//判断是否比当前窗口还小，是就取串
						if (minlen > right - left + 1)
						{
							//更新窗口大小
							minlen = right - left + 1;
							result = S.substr(left, right - left + 1);
						}
						//舍弃窗口左边字符串，继续移动窗口
						Tmap[S[left]]++;
						if (Tmap[S[left]] > 0)	//如果左边连续相同，则count不递减，窗口需要继续向右移动
						{
							count--;
						}
					}
					left++;	//移动左窗口
				}
			}
		}
		return result;
	}
};