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

const int maxN = 3e5+7;
int a[maxN];
struct node
{
	int mx_sum;
	int mx1;
	int mx2;
	node()
	{
		mx1 = mx2 = -1e8+9;
		mx_sum = 2*mx2;
	}
	node(int val)
	{
		mx1 = val;
		mx2 = -1e8+7;
		mx_sum = mx1+mx2;;
	}
	void merge(node left , node right)
	{
		vector<int> p(4);
		p[0] = left.mx1;
		p[1] = left.mx2;
		p[2] = right.mx1;
		p[3] = right.mx2;
		sort(all(p));
		mx1 = p[3];
		mx2 = p[2];
		mx_sum = mx1+mx2;
	}
}tree[4*maxN];


void build(int id, int left ,int right)
{
	if(left == right)
	{
		tree[id] = node(a[left]);  
		return;
	}
	int mid = mid(left ,right);
	build(2*id , left , mid);
	build(2*id+1,mid+1,right);
	tree[id] = node();
	tree[id].merge(tree[2*id],tree[2*id+1]);
}
void update(int id , int left ,int right , int index , int val)
{
	if(left == right)
	{
		tree[id] = node(val);
		return;
	}
	int mid = mid(left, right);
	if(index <= mid)
		update(2*id,left,mid,index,val);
	else
		update(2*id+1,mid+1,right,index,val);
	tree[id] = node();
	tree[id].merge(tree[2*id],tree[2*id+1]);
}

node query(int id , int left , int right ,int lq ,int rq)
{
	if(right < lq || left > rq)
		return node();
	if(left >= lq && right <= rq)
	{
		return tree[id];
	}
	int mid = mid(left , right);
	node n_l = query(2*id,left,mid,lq,rq);
	node n_r = query(2*id+1,mid+1,right,lq,rq);
	node temp = node();
	temp.merge(n_l,n_r);
	return temp;
}


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	int n; 
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&a[i]);
	int m; 
	build(1,0,n-1);
	scanf("%d",&m);
	while(m--)
	{
		char ch; 
		scanf(" %c",&ch);
		if(ch == 'U')
		{
			int i , x; 
			scanf("%d%d",&i,&x);
			i--;
			update(1,0,n-1,i,x);
			//update  
		}
		if(ch == 'Q')
		{
			int l , r; 
			scanf("%d%d",&l,&r);
			printf("%d\n",query(1,0,n-1,l-1,r-1).mx_sum);
			//query  
		}
	}
    return 0;
}

