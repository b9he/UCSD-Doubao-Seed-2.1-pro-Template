/**
 * Author: Chengxi Meng
 * Source: Personal VS Code snippets
 * Description: Euler linear sieve for primes, smallest prime factors and factorization
 * within [1,n]. Optional phi, mu and divisor-count modules remain
 * commented out; enable their declarations, initialization and recurrences together.
 * All products p*i must fit int.
 * Usage:
 * MathSieve sieve(1000);cout<<(sieve.spf[97]==97); // 1
 * for(auto [p, e]:sieve.factorize(120))
 *  cout<<p<<'^'<<e<<' '; // 2^3 3^1 5^1
 * Time: O(N) build and space; O(\log x) factorization.
 * Status: Layout preview; original implementation retained
 */
#pragma once
struct MathSieve { int n; std::vec<int>primes, spf;
// std::vec<ll>phi;
// std::vec<int>mu;
// std::vec<int>d, cnt;
	MathSieve(int _n):n(_n), spf(_n+1) /*, phi(_n + 1), mu(_n + 1), d(_n + 1), cnt(_n + 1)*/ {
// [Phi] if (_n>=1) phi[1]=1;
// [Mu] if (_n>=1) mu[1]=1;
// [Divisor count] if (_n>=1) { d[1]=1; cnt[1]=0; }
		for (int i=2; i<=n;++i) spf[i]=i;
		for (int i=2; i<=n;++i) { if (spf[i]==i) {
				primes.push_back(i);
// [Phi] phi[i]=i-1;
// [Mu] mu[i]=-1;
// [Divisor count] d[i]=2; cnt[i]=1;
			} for (int p:primes) { if (p*i>n) break;
				spf[p*i]=p; if (i%p==0) {
// [Phi] phi[p*i]=phi[i]*p;
// [Mu] mu[p*i]=0;
// [Divisor count] d[p * i] = d[i] / (cnt[i] + 1) * (cnt[i] +
// 2); cnt[p * i] = cnt[i] + 1;
					break; } else {
// [Phi] phi[p*i]=phi[i]*phi[p];
// [Mu] mu[p*i]=-mu[i];
// [Divisor count] d[p*i]=d[i]*d[p]; cnt[p*i]=1;
				} } } }
	std::vec<std::pair<int, int>>factorize(int x) {
		std::vec<std::pair<int, int>>factors; while (x>1) {
			int p=spf[x]; int count=0; while (x%p==0) {
				count++; x/=p; } factors.push_back({p, count}); }
		return factors; } };
