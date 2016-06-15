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
ll a[maxN];
ll last_ans ;
vector<ll> v[maxN];

void build(int id , int left ,int right)
{
	if(left == right)
	{
		v[id].push_back(a[left]);  
		return;
	}
	int mid = mid(left ,right);
	build(2*id,left,mid);
	build(2*id+1,mid+1,right);
	merge(all(v[2*id]),all(v[2*id+1]),back_inserter(v[id]));
}
ll query(int id ,int left ,int right ,int lq ,int rq , int k )
{
	if(left > rq || right < lq)
		return 0ll;
	if(left >= lq && right <= rq)
	{
		ll ans = v[id].size() - ( upper_bound(all(v[id]),k) - v[id].begin());
		return ans;  
	}
	int mid = mid(left, right);
	return query(2*id,left,mid,lq,rq,k) + query(2*id+1,mid+1,right,lq,rq,k);
}

/*
 * Memory O(nlogn)
 * each element is in logn nodes at most
 */

int main()
{

	int n; scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%lld",&a[i]);  
	build(1,0,n-1);
	int q;
	scanf("%d",&q);
	while(q--)
	{
		ll a , b , c ,  i , j , k;
		scanf("%lld%lld%lld",&a,&b,&c);
		i = a ^ last_ans;
		j = b ^ last_ans;
		k = c ^ last_ans;
		//query [i,j] 
		last_ans = 
		last_ans = query(1,0,n-1,i-1,j-1,k);
		printf("%lld\n",last_ans);
	}
    return 0;
}

