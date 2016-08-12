#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>
using namespace std;



struct trienode
{
	bool endofword;
	trienode *edge[10];
	trienode()
	{
		for(int i = 0; i < 10; i++)
			edge[i] = NULL;
		endofword = false;
	}
};

trienode *root;
int flag;

inline void insert(string str)
{
	int len = str.length();
	trienode *curr = new trienode;
	curr = root;
	if(root->edge[str[0]-'0'] == NULL)
		root->edge[str[0]-'0'] = new trienode;
	for(int i = 0; i < len; i++)
	{
		int dig = str[i] - '0';
		if(curr->endofword)
		{
			flag = 0;  //this means 
		}
		if(curr->edge[dig] == NULL)
		{
			curr->edge[dig] = new trienode;  
		}
		curr = curr->edge[dig];
	}
	curr->endofword = true;

	for(int i = 0; i < 10; i++)
		if(curr->edge[i] != NULL)
			flag = 0; // there exist a num > curr.length therfore common prefix hence flag = 0
}

int main()
{

	int t; scanf("%d",&t);
	while(t--)
	{
		flag = 1;
		root = new trienode;
		int n; scanf("%d",&n);
		for(int i = 0; i < n; i++)
		{
			string s; cin >> s;
			insert(s);
		}
		if(!flag)
		{
			cout << "NO\n";
			continue;
		}
		cout << "YES\n";
	}
	return 0;
}
