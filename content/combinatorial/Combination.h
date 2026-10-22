/**
 * Author: Chengxi Meng
 * Source: Personal VS Code snippets
 * Description: Precomputes factorials and inverse factorials for binomial coefficients
 * modulo prime MOD. Requires 0 <= n < MAXN <= MOD. Invalid m returns 0.
 * Usage:
 * init_comb();cout<<C(5, 2); // 10
 * cout<<fac[5]; // 120
 * Time: O(MAXN+\log MOD) preprocessing, O(1) query, O(MAXN) space.
 * Status: Layout preview; original implementation retained
 */
#pragma once
const int MOD=1000000007; const int MAXN=1000005;
ll fac[MAXN]; ll invFac[MAXN]; ll qpow(ll base, ll exp) {
	ll res=1; base%=MOD; while (exp>0) {
		if (exp&1) res=res*base%MOD;
		base=base*base%MOD; exp>>=1; } return res; }
void init_comb() { fac[0]=1; invFac[0]=1;
	for (int i=1; i<MAXN; i++) {
		fac[i]=fac[i-1]*i%MOD; }
	invFac[MAXN-1]=qpow(fac[MAXN-1], MOD-2);
	for (int i=MAXN-2; i>=1; i--) {
		invFac[i]=invFac[i+1]*(i+1)%MOD; } }
ll C(ll n, ll m) { if (m>n||m<0) return 0;
	if (m==0||m==n) return 1;
	return fac[n]*invFac[m]%MOD*invFac[n-m]%MOD; }
