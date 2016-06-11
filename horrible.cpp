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

const int maxN  = 2e5+7;

ll tree[5*maxN];
ll lazy[5*maxN];


void update(int node ,int left ,int right, int lq, int rq , int x)
{
	if(lazy[node])
	{
		tree[node] += (right-left+1)*1ll*lazy[node];
		if(left != right)
		{
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		lazy[node] = 0;
	}
	// no overlap
	if( lq > right || rq < left )
		return;
	//total overlap
	if( left >= lq && right <= rq )
	{
		tree[node] += (right-left+1)*1ll*x;
		if(left != right)
		{
			lazy[2*node] += x;
			lazy[2*node+1] += x;
		}
		lazy[node] = 0;
		return;
	}
	// partial overlap
	
	int mid = mid(left,right);
	update(2*node,left,mid,lq,rq,x);
	update(2*node+1,mid+1,right,lq,rq,x);

	tree[node] = tree[2*node] + tree[2*node+1];
}

ll query(int node,int left , int right, int lq, int rq)
{
	if(lazy[node])
	{
		tree[node] += (right-left+1)*1ll*lazy[node];
		if(left != right)
		{
			lazy[2*node] += lazy[node];
			lazy[2*node+1] += lazy[node];
		}
		lazy[node] = 0;
	}
	// no overlap
	if( lq > right || rq < left )
		return 0;
	//total overlap
	if( left >= lq && right <= rq )
	{
		return tree[node];
	}
	int mid = mid(left,right);
	return query(2*node,left,mid,lq,rq) + query(2*node+1,mid+1,right,lq,rq);
}

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	int t; cin >> t;
	while(t--)
	{
		for(int i = 0; i < 5*maxN; i++)
		{
			tree[i] = lazy[i] = 0;  
		}
		int n , q; cin >> n >> q;
		while(q--)
		{
			int tp; cin >> tp;
			if(tp == 0 )
			{
				int l , r , x; cin >> l >> r >> x;
				update(1,0,n-1,l-1,r-1,x);
				//add x in [l,r]
				//update
			}
			else if(tp == 1)
			{
				int l , r; cin >> l >> r;
				cout << query(1,0,n-1,l-1,r-1) << "\n";
				// query the sum in [l,r]
			}
		}
	}
    return 0;
}

