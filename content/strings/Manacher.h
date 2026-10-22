/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * Description: For each position in a string, computes p[0][i] = half length of
 *  longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
 * Usage:
 * string s="abba";auto p=manacher(s);int start=0, len=0;
 * rep(z, 0, 2)rep(i, 0, sz(p[z])) {
 *  int k=2*p[z][i]+z;
 *  if(k>len)len=k, start=i-p[z][i];
 * }
 * cout<<s.substr(start, len); // abba
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

array<vi, 2>manacher(const string&s) {
	int n=sz(s);
	array<vi, 2>p={vi(n+1), vi(n)};
	rep(z, 0, 2) for (int i=0, l=0, r=0; i<n; i++) {
		int t=r-i+!z;
		if (i<r) p[z][i]=min(t, p[z][l+t]);
		int L=i-p[z][i], R=i+p[z][i]-!z;
		while (L>=1&&R+1<n&&s[L-1]==s[R+1])
			p[z][i]++, L--, R++;
		if (R>r) l=L, r=R;
	}
	return p;
}
