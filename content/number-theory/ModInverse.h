/**
 * Author: Simon Lindholm
 * Date: 2016-07-24
 * License: CC0
 * Source: Russian page
 * Description: Pre-computation of modular inverses. Assumes LIM $\le$ mod and that mod is a prime.
 * Paste the precomputation inside a function after defining \texttt{mod} and \texttt{LIM}.
 * Usage:
 * const ll mod=7, LIM=7;
 * // Paste fragment here.
 * cout<<inv[3]; // 5, because 3*5=1 mod 7
 * Status: Works
 */
#pragma once

// const ll mod=1000000007, LIM=200000; ///include-line
ll*inv=new ll[LIM]-1; inv[1]=1;
rep(i, 2, LIM) inv[i]=mod-(mod/i)*inv[mod%i]%mod;
