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


const int MAXN = 1e5+7;
string s; 
int len;
int P[MAXN], HashF[MAXN], HashR[MAXN];
class RollingHash {
    public:
        RollingHash() {
            prime = 100001;
            mod1 = 1000000007;
            mod2 = 1897266401;
            P[0] = 1;
            for(int i=1; i<MAXN; i++) {
                P[i] = 1LL * P[i-1] * prime % mod1;
            }
        }

        void Construct() {
            HashF[0] = HashR[ len+1 ] = 0;
            for(int i=1; i<=len; i++) {
                HashF[i] = ( 1LL * HashF[i-1] * prime + s[i-1] ) % mod1;
                HashR[len-i+1] = ( 1LL * HashR[len-i+2] * prime + s[ len - i ] ) % mod1; 
            }
        }

        int GetForwardHash( int l, int r ) {
            if( l == 1 ) return HashF[r];
            int hash = HashF[r] - 1LL * HashF[l-1] * P[ r - l + 1 ] % mod1;
            if( hash < 0 ) hash += mod1;
            return hash;
        }
        int GetBackwardHash( int l, int r ) {
            if( r == len ) return HashR[l];
            int hash = HashR[l] - 1LL * HashR[r+1] * P[ r - l + 1 ] % mod1;
            if( hash < 0 ) hash += mod1;
            return hash;
        }
        bool IsPalin( int l, int r ) {
            if( r < l ) return true;
            return (GetForwardHash(l, r) == GetBackwardHash(l, r));
        }

    private:
        int prime, mod1, mod2;
};


int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	int k; cin >> k;
	cin >> s;
	len = s.length();
	RollingHash obj;
	obj.Construct();
	int ans = 0;
	for(int i = 1; i+k-1 <= len; i++)
	{
		if(obj.IsPalin(i,i+k-1))
			ans++;
	}
	cout << ans << "\n";

    return 0;
}

