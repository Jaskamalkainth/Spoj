#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;




// Z-Algorithm for Pattern Matching
// O(n+m)
inline vector<int> calculateZ(string inp)
{
	int len = inp.length();
	vector<int> Z(len);
	int left = 0;
	int right = 0;
	for(int k = 1; k < len; k++)
	{
		if(k > right)
		{
			left = right = k;
			while(right < len && inp[right] == inp[right-left])
			{
				right++;  
			}
			Z[k] = right - left;
			right--;
		}
		else
		{
			int k1 = k - left;
			// inside the Z-Box
			if(Z[k1] < right-k+1)
			{
				Z[k] = Z[k1];  
				//if the value is inside the Z-box then copy it
			}
			else
			{
				// otherwise do more comparisons
				left = k;
				while(right < len && inp[right] == inp[right-left])
				{
					right++;  
				}
				Z[k] = right-left;
				right--;
			}
		}
	}
	return Z;
	// Z[i] denotes the length of the longest substring starting from i which is also the prefix of the string.
}

int main()
{
	int t; 
	scanf("%d",&t);
	while(t--)
	{
		string s; cin >> s;
		reverse(s.begin(),s.end());
		vector<int> Z = calculateZ(s);
		Z[0] = s.length();
		reverse(Z.begin(),Z.end());
		int q; 
		scanf("%d",&q);
		while(q--)
		{
			int id;
			scanf("%d",&id);
			printf("%d\n",Z[id-1]);
		}
	}
	

	return 0;
}
