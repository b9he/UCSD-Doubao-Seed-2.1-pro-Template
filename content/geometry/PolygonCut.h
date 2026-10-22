/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/PolygonCut}
\vspace{-6mm}
\end{minipage}
 * Usage:
 * vec<P>p={P(0, 0), P(2, 0), P(2, 2), P(0, 2)};
 * auto kept=polygonCut(p, P(1, -1), P(1, 3));
 * cout<<kept.size(); // 4, right half of the square
 * Status: tested but not extensively
 */
#pragma once

#include "Point.h"

typedef Point<double>P;
vector<P>polygonCut(const vector<P>&poly, P s, P e) {
	vector<P>res;
	rep(i, 0, sz(poly)) {
		P cur=poly[i], prev=i?poly[i-1]:poly.back();
		auto a=s.cross(e, cur), b=s.cross(e, prev);
		if ((a<0)!=(b<0))
			res.push_back(cur+(prev-cur)*(a/(a-b)));
		if (a<0)
			res.push_back(cur);
	}
	return res;
}
