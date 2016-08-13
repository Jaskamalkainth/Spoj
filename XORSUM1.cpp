#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXBITS = 31;

struct node
{
	node *left, *right;
	node()
	{
		left = right = NULL;  
	}
};

inline void insert(node* curr, int level, int N)
{
	if(level == -1)
		return ; 
	int b = (N & (1 << level)) != 0;
	if(b)
	{
		if(curr->right  == NULL)
			curr->right = new node;
		 insert(curr->right,level-1,N);
	}
	else
	{
		if(curr->left  == NULL)
			curr->left = new node;
		insert(curr->left,level-1,N);
	}
}
inline void query(node *curr , int level , int N , long long& num)
{
	if(level == -1)
		return ;
	int bit_N = (N & (1 << level)) != 0;
	if(bit_N)
	{
		if(curr->left != NULL)
			query(curr->left,level-1,N,num);
		else
		{
			num += (1<<level);
			query(curr->right,level-1,N,num);
		}
	}
	else
	{
		if(curr->right != NULL)
		{
			num += (1<<level);
			query(curr->right,level-1,N,num);
		}
		else
			query(curr->left,level-1,N,num);
	}
}
int main()
{
	int t; scanf("%d",&t);
	while(t--)
	{
		int n; scanf("%d",&n);
		long long  p = 0;
		long long ans = -1;

		node* root = new node;
		insert(root,MAXBITS,0);
		for(int i = 0; i < n; i++)
		{
			long long num = 0;
			long long x; scanf("%lld",&x);

			p = p ^ x;

			insert(root,MAXBITS,p);
			query(root,MAXBITS,p,num);

			ans = max ( ans , num^p);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
