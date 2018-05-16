#include <iostream>
#include <string>
using namespace std;

string processline(string line)
{
	int len = line.length();
	int i = 0, j = len - 1;
	for (; i < len && line[i] == ' '; ++i);
	string temp;
	while (i <= j)
	{
		if (line[i] == '_')
		{
			temp += "<em>";
			++i;
			string t;
			while (i <= j && line[i] != '_')
				t += line[i++];
			temp += processline(t);
			temp += "</em>";
			++i;
		}
		else if (line[i] == '[')
		{
			temp += "<a href=\"";
			string t;
			++i;
			while (i <= j && line[i] != ']')
				t += line[i++];
			i += 2;
			while (line[i] != ')')
				temp += line[i++];
			temp += "\">";
			temp += processline(t);
			temp += "</a>";
			++i;
		}
		else
			temp += line[i++];
	}
	return temp;
}

int main()
{
	string line;
	string EndTag;
	int i, j, k;
	while (getline(cin, line))
	{
		if (line.length() == 0)
			continue;
		else if (line[0] == '#')
		{
			for (i = 0; line[i] == '#'; ++i);
			cout << "<h" << i << ">";
			cout << processline(line.substr(i));
			cout << "</h" << i << ">" << endl;
		}
		else if (line[0] == '*')
		{
			cout << "<ul>" << endl;
			cout << "<li>";
			cout << processline(line.substr(1));
			cout << "</li>" << endl;
			while (getline(cin, line))
			{
				if (line[0] != '*')
					break;
				cout << "<li>";
				cout << processline(line.substr(1));
				cout << "</li>" << endl;
			}
			cout << "</ul>" << endl;
		}
		else
		{
			cout << "<p>";
			cout << processline(line);
			while (getline(cin, line))
			{
				if (line.length() == 0)
					break;
				cout << endl << processline(line);
			}
			cout << "</p>" << endl;
		}
	}
}