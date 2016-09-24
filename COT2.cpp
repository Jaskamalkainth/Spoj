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

const int maxn = 80001;
const int maxm = 1e5+7;
int wt[maxn];
vi G[maxn];
int st[maxn], en[maxn] , timer = 0;
int ID[maxn];
const int MAXN = 4e4+7; 
const int MAXLOG = 18; 
int par[MAXN][MAXLOG]; 
int d[MAXN];
void dfs(int v,int p = -1){
	st[v] = ++timer;
	ID[timer] = v;
    par[v][0] = p;
    if(p + 1)
        d[v] = d[p] + 1;
    for(int i = 1;i < MAXLOG;i ++)
        if(par[v][i-1] + 1)
            par[v][i] = par[par[v][i-1]][i-1];
    for(auto u : G[v])
        if(p - u)
            dfs(u,v);
	en[v] = ++timer;
	ID[timer] = v;
}
int lca(int v,int u){
	if(v == 1 || u == 1)
		return 1;
    if(d[v] < d[u])
        swap(v,u);
    for(int i = MAXLOG - 1;i >= 0;i --)
        if(par[v][i] + 1 and d[par[v][i]] >= d[u])
            v = par[v][i];
    if(v == u)
        return v;
    for(int i = MAXLOG - 1;i >= 0;i --)
        if(par[v][i] - par[u][i])
            v = par[v][i], u = par[u][i];
    return par[v][0];
}
int BL[maxm];
struct node
{
	int l , r , id , lc;
	bool operator<( const node& rhs) const
	{
		return (BL[l] == BL[rhs.l]) ? ( r < rhs.r ) : ( BL[l] < BL[rhs.l] );  
	}
}q[maxm];
int BLOCK;
int ans[maxm];
int res ;
int vis[maxn] , cnt[maxn];
inline void update(int x)
{
	if( vis[x] )
		if(--cnt[wt[x]] == 0)
			res--;
	if( !vis[x] )
		if(cnt[wt[x]]++ == 0)
			res++;
	vis[x] ^= 1;
}
int main()
{
	int n, m; 
	scanf("%d%d",&n,&m);
	int b[maxn];
	ll mxx = -1;
	for(int i = 1; i <= n; i++)
	{
		cin >> wt[i];
		b[i] = wt[i];
		mxx = max((ll)wt[i],mxx);
	}

	if(mxx >=  maxn)
	{
		sort(b + 1, b + n + 1);
		for (int i = 1; i <= n; ++i)
			wt[i] = lower_bound(b + 1, b + n + 1, wt[i]) - b; 
	}
	for(int i = 1; i <= n-1; i++)
	{
		int u ,v; 
		scanf("%d%d",&u,&v);
		G[u].pb(v);
		G[v].pb(u);
	}
	dfs(1);
	for(int i = 1; i <= m; i++)
	{
		int u , v; 
		scanf("%d%d",&u,&v);

		q[i].lc = lca(u,v);
		// 2case
		if(st[u] > st[v]) swap(u,v);
		if(q[i].lc == u)
		{
			q[i].l = st[u];
			q[i].r = st[v];
		}
		else
		{
			q[i].l = en[u];
			q[i].r = st[v];
		}
		q[i].id = i;
	}
	BLOCK = sqrt(timer);
	for(int i = 1; i <= timer; i++)
	{
		BL[i] = (i-1)/BLOCK+1;  
	}
	sort(q+1,q+m+1);

	int curL = 1;
	int curR = 0;
	for(int i = 1; i <= m; i++)
	{
		while(curL < q[i].l) update(ID[curL++]);
		while(curL > q[i].l) update(ID[--curL]);
		while(curR < q[i].r) update(ID[++curR]);
		while(curR > q[i].r) update(ID[curR--]);
		int u = ID[curL];
		int v = ID[curR];
		// case2 check
		if(q[i].lc != u and q[i].lc != v)  update(q[i].lc);
		ans[q[i].id] = res;
		if(q[i].lc != u and q[i].lc != v)  update(q[i].lc);
	}

	for(int i = 1; i <= m; i++)
	{
		printf("%d\n",ans[i]);
	}

	return 0;
}

