/**
 * Author: Simon Lindholm
 * Date: 2016-09-06
 * License: CC0
 * Source: me
 * Description: To get all uniquely determined values of $x$ back from SolveLinear, make the following changes:
 * Define \texttt{undefined} as \texttt{numeric\_limits<double>::quiet\_NaN()} or another chosen sentinel.
 * Usage:
 * vec<vd>A={{1, 0}};vd b={2}, x(2);
 * int rank=solveLinear(A, b, x);
 * cout<<x[0]; // 2; x[1] is undefined, rank=1
 * Status: tested on kattis:equationsolverplus, stress-tested
 */
#pragma once

#include "SolveLinear.h"

rep(j, 0, n) if (j!=i) // instead of rep(j,i+1,n)
// ... then at the end:
x.assign(m, undefined);
rep(i, 0, rank) {
	rep(j, rank, m) if (fabs(A[i][j])>eps) goto fail;
	x[col[i]]=b[i]/A[i][i];
fail:; }
