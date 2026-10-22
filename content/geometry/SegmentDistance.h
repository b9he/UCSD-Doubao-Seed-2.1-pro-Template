/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
Returns the shortest distance between point p and the line segment from point s to e.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Usage:
 * cout<<segDist(P(0, 0), P(2, 0), P(3, 1)); // sqrt(2)
 * Status: tested
 */
#pragma once

#include "Point.h"

typedef Point<double>P;
double segDist(P s, P e, P p) {
	if (s==e) return (p-s).dist();
	auto d=(e-s).dist2(), t=min(d, max(.0, (p-s).dot(e-s)));
	return ((p-s)*d-(e-s)*t).dist()/d;
}
