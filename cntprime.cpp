/*
 *    J1K7_7
 */
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <list>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <limits>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
typedef long double        ld;
typedef pair<int,int>      pii;
typedef pair<ll,ll>        pll;
typedef vector<int>        vi;
typedef vector<long long>  vll;
#define l(x) 		       (x << 1) + 1
#define r(x) 		       (x << 1) + 2
#define mid(l, r) 	       ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))
#define snuke(c,itr)       for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

template<class T>
inline bool ispow2(T x){return (x!=0 && (x&(x-1))==0);} //0 or 1

template<class T> inline T powmod(T a,T b,T mod) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}
template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%lld",&x); return x; }

const int mod=1e9+7;

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);

const int maxN = 1e4+7;
const int maxn = 1e6+7;
int tree[4*maxN];
int lazy[4*maxN];
int a[maxN];
int  pp[maxn+1];
inline void pre_sieve()
{
    for(ll i = 2; i < maxn; i++ )
        if( pp[i] == 0 )
            for(ll j = i*i; j < maxn; j += i)
                pp[j] = 1;
}
inline void build(int id ,int left , int right)
{
	if(left == right)
	{
		if(pp[a[left]] == 0)
			tree[id] = 1;  
		return;
	}
	int mid = mid(left,right);
	build(2*id,left,mid);
	build(2*id+1,mid+1,right);
	tree[id] = tree[2*id] + tree[2*id+1];
}

inline void range_update(int id ,int left ,int right , int lq ,int rq ,int val)
{
	if(lazy[id])
	{
		if(pp[lazy[id]] == 0)
			tree[id] = (right-left+1);
		else
			tree[id] = 0;  
		if(left != right)
		{
			lazy[2*id] = lazy[id];
			lazy[2*id+1] = lazy[id];
		}
		lazy[id] = 0;
	}
	if(left > rq || right < lq)
		return;
	if(left >= lq && right <= rq)
	{
		if(pp[val] == 0)
			tree[id] = (right-left+1);
		else
			tree[id] = 0;
		if(left != right)
		{
			lazy[2*id] = val;
			lazy[2*id+1] = val;
		}
		lazy[id] = 0;
		return ;
	}
	int mid = mid(left,right);
	range_update(2*id, left,mid,lq,rq,val);
	range_update(2*id+1,mid+1,right,lq,rq,val);
	tree[id] = tree[2*id] + tree[2*id+1];
}
inline int range_query(int id ,int left ,int right ,int lq ,int rq )
{
	if(lazy[id])
	{
		if(pp[lazy[id]] == 0)
			tree[id] = (right-left+1);
		else
			tree[id] = 0;  
		if(left != right)
		{
			lazy[2*id] = lazy[id];
			lazy[2*id+1] = lazy[id];
		}
		lazy[id] = 0;
	}
	if(left > rq || right < lq)
		return 0;
	if(left >= lq && right <= rq)
		return tree[id];
	int mid = mid(left,right);
	return range_query(2*id,left,mid,lq,rq) + range_query(2*id+1,mid+1,right,lq,rq);
}

int main()
{
	pre_sieve();
	int t; scanf("%d",&t);
	for(int i = 1; i <= t;i++)
	{
		for(int i = 0; i < 4*maxN; i++)
			tree[i] = lazy[i] = 0;
		printf("Case %d:\n",i);
		int n , q;
		scanf("%d%d",&n,&q);
		for(int i = 0; i < n; i++)
			scanf("%d",&a[i]);
		build(1,0,n-1);
		while(q--)
		{
			int tp; scanf("%d",&tp);
			if(tp == 0)
			{
				int x ,y ,v;
				scanf("%d%d%d",&x,&y,&v);
				range_update(1,0,n-1,x-1,y-1,v);
			}
			else
			{
				int x ,y;
				scanf("%d%d",&x,&y);
				printf("%d\n",range_query(1,0,n-1,x-1,y-1));
			}
		}
	}
    return 0;
}

