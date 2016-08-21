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
#define left(x) 		   (x << 1)
#define right(x) 		   (x << 1) + 1
#define mid(l, r) 	       ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define debug3(x, y, z)    {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<"\n";}
#define debug4(x, y, z, w) {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<", "<<#w << " = " <<w <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))

const int mod=1e9+7;

template<class T> inline T gcd(T a,T b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
template<class T> inline T lcm(T a,T b){return a/gcd(a,b)*b;}
template<typename T, typename S> T expo(T b, S e, const T &m){if(e <= 1)return e == 0?1: b;\
	return (e&1) == 0?expo((b*b)%m, e>>1, m): (b*expo((b*b)%m, e>>1, m))%m;}
template<typename T> T modinv(T a) { return expo(a, mod-2, mod); }

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%lld",&x); return x; }

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);


const int maxn = 100007;


ll calc(ll n)
{
	if( n < 0 )
		return 0;
	return (1ll*n*(n+1))/2;
}
struct node
{
	ll sum;
	bool flag;
	ll start, end, incrm , numleaves;
	node()
	{
		sum = flag = start = end = 0;
		numleaves = 1;
	}
	node(int val)
	{
		sum = flag = start = end = numleaves = 0;
	}
	void merge(node &l ,node &r)
	{
		sum = l.sum + r.sum;
		numleaves = l.numleaves + r.numleaves;
	}
	void split(node &l , node &r, int left, int right)
	{
		if(left != right)
		{
			l.flag = r.flag = 1;
			l.start += start;
			l.end += (start + (l.numleaves-1)*incrm);
			r.start += (start + l.numleaves*incrm);
			r.end += end;
			r.incrm += incrm;
			l.incrm += incrm;
			l.sum +=( start*l.numleaves + calc(l.numleaves-1)*incrm);
			r.sum +=(start*numleaves)+incrm*(calc(numleaves-1)) - (start*l.numleaves)-incrm*(calc(l.numleaves-1));
		}
		start = end = flag = incrm = 0;
	}
}tree[4*maxn];

inline void build(int id ,int left ,int right)
{
	if(left == right)
	{
		tree[id] = node();
		return ;
	}
	int mid = mid(left,right);
	build(2*id,left,mid);
	build(2*id+1,mid+1,right);
	tree[id].merge(tree[2*id],tree[2*id+1]);
}

inline void range_update(int id ,int left, int right ,int lq ,int rq)
{
	if(tree[id].flag)
		tree[id].split(tree[2*id],tree[2*id+1],left,right);

	if(left > rq || right < lq)
		return ;
	
	if(left >= lq && right <= rq)
	{
		ll val1 = left-lq+1;
		ll val2 = (rq-lq+1) - (rq-right);
		tree[id].sum += (calc(val2)-calc(val1-1));
		tree[id].incrm++;
		tree[id].start += val1;
		tree[id].end += val2;
		tree[id].flag = false;
		tree[id].split(tree[2*id],tree[2*id+1],left,right);
		return ;
	}
	
	int mid = mid(left,right);
	range_update(2*id,left,mid,lq,rq);
	range_update(2*id+1,mid+1,right,lq,rq);
	tree[id].merge(tree[2*id],tree[2*id+1]);
}

inline node query(int id ,int left ,int right ,int lq ,int rq)
{
	if(tree[id].flag)
		tree[id].split(tree[2*id],tree[2*id+1],left,right);

	if(left > rq || right < lq)
		return node(0);

	if(left >= lq && right <= rq)
	{
		return tree[id];
	}
	
	int mid = mid(left,right);
	node nl = query(2*id,left,mid,lq,rq);
	node nr = query(2*id+1,mid+1,right,lq,rq);
	node temp;
	temp.merge(nl,nr);
	return temp;
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	ll n , q; cin >> n >> q;
	build(1,0,n-1);
	while(q--)
	{
		ll tp , l , r; cin >> tp >> l >> r;
		if(tp == 0)
		{
			//add  
			range_update(1,0,n-1,l-1,r-1);
		}
		else
		{
			//query  
			cout << query(1,0,n-1,l-1,r-1).sum << "\n";
		}
	}
	return 0;
}

