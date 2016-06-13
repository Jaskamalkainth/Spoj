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
int a[maxN];

struct node
{
	int sum , bestSuffixSum, bestPrefixSum ,  bestSum;
	node()
	{
		sum = bestSuffixSum = bestPrefixSum = bestSum = 0;  
	}
	node(int val)
	{
		sum = bestSuffixSum = bestPrefixSum = bestSum = val; 
	}
	void merge(node left ,node right)
	{
		sum = left.sum + right.sum;
		bestPrefixSum  = max( left.bestPrefixSum , left.sum + right.bestPrefixSum);
		bestSuffixSum  = max( right.bestSuffixSum ,right.sum + left.bestSuffixSum);
		bestSum = max(left.bestSum , right.bestSum);
		bestSum = max( bestSum , left.bestSuffixSum + right.bestPrefixSum);
	}
	void printnode()
	{
		printf("( sum = %d , bestSuffixSum = %d , bestPrefixSum = %d , bestSum = %d )\n\n",sum,bestSuffixSum,bestPrefixSum,bestSum);   
	}
}tree[4*maxN];

void build(int id ,int left ,int right)
{
	if(left == right)
	{
		tree[id] = node(a[left]);
		return;
	}
	int mid = mid(left ,right);
	build(2*id,left ,mid);
	build(2*id+1, mid+1,right);
	tree[id] = node();
	tree[id].merge(tree[2*id],tree[2*id+1]);
}

node query(int id , int left , int right ,int lq ,int rq)
{
	if(lq > right || rq < left || lq > rq )
	{
		node n = node(-1000000);
		n.sum = 0;
		return n;
	}
	if(left >= lq && right <= rq)
		return tree[id];
	int mid = mid(left,right);
	node l = query(2*id,left,mid,lq,rq);
	node r = query(2*id+1,mid+1,right,lq,rq);
	node temp = node();
	temp.merge(l,r);
	return temp;
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);

	int t; 
	scanf("%d",&t);
	while(t--)
	{
		int n; 
		scanf("%d",&n);
		for(int i = 0; i < n; i++)
			scanf("%d",&a[i]);
		for(int i = 0; i < 4*maxN; i++)
			tree[i] = node();
		build(1,0,n-1);
	
		int m;
		scanf("%d",&m);
		while(m--)
		{
			int x1 , y1 , x2 , y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1--;
			x2--;
			y1--;
			y2--;

			int ans;
			// query
			//if no overlap
			if(y1 < x2)
				ans = query(1,0,n-1,x1,y1).bestSuffixSum + query(1,0,n-1,y1+1,x2-1).sum + query(1,0,n-1,x2,y2).bestPrefixSum;

			else
			{
				ans = query(1,0,n-1,x1,x2-1).bestSuffixSum + query(1,0,n-1,x2,y2).bestPrefixSum;
				ans = max( ans , query(1,0,n-1,x2,y1).bestSuffixSum + query(1,0,n-1,y1+1,y2).bestPrefixSum);
				ans = max( ans , query(1,0,n-1,x2,y1).bestSum);
			}

			printf("%d\n",ans);
		}
	}

    return 0;
}

