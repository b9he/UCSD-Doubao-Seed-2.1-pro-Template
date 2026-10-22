/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-05-05
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
If a unique intersection point of the lines going through s1,e1 and s2,e2 exists \{1, point\} is returned.
If no intersection point exists \{0, (0,0)\} is returned and if infinitely many exists \{-1, (0,0)\} is returned.
The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
Products of three coordinates are used in intermediate steps so watch out for overflow if using int or ll.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\end{minipage}
 * Usage:
 * using P=Point<double>;
 * auto [status, p]=lineInter(P(0, 0), P(2, 2), P(0, 2), P(2, 0));
 * if(status==1)cout<<p; // (1,1)
 * Status: stress-tested, and tested through half-plane tests
 */
#pragma once

#include "Point.h"

template<class P>
pair<int, P>lineInter(P s1, P e1, P s2, P e2) {
	auto d=(e1-s1).cross(e2-s2);
	if (d==0) // if parallel
		return {-(s1.cross(e1, s2)==0), P(0, 0)};
	auto p=s2.cross(e1, e2), q=s2.cross(e2, s1);
	return {1, (s1*p+e1*q)/d};
}
