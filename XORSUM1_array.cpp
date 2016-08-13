#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxBITS = 31;
const int maxn =3e5*32;
int trie[maxn][2];
int sz = 1;

inline void clear()
{
	trie[0][0] = trie[0][1] = -1;
}

inline void insert(int N)
{
	int node = 0;
	for(int i = maxBITS; i >= 0; i--)
	{
		int b = ( N & (1 << i )) != 0;
		if(trie[node][b] == -1)
		{
			trie[node][b] = sz;
			trie[sz][0] = trie[sz][1] = -1;
			sz++;
		}
		node = trie[node][b];
	} 
}
inline long long query(int X)
{
	int node = 0;
	long long ans = 0;
	for(int i = maxBITS; i >= 0; i--)
	{
		int ok = 1;
		int b = ( X & (1 << i )) != 0;
		if(trie[node][b^1] == -1)
		{
			ok = 0;  
			node = trie[node][b];
		}
		else
		{
			node = trie[node][b^1];
		}
		if(ok)
		{
			ans += (1 << i);  
		}
	}
	return ans;
}
int main()
{
	int t;
	scanf("%d",&t);
	while(t--)
	{
		clear();
		int n; 
		scanf("%d",&n);
		long long p = 0;
		long long ans = -1;
		insert(0);
		for(int i = 0; i < n; i++)
		{
			int x; 
			scanf("%d",&x);
			p ^= x;
			insert(p);
			ans = max(ans , query(p));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
