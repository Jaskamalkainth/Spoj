#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;


/*
 * Suffix Array O(n * logn )
 */
const int MAXN = 3e3;
int cnt[256], cls[2][MAXN], sa[2][MAXN], st[MAXN], rnk[MAXN];
//sa[1][0] sa[1][1] ..... sa[1][n] where n=str.length() 
//sa[1][i] i=0->n gives the Suffix Array
//For LCP Array lcp[i] i=0-->n

int suff_arr[MAXN];
int suff_len[MAXN];
int lcp[MAXN];

void init()
{
	for(int i = 0 ; i < MAXN; i++)
	{
		if( i < 256 ) cnt[i] = 0;
		st[i] = rnk[i] = suff_len[i] = suff_len[i] = 0;
	}
	for(int i = 0 ; i < MAXN; i++)
		for(int  j = 0; j < 2 ; j++)
		{
			cls[j][i] = sa[j][i] = 0;
		}

}
void suffixArray(string s) 
{
	int i, j;
	fill(cnt,cnt+sizeof(cnt),0);
	int n = s.size();
    for (i = 0; i < n; i++) { cnt[s[i]] ++; cls[0][i] = s[i];}
    for (i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
    for (i = 0; i < n; i++) sa[0][--cnt[cls[0][i]]] = i;
    int cur = 0;
    for (i = 0; (1 << i) < n; i++) {
        int clen = (1 << i);
        for (j = 0; j < n; j++) {
            if (j > 0 && sa[cur][j - 1] + clen < n && cls[cur][sa[cur][j]] == cls[cur][sa[cur][j - 1]] &&
                    cls[cur][sa[cur][j] + clen / 2] == cls[cur][sa[cur][j - 1] + clen / 2]
               )
                cls[1 - cur][sa[cur][j]] = cls[1 - cur][sa[cur][j - 1]];
            else cls[1 - cur][sa[cur][j]] = j;
        }
        for (j = 0; j < n; j++) { st[j] = j; sa[1 - cur][j] = sa[cur][j]; }
        for (j = 0; j < n; j++) {
            int cele = sa[cur][j] - clen;
            if (cele >= 0) sa[1 - cur][st[cls[1 - cur][cele]]++] = cele;
        }
        cur = 1 - cur;
    }
    for (i = 0; i < n; i++) { sa[0][i] = sa[cur][i]; rnk[sa[cur][i]] = i;}
    int x = 0;
    for (i = 0; i < n; i++) {
        if (rnk[i] < n - 1) {
            for (j = sa[cur][rnk[i] + 1]; max(i, j) + x < n && s[i + x] == s[j + x]; x++);
            lcp[rnk[i] + 1] = x; if (x > 0) x--;
        }
    }

	for(int i = 0 ; i < n; i++)
	{
		suff_arr[i] = sa[1][i];   
		suff_len[i] = ( n - sa[1][i]);
	}
}


int main()
{
	int t; cin >> t;
	while(t--)
	{
		init();
		string s; cin >> s;
		suffixArray(s);
		long long ans = suff_len[0];
		for(int i = 1; i < s.length(); i++)
		{
			ans += (suff_len[i]-lcp[i]); 
		}
		cout << ans << "\n";
	}
	return 0;
}
