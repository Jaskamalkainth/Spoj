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


	template<typename T >
T min_ ( T a , T b )
{
	return a > b ? b : a ;  
}

	template < typename T ,  typename... Ts >
T min_( T first , Ts... last )
{
	return  min_(first, min_(last...));
}

int main()
{
	ios_base::sync_with_stdio(false); cin.tie(0);

	int t; cin >> t;
	while(t--)
	{
		int n; cin >> n;
		char inp[n][n];
		int ans = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
			{
				cin >> inp[i][j];
				if(inp[i][j] == '#')
					ans = 1;
			}
		int up[n][n],left[n][n],right[n][n],down[n][n];
		
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(j == 0)
				{
					left[i][0] = (inp[i][0] == '#' ? 1 : 0);
					continue;
				}
				if(inp[i][j] == '#')
					left[i][j] = 1 + left[i][j-1];
				else
					left[i][j] = 0;
			}
		}
		for(int i = 0; i < n; i++)
		{
			for(int j = n-1; j >= 0; j--)
			{
				if(j == n-1)
				{
					right[i][n-1] = (inp[i][n-1] == '#' ? 1 : 0);
					continue;
				}
				if(inp[i][j] == '#')
					right[i][j] = 1 +right[i][j+1];
				else
					right[i][j] = 0;
			}
		}
		for(int j = 0; j < n; j++)
		{
			for(int i = 0; i < n; i++)
			{
				if(i == 0)
				{
					up[0][j] = (inp[0][j] == '#' ? 1 : 0);  
					continue;
				}
				up[i][j] = (inp[i][j] == '#' ? up[i-1][j] + 1 : 0 );
			}
		}
		
		for(int j = 0; j < n; j++)
		{
			for(int i = n-1; i >= 0; i--)
			{
				if(i == n-1)
				{
					down[n-1][j] = (inp[n-1][j] == '#' ? 1 : 0);  
					continue;
				}
				down[i][j] = (inp[i][j] == '#' ? down[i+1][j] + 1 : 0 );
			}
		}
		for(int i = 1; i < n; i++)
		{
			for(int j = 1; j < n; j++)
			{
				int t = min_(up[i][j], down[i][j] , right[i][j] , left[i][j]);
				ans = max( ans , t);
			}
		}
		cout << ans << "\n";
	}
	return 0;
}

