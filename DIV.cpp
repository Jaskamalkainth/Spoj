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
#define mp                 make_pair
#define pb                 push_back
#define ss                 second
#define ff                 first


const int maxN = 1e6+7;
int  pp[maxN+1];
ll cnt[maxN+1]; // cnt[r] - cnt[l-1]  number of primes in [l,r]
vector <int> prime,sp;
inline void pre_sieve()
{
    sp.resize(maxN);
    for(ll i = 2; i < maxN; i++ )
        if( pp[i] == 0 )
        {
            sp[i] = i;
            for(ll j = i*i; j < maxN; j += i)
                if ( pp[j] == 0 )
                {
                    sp[j] = i;
                    pp[j] = 1;
                }
        }
    for(int i =2; i< maxN; i++)
        if(pp[i] == 0)
            prime.push_back(i);

    for(int i = 2; i < maxN; i++)
        cnt[i] = cnt[i-1] + !(pp[i]);
   }
int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
	vi  ans;
	pre_sieve();
	for(int i = 2; i < maxN; i++)
	{
		if(!pp[i]) continue;
		int num = i;
		ll fnum = 1ll;
		map<int,int> mm;
		while(num > 1)
		{
			mm[sp[num]]++;
			num /= sp[num];
		}
		for(auto ii: mm)
			fnum *= (ii.ss+1);

		if(!pp[fnum])
			continue;
		int step = 0;
		int p, q;
		while(fnum > 1)
		{
			step++;
			if(step == 1)
				p = sp[fnum];
			else if(step == 2)
				q = sp[fnum];
		
			fnum /= sp[fnum];
			if(step == 2)
				break;
		}
		if(fnum == 1 && p != q)
		{
			ans.pb(i);  
		}
	}
	for(int i = 8; i < ans.size(); i += 9)
		cout << ans[i] << "\n";
    return 0;
}

