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

const int maxn = 4e4+7;
vector<pii> points(maxn);
map<int ,int> compress;

int tree[4*maxn];
int lazy[4*maxn];

void range_update(int node ,int left, int right ,int lq ,int rq , int val)
{
	if(lazy[node])
	{
		tree[node] = lazy[node];
		if(left != right)
		{
			lazy[2*node]  = lazy[node];
			lazy[2*node+1]  = lazy[node];
		}
		lazy[node] = 0;
	}
	if(left > rq || right < lq)
		return ;
	if(left >= lq && right <= rq)
	{
		tree[node] = val;
		if(left != right)
		{
			lazy[2*node]  = val;
			lazy[2*node+1]  = val;
		}
		lazy[node] = 0;
		return;
	}
	int mid = mid(left, right);
	range_update(2*node, left , mid , lq ,rq, val);
	range_update(2*node+1,mid+1,right, lq ,rq, val);
	tree[node] = val;
}


int query(int node ,int left ,int right ,int lq,int rq)
{
	if(lazy[node])
	{
		tree[node] = lazy[node];
		if(left != right)
		{
			lazy[2*node]  = lazy[node];
			lazy[2*node+1]  = lazy[node];
		}
		lazy[node] = 0;
	}
	if(left > rq || right < lq)
		return -1;
	if(left >= lq && right <= rq)
	{
			return tree[node];
	}
	int mid = mid(left, right);
	return max(query(2*node, left , mid , lq ,rq),query(2*node+1,mid+1,right, lq ,rq));
}

int main()
{
	int t; scanf("%d",&t);
	while(t--)
	{
		compress.clear();
		points.clear();
		for(int i = 0; i < 4*maxn;i++)
			tree[i] = lazy[i] = 0;

		int n ; 
		scanf("%d",&n);
		for(int i = 0; i < n; i++)
		{
			scanf("%d%d",&points[i].ff,&points[i].ss);  
			compress[points[i].ff] = compress[points[i].ss] = 1;
		}
		int a = 0;
		for(auto &x: compress)
			x.ss = a++;

		for(int i = 0; i < n; i++)
		{
			range_update(1,0,maxn-1,compress[points[i].ff] ,compress[points[i].ss],i+1);  
		}
		set<int> ans;
		for(int i = 0; i < maxn-1; i++)
		{
			ans.insert(query(1,0,maxn-1,i,i));
		}
		int k = ans.size();
		if(ans.find(0) != ans.end())
			k--;
		printf("%d\n",k);
	}
    return 0;
}

