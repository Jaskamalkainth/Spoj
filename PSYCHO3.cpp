/*
 *    J1K7_7
 *
 *    You can use my contents on a Creative Commons - Attribution 4.0 International - CC BY 4.0 License.  XD 
 *    - JASKAMAL KAINTH
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
#include <cassert>
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
#define left(x)		   (x << 1)
#define right(x) 	   (x << 1) + 1
#define mid(l, r) 	   ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define debug(x)	   {cerr <<#x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define debug3(x, y, z)    {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<"\n";}
#define debug4(x, y, z, w) {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<", "<<#z<<" = "<<z<<", "<<#w << " = " <<w <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x) 		   memset(x,0,sizeof(x))

inline int nextint(){ int x; scanf("%d",&x);   return x; }
inline ll  nextll() { ll  x; scanf("%lld",&x); return x; }

#define gc getchar
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}
// variadics
template<typename T >T min_ ( T a , T b ) { return a > b ? b : a ; }
template < typename T ,  typename... Ts > T min_( T first , Ts... last ){ return  min_(first, min_(last...)); }

// lambda exp auto  square = [](int inp) { return inp * inp; } ;

template<class T, class S> std::ostream& operator<<(std::ostream &os, const std::pair<T, S> &t) {
	os<<"("<<t.first<<", "<<t.second<<")";
	return os;
}
template<typename T> ostream& operator<< (ostream& out, const vector<T>& v) {
    out << "["; size_t last = v.size() - 1; for(size_t i = 0; i < v.size(); ++i) {
    out << v[i]; if (i != last) out << ", "; } out << "]"; return out;
}

ll pwr(ll base, ll p, ll mod){
ll ans = 1; while(p) { if(p&1) ans=(ans*base)%mod; base=(base*base)%mod; p/=2; } return ans;
}
ll gcd(ll a, ll b) {  return b == 0 ? a : gcd(b,a%b); }
ll lcm(ll a, ll b) {  return a*(b/gcd(a,b)); }

const long double PI = (long double)(3.1415926535897932384626433832795);
const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();
const int mod = 1e9+7;
const int oo = 0x3f3f3f3f;
const ll  OO = 0x3f3f3f3f3f3f3f3fll;

const int maxn  = 1107;
const int maxk = 1e5+7;
int pp[maxn] , sp[maxn];
int dp[maxk][maxn];

bool is_subset_sum(vector<int>& v,int sum)
{
	int n=v.size();
	vector<int>dp(sum+1,0);
	dp[0]=1; //sum =0 is always attainable.

	for(int i=0;i<n;i++)for(int j=sum;j>=v[i];j--)
		dp[j]|=dp[j-v[i]];

	return dp[sum];
}

map<int,int> mm;
	
vi pshyco_num;
inline void pre()
{
	for(int i = 2; i < maxn; i++)
	{
		if(!pp[i])
		{
			sp[i] = i;
			for(int j = i*i; j < maxn; j += i)
			{
				if(!pp[j])
				{
					sp[j] = i;
					pp[j] = 1;
				}
			}
		}
	}
	for(int i = 2; i < maxn; i++)
	{
		int x = i;
		int o = 0, e = 0;
		map<int,int> pw_;
		while(x > 1)
		{
			pw_[sp[x]]++;
			x /= sp[x];
		}
		for(auto &i: pw_)
		{
			if(i.ss&1)
				o++;
			else
				e++;
		}
		if(e > o)
			pshyco_num.pb(i);
	}
	for(auto &i: pshyco_num)
	{
		mm[i] = 1;
	}
}
int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);
	
	pre();
	int t; cin >> t;
	while(t--)
	{
		int n , k; cin >> n >> k;
		vi ps_num;
		for(int i = 0; i < n; i++)
		{
			int x; cin >> x;
			if(mm[x])
				ps_num.pb(x);
		}
		int nsz = ps_num.size();
	
		int sum = 0;
		for(auto i: ps_num)
			sum += i;
		if(sum < k )
		{
			cout << "No\n";
			continue;
		}
		if(is_subset_sum(ps_num,k))
		{
			cout << "Yes\n";  
		}
		else
		{
			cout << "No\n";
		}
		// dp on ps_num .
	}

    return 0;
}

