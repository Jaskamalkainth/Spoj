#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxBITS = 20;


struct node{
	int lc, rc;
	node *left, *right;
	node()
	{
		lc = rc = 0;
		left = right = NULL;
	}
};


inline node* insert(node*  curr , int level, int N)
{
	if(level == -1)
		return curr;
	int b = N & (1 << level);  
	if(b)
	{
		curr->rc++;
		if(curr->right == NULL)
			curr->right = new node;
	curr->right = insert(curr->right,level-1 , N);
	}
	else
	{
		curr->lc++;
		if(curr->left == NULL)
			curr->left = new node;
	curr->left = insert(curr->left,level-1,N);
	}
	return curr;
}

inline int query(node* curr, int level ,int N, int K)
{
	if(level == -1 || curr == NULL)
		return 0;
	int bit_N = N & (1 << level);
	int bit_K = K & (1 << level);
	if(bit_K)
	{
		if(bit_N)
		{
			return curr->rc +  query(curr->left,level-1,N,K);
		}
		else
		{
			return curr->lc + query(curr->right,level-1,N,K);  
		}
	}
	else
	{
		if(bit_N)
		{
			return query(curr->right,level-1,N,K);
		}
		else
		{
			return query(curr->left,level-1,N,K);  
		}
	}
}
int main()
{
	int t; scanf("%d",&t);
	while(t--)
	{
		node *root = new node;
		int n , k; 
		scanf("%d%d",&n,&k);
		int p = 0;
		int q = 0;
		long long ans = 0; 
		root = insert(root, maxBITS,0);
		for(int i = 0; i < n; i++)
		{
			int x; scanf("%d",&x);
			q = p ^ x;
			ans += query(root,maxBITS, q , k );
			root = insert(root, maxBITS,q);
			p = q;
		}
		printf("%lld\n",ans);
	}

	return 0;
}
