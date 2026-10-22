/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Basic operations on square matrices.
 * Usage:
 * Matrix<ll, 2>A;
 * A.d={{{1, 1}, {1, 0}}};array<ll, 2>x={1, 0};
 * auto y=(A^5)*x;
 * cout<<y[0]<<' '<<y[1]; // 8 5
 * Status: tested
 */
#pragma once

template<class T, int N>struct Matrix {
	typedef Matrix M;
	array<array<T, N>, N>d{};
	M operator*(const M&m) const {
		M a;
		rep(i, 0, N) rep(j, 0, N)
			rep(k, 0, N) a.d[i][k]+=d[i][j]*m.d[j][k];
		return a;
	}
	array<T, N>operator*(const array<T, N>&vec) const {
		array<T, N>ret{};
		rep(i, 0, N) rep(j, 0, N) ret[i]+=d[i][j]*vec[j];
		return ret;
	}
	M operator^(ll p) const {
		assert(p>=0);
		M a, b(*this);
		rep(i, 0, N) a.d[i][i]=1;
		while (p) {
			if (p&1) a=a*b;
			b=b*b;
			p>>=1;
		}
		return a;
	}
};
