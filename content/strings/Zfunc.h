/**
 * Author: chilli
 * License: CC0
 * Description: \texttt{z[i]} is the LCP of \texttt{s[i:]} and \texttt{s}, except \texttt{z[0]=0}.
 * For extended KMP, run Z on pattern + separator + text; choose a separator absent from both.
 * Then \texttt{z[pattern.size()+1+i]} is the LCP of the pattern and the text suffix at $i$.
 * Usage:
 * string pat="aba", s="ababa";auto z=Z(pat+'#'+s);
 * rep(i, 0, sz(s))cout<<z[sz(pat)+1+i]<<' '; // 3 0 3 0 1
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vi Z(const string&S) {
	vi z(sz(S));
	int l=-1, r=-1;
	rep(i, 1, sz(S)) {
		z[i]=i>=r?0:min(r-i, z[i-l]);
		while (i+z[i]<sz(S)&&S[i+z[i]]==S[z[i]])
			z[i]++;
		if (i+z[i]>r)
			l=i, r=i+z[i];
	}
	return z;
}
