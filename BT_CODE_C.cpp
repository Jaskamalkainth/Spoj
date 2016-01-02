/*
 *
 *    J1K7_7
 * 
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
#define pr(n)              printf("%d",n)
#define s(n)               scanf("%d",&n)
#define debug(x)	       {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		       memset(x,0,sizeof(x))
#define snuke(c,itr)       for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
const int mod=1e9+7;

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);

inline bool ispow2(int x){return (x!=0 && (x&(x-1))==0);} //0 or 1

int msb(unsigned x){ union { double a; int b[2]; }; a = x; return (b[1] >> 20) - 1023; }

template<class T>
inline void cinarr(T a, int n){ for (int i=0;i<n;++i) cin >> a[i];}

inline ll powmod(ll a,ll b) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}

inline ll gcd(ll a,ll b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
inline ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%lld",&x); return x; }

vector<ll> type[4];


ll mx_cnt = -1;
ll value = -1; 
void get( ll v )
{
	ll cnt = 0ll ;
	// x < v
	cnt += (ll)(lower_bound(all(type[0]),v) - type[0].begin()) ;

	//x > v
	
	cnt += (ll)(type[1].size() - (ll)(lower_bound(all(type[1]),v)- type[1].begin())  );

	// x = v
	cnt += (ll)(upper_bound(all(type[2]),v) - lower_bound(all(type[2]),v));


	// x != v
	
	cnt += ((ll)type[3].size() - (ll)(upper_bound(all(type[3]),v) - lower_bound(all(type[3]),v)));

	if ( mx_cnt == -1 || cnt > mx_cnt || ( cnt == mx_cnt && v < value) )
	{
		mx_cnt = cnt; value = v;  
	}
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);

	int n; cin >> n;
	for(int i = 1;  i <= n ; i++)
	{
		ll v; int tp; cin >> tp >> v;  
		type[tp-1].pb(v);
	}

	for(int i = 0; i < 4; i++)
		sort(all(type[i]));

	for(int i = 0; i < 4; i++)
	{
		for(auto ele : type[i])
		{
			get(ele);
			get(ele-1);
			get(ele+1);
		}
	}
	get(0);


	cout << mx_cnt << " " << value << "\n";

	return 0;
}

