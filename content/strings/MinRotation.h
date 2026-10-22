/**
 * Author: Stjepan Glavina
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/min_rotation.cpp
 * Description: Finds the lexicographically smallest rotation of a string.
 * Usage:
 * string s="baca";int k=minRotation(s);
 * rotate(s.begin(), s.begin()+k, s.end());
 * cout<<s; // abac
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

int minRotation(string s) {
	int a=0, N=sz(s); s+=s;
	rep(b, 0, N) rep(k, 0, N) {
		if (a+k==b||s[a+k]<s[b+k]) {b+=max(0, k-1); break;}
		if (s[a+k]>s[b+k]) { a=b; break; }
	}
	return a;
}
