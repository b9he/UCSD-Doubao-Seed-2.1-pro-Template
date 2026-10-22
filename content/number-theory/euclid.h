/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 * Usage:
 * ll a=6, b=9, c=3, x, y;ll g=euclid(a, b, x, y);
 * if(c%g)cout<<-1;
 * else { // ax+by=c; here a,b>0
 *  ll step=b/g;
 *  x=(__int128)x*(c/g)%step;x=(x+step)%step;
 *  if(!x)x+=step;
 *  y=(c-(__int128)a*x)/b;
 *  cout<<x<<' '<<y; // 2 -1; smallest positive x
 * }
 */
#pragma once

ll euclid(ll a, ll b, ll&x, ll&y) {
	if (!b) return x=1, y=0, a;
	ll d=euclid(b, a%b, y, x);
	return y-=a/b*x, d;
}
