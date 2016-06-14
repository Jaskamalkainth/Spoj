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


const int maxN = 3e4+7;
struct node
{
	int unmatched_open , unmatched_closed;
	node()
	{
		unmatched_open = unmatched_closed = 0;  
	}
	node(int val)
	{
		unmatched_open = unmatched_closed = val;  
	}
	void merge(node l , node r)
	{
		unmatched_open = l.unmatched_open + r.unmatched_open - min(l.unmatched_open ,r.unmatched_closed);
		unmatched_closed = l.unmatched_closed + r.unmatched_closed - min(l.unmatched_open , r.unmatched_closed);
	}
}tree[4*maxN];
		

char str[maxN];
void build(int id ,int left ,int right)
{
	if(left == right)
	{
		if(str[left] == '(')
		{
			tree[id].unmatched_open = 1;
			tree[id].unmatched_closed = 0;
		}
		else
		{
			tree[id].unmatched_open = 0;
			tree[id].unmatched_closed = 1;
		}
		return ;
	}
	int mid = mid(left, right);
	build(2*id,left,mid);
	build(2*id+1,mid+1,right);
	tree[id] = node();
	tree[id].merge(tree[2*id],tree[2*id+1]);
}
void update(int id , int left ,int right, int index)
{
	if(left == right)
	{
		if(str[index] == '(')
		{
			tree[id].unmatched_open = 0;
			tree[id].unmatched_closed = 1;
			str[index] = ')';
		}
		else
		{
			tree[id].unmatched_open = 1;
			tree[id].unmatched_closed = 0;
			str[index] = '(';
		}
		return;
	}
	int mid = mid(left, right);
	if(index <= mid)
		update(2*id,left,mid,index);
	else
		update(2*id+1,mid+1,right,index);
	tree[id] = node();
	tree[id].merge(tree[2*id],tree[2*id+1]);
}
int main()
{
	for(int tc = 1; tc <= 10; tc++)
	{
		for(int i = 0; i < 4*maxN; i++)
			tree[i] = node();
		printf("Test %d:\n",tc);
		int n;
		scanf("%d",&n);
		scanf("%s",str);
		build(1,0,n-1);
		int q;
		scanf("%d",&q);
		while(q--)
		{
			int k;
			scanf("%d",&k);
			if(k!=0)
			{
				update(1,0,n-1,k-1);
			}
			else
			{
				if(tree[1].unmatched_open == 0 && tree[1].unmatched_closed == 0)
					printf("%s\n","YES");
				else
					printf("%s\n","NO");
			}
		}
	}


    return 0;
}

