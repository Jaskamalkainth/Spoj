#include<iostream>
#include<vector>
#include<string>
#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
	string s; cin >> s;
	int len  = s.length();
	int count = 0;
	int j , k;
	for(int i = 0 ; i < len; i++)
	{
		// count odd len palindrome
		j = i-1;
		k = i+1;
		while(j >= 0 && k < len && s[j] == s[k])
			j--,k++,count++;
		//count even len palindrome
		j = i;
		k = i+1;
		while(j >= 0 && k < len && s[j] == s[k])
			j--,k++,count++;
	}
	cout << count + s.length()<< "\n";
	return 0;
}
