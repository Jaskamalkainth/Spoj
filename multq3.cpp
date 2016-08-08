#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;


const int maxn = 1e5+7;

struct node
{
	int cnt0 , cnt1 , cnt2;
	node()
	{
		cnt0 = 1;
		cnt1 = cnt2 = 0;
	}
	node(int i)
	{
		cnt0 = i;
		cnt1 = cnt2 = 0;
	}
	void merge(node l ,node r)
	{
		cnt0 = l.cnt0 + r.cnt0;
		cnt1 = l.cnt1 + r.cnt1;
		cnt2 = l.cnt2 + r.cnt2;
	}
}tree[4*maxn];
int lazy[4*maxn];

inline void lazy_update(int id, int left ,int right)
{
	lazy[id] %= 3;
	if(lazy[id]  == 1)
	{
		int t0 = tree[id].cnt0;
		int t1 = tree[id].cnt1;
		int t2 = tree[id].cnt2;

		tree[id].cnt0 = t2;
		tree[id].cnt1 = t0;
		tree[id].cnt2 = t1;

	}
	if(lazy[id]  == 2)
	{
		int t0 = tree[id].cnt0;
		int t1 = tree[id].cnt1;
		int t2 = tree[id].cnt2;

		tree[id].cnt0 = t1;
		tree[id].cnt1 = t2;
		tree[id].cnt2 = t0;
	}
	if(left != right)
	{
		lazy[2*id] += lazy[id];
		lazy[2*id+1] += lazy[id];
	}
	lazy[id] = 0;
}
inline void build(int id ,int left ,int right)
{
	if(left == right)
	{
		tree[id] = node();
		return;
	}
	int mid = (left+right)/2;
	build(2*id,left,mid);
	build(2*id+1,mid+1,right);
	tree[id] = node(0);
	tree[id].merge(tree[2*id],tree[2*id+1]);
}

inline void range_update(int id ,int left ,int right ,int lq , int rq)
{
	if(lazy[id])
	{
		lazy_update(id, left ,right);
	}
	if(left > rq || right < lq)
		return;
	if(left >= lq && right <= rq)
	{

		int t0 = tree[id].cnt0;
		int t1 = tree[id].cnt1;
		int t2 = tree[id].cnt2;

		tree[id].cnt0 = t2;
		tree[id].cnt1 = t0;
		tree[id].cnt2 = t1;
		if(left != right)
		{
			lazy[2*id]++;
			lazy[2*id+1]++;
		}
		return ;
	}
	int mid = (left+right)/2;
	range_update(2*id,left,mid,lq,rq);
	range_update(2*id+1,mid+1,right,lq,rq);

	tree[id] = node();
	tree[id].merge(tree[2*id],tree[2*id+1]);
}


inline node range_query(int id ,int left, int right ,int lq ,int rq)
{
	if(lazy[id])
	{
		lazy_update(id,left,right);
	}
	if(left > rq || right < lq)
		return node(0);
	if(left >= lq && right <= rq)
		return tree[id];
	int mid = (left+right)/2;
	node t = node();
	node l = range_query(2*id,left,mid,lq,rq);
	node r = range_query(2*id+1,mid+1,right,lq,rq);
	t.merge(l,r);
	return t;
}


int main()
{
	int n, q; 
	scanf("%d%d",&n,&q);
	build(1,0,n-1);
	while(q--)
	{
		int tp , l ,r;
		scanf("%d%d%d",&tp,&l,&r);
		if(tp == 0)
			range_update(1,0,n-1,l,r);
		if(tp == 1)
		{
			int ans = range_query(1,0,n-1,l,r).cnt0;
			printf("%d\n",ans);
		}
		/*
		cout << "Tree\n";
		for(int i = 1; i < 8; i++)
			cout << i << " , " << tree[i].cnt0 << "\n";
		cout << "\n\n\n";
		cout << "Lazy Tree\n";
		for(int i = 1; i < 8; i++)
			cout << lazy[i] << "\n";

		cout << "\n\n\n";
*/	}
	return 0;
}
