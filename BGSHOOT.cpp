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

const int maxN = 2e5+7;
map<ll,ll> compress;
vector<pair<ll,ll> > seg(maxN), qq(maxN);
ll cnt[maxN];
ll tree[4*maxN];
void build(int node ,int left ,int right)
{
	if(left == right)
	{
		tree[node] = cnt[left];
		return;
	}
	int mid = mid(left, right);
	build(2*node , left  ,mid);
	build(2*node+1,mid+1,right);
	tree[node] = max ( tree[2*node],tree[2*node+1]);
}

int query(int node ,int left ,int right , int lq, int rq)
{
	if(left > rq || right < lq)
		return -1000000;
	if(left >= lq && right <= rq)
		return tree[node];
	int mid = mid(left, right);
	int q1 = query(2*node,left,mid,lq,rq);
	int q2 = query(2*node+1,mid+1,right,lq,rq);
	return max(q1,q2);
}


int main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		ll l , r; 
		scanf("%lld%lld",&l,&r);
		seg[i].ff = l;
		seg[i].ss = r;
		compress[l] = compress[r] = 1;
	}
	int q; 
	scanf("%d",&q);
	for(int i = 0; i < q; i++)
	{
		ll l , r;  
		scanf("%lld%lld",&l,&r);
		qq[i].ff = l;
		qq[i].ss = r;
		compress[l] = compress[r] = 1;
	}
	ll a = 0;
	for(auto &x: compress)
		x.ss = a++;

	for(int i = 0; i < n ; i++)
	{
			cnt[compress[seg[i].ff]]++;
			cnt[compress[seg[i].ss]+1]--;
	}
	for(int i = 0; i < maxN; i++)
		cnt[i] += cnt[i-1];

	build(1,0,maxN-1);
	for(int i = 0; i < q; i++)
	{
		printf("%d\n",query(1,0,maxN-1,compress[qq[i].ff],compress[qq[i].ss]));  
	}
    return 0;
}

