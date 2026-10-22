/**
 * Author: Chengxi Meng
 * Source: Personal VS Code snippets
 * Description: 30-bit linear-basis fragment: reads n nonnegative integers from cin
 * and prints their maximum subset XOR. Paste inside a function after declaring n.
 * Usage:
 * int n=3; // cin: 1 2 3
 * // Paste fragment here.
 * // output: 3
 * Time: O(30N) time, O(30) space.
 * Status: Layout preview; original implementation retained
 */
#pragma once
vec<ll>basis(30, 0); for (int i=0; i<n; i++) { ll x;
	cin>>x; for (int j=29; j>=0; j--) { if ((x>>j)&1) {
			if (!basis[j]) { basis[j]=x; break; } x^=basis[j]; }
	} } ll max_xor=0; for (int j=29; j>=0; j--) {
	if ((max_xor^basis[j])>max_xor) { max_xor^=basis[j]; }
} cout<<max_xor<<"\\n";
