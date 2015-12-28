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
typedef unsigned long long ll;
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

inline ll pow(ll a,ll b) {ll res = 1; while(b){if(b&1) res = (res*a);a = (a*a);b >>= 1;}return res;}

inline ll gcd(ll a,ll b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
inline ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

inline int nextint(){ int x; scanf("%d",&x); return x; }
inline ll nextll(){ ll x; scanf("%llu",&x); return x; }

const int maxN = 1e8+7;
int  pp[maxN+1];
vector <ll> prime;
inline void pre_sieve()
{
    // there are 1007 primes < 8000 
    // there are 78499   primes < 1e6+7
    for(ll i = 2; i < maxN; i++ )
        if( pp[i] == 0 )
            for(ll j = i*i; j < maxN; j += i)
                pp[j] = 1;

    for(int i =2; i< maxN; i++)
        if(pp[i] == 0)
            prime.push_back(i);
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);

	int t = nextint();
	pre_sieve();
	while(t--)
	{
		ll sum = 1ll;
		ll n = nextll();
		ll cache_n = n;
		ll i; 
		ll t; 
		ll  wt;
		for(  i = 0 , t = prime[i]; i < prime.size() && t * t <= n ; t = prime[++i])
		{
			if (  n % t == 0)
			{
				wt = 0;
				while( n % t == 0 )
				{
					wt++;
					n /= t;
				}
				sum *= ( (pow(t,wt+1)-1) / (t-1) );
				//debug2(t , n );
			}
		}
		if ( n > 1)
		{
			sum *= (n+1);  
		}
		sum -= cache_n;
		printf("%llu\n",sum);
	}

	return 0;
}

