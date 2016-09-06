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

#define gc getchar
template <typename T> void scanint(T &x) {
	T c = gc(); while(((c < 48) || (c > 57)) && (c!='-')) c = gc();
	bool neg = false; if(c == '-') neg = true; x = 0; for(;c < 48 || c > 57;c=gc());
	for(;c > 47 && c < 58;c=gc())	x = (x*10) + (c - 48); if(neg)	x = -x;
}
ll pwr(ll base, ll p, ll mod){
ll ans = 1;while(p){if(p&1)ans=(ans*base)%mod;base=(base*base)%mod;p/=2;}return ans;
}

const int MAXN = 1e5+6;
/*
 * Suffix Array
 */
// isA[i] : rank array
// SA[i]  : Suffix array
// lcp[i] : lcp array
// GetLCP(i,j): lcp of any 2 suffixes.
int len;
int iSA[MAXN], SA[MAXN];
int cnt[MAXN], next_gen[MAXN], lcp[ MAXN ], LCP[MAXN][22]; //internal
bool bh[MAXN], b2h[MAXN],m_arr[MAXN];

string s; 
bool smaller_first_char(int a, int b){
	return s[a] < s[b];
}

void SuffixSort(int n) {
	for (int i=0; i<n; ++i){
		SA[i] = i;
	}
	sort(SA, SA + n, smaller_first_char);
	for (int i=0; i<n; ++i){
		bh[i] = i == 0 || s[SA[i]] != s[SA[i-1]];
		b2h[i] = false;
	}
	for (int h = 1; h < n; h <<= 1){
		int buckets = 0;
		for (int i=0, j; i < n; i = j){
			j = i + 1;
			while (j < n && !bh[j]) j++;
			next_gen[i] = j;
			buckets++;
		}
		if (buckets == n) break;
		for (int i = 0; i < n; i = next_gen[i]){
			cnt[i] = 0;
			for (int j = i; j < next_gen[i]; ++j){
				iSA[SA[j]] = i;
			}
		}
		cnt[iSA[n - h]]++;
		b2h[iSA[n - h]] = true;
		for (int i = 0; i < n; i = next_gen[i]){
			for (int j = i; j < next_gen[i]; ++j){
				int s = SA[j] - h;
				if (s >= 0){
					int head = iSA[s];
					iSA[s] = head + cnt[head]++;
					b2h[iSA[s]] = true;
				}
			}
			for (int j = i; j < next_gen[i]; ++j){
				int s = SA[j] - h;
				if (s >= 0 && b2h[iSA[s]]){
					for (int k = iSA[s]+1; !bh[k] && b2h[k]; k++) b2h[k] = false;
				}
			}
		}
		for (int i=0; i<n; ++i){
			SA[iSA[i]] = i;
			bh[i] |= b2h[i];
		}
	}
	for (int i=0; i<n; ++i){
		iSA[SA[i]] = i;
	}
}

void InitLCP(int n) {
	for (int i=0; i<n; ++i) 
		iSA[SA[i]] = i;
	lcp[0] = 0;
	for (int i=0, h=0; i<n; ++i) {
		if (iSA[i] > 0) {
			int j = SA[iSA[i]-1];
			while (i + h < n && j + h < n && s[i+h] == s[j+h]) 
				h++;
			lcp[iSA[i]] = h;
			if (h > 0) 
				h--;
		}
	}
}

void ConstructLCP() {
	InitLCP( len );
	for(int i = 0;i<len;++i)
		LCP[i][0] = lcp[i];
	for(int j = 1;(1<<j)<=len;++j){
		for(int i = 0;i+(1<<j)-1<len;++i){
			if(LCP[i][j-1]<=LCP[i+ ( 1<<(j-1) )][j-1])
				LCP[i][j] = LCP[i][j-1];
			else
				LCP[i][j] = LCP[i+(1<<(j-1))][j-1];
		}
	}
}

int GetLCP(int x, int y) {
	if(x == y) return len-SA[x];
	if(x > y) swap(x,y);
	int log = 0;
	while((1<<log)<=(y-x)) ++log;
	--log;
	return min(LCP[x+1][log],LCP[y-(1<<log)+1][log]);
}
/*
 * SA END/
 *
 */
//	SuffixSort(len);
//	ConstructLCP();


int main()
{
	int t; scanint(t);
	while(t--)
	{
		int n , k; 
		scanint(n);
		scanint(k);
		cin >> s;
		len = s.length();
		if(k == 1)
		{
			set<char> sss;
			for(auto c: s)
				sss.insert(c);
			cout << sss.size() << "\n";
			continue;

		}
		SuffixSort(len);
		ConstructLCP();


		ll ans = (len-SA[0] >= k)?1:0;
		for(int i = 1; i < len; i++)
		{
			int L = GetLCP(i-1,i);
			if(L < k && (len-SA[i]) >= k)
				ans++;
		}
		cout << ans << "\n";
	}
	return 0;
}

