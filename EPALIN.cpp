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
	string s; 
	while(getline(cin,s))
	{
		int len = s.length();
		
		string rev_s = s;
		reverse(rev_s.begin(),rev_s.end());
		string modif_s = rev_s + "$" + s;
		int modif_len = modif_s.length();

		vector<int> z = calculateZ(modif_s);

		int max_palin_len = -1;
		for(int i = 0; i < z.size(); i++)
		{
			if(z[i] && z[i] ==  modif_len-i)
			{
				max_palin_len = modif_len - i;
				break;
			}
		}
		
		if(max_palin_len == s.length())
			cout << s << "\n";
		else
		{
			if(max_palin_len == 1)
			{
				string tans = s.substr(0,s.length()-1);
				reverse(tans.begin(),tans.end());
				string ans = s + tans;
				cout << ans << "\n";
				continue;
			}
			string tans = s.substr(0,len-max_palin_len);
			reverse(tans.begin(),tans.end());
			string ans = s + tans;
			cout << ans << "\n";
		}
	}
	return 0;
}
