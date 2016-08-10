#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<algorithm>
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
	while(1)
	{
		string s; cin >> s;
		int len = s.length();

		if(s[0] == '*')
			return 0;
		
		vector<int> z = calculateZ(s);


		int sc = 0;
		for(int i = 0;i < z.size(); i++)
			if(z[i])
				if(z[i] == len - i && len%(len-i) == 0)
					sc = len-i;

		if(sc == 0)
		{
			cout <<  1 << "\n";
			continue;
		}

		string t = s.substr(0,sc);
		int ok = 1;
		int k = 0;
		for(int i = 0;i < len; i++)
		{
			if(s[i] != t[k++])
				ok = 0;
			if(k == sc)
				k =0;
		}
		if(ok)
			cout << len/sc << "\n";
		else
			cout <<  1 << "\n";
	}
	return 0;
}
