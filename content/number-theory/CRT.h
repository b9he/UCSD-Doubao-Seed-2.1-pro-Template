/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: Chinese Remainder Theorem.
 *
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$.
 * Assumes $mn < 2^{62}$.
 * Usage:
 * ll a=2, m=6, b=8, n=9;
 * if((a-b)%gcd(m, n))cout<<-1;
 * else cout<<crt(a, m, b, n)<<' '<<lcm(m, n); // 8 18
 * Time: $\log(n)$
 * Status: Works
 */
#pragma once

#include "euclid.h"

ll crt(ll a, ll m, ll b, ll n) {
	if (n>m) swap(a, b), swap(m, n);
	ll x, y, g=euclid(m, n, x, y);
	assert((a-b)%g==0); // else no solution
	x=(b-a)%n*x%n/g*m+a;
	return x<0?x+m*n/g:x;
}
