/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-27
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
If a unique intersection point between the line segments going from s1 to e1 and from s2 to e2 exists then it is returned.
If no intersection point exists an empty vector is returned.
If infinitely many exist a vector with 2 elements is returned, containing the endpoints of the common line segment.
The wrong position will be returned if P is Point<ll> and the intersection point does not have integer coordinates.
Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentIntersection}
\end{minipage}
 * Usage:
 * using P=Point<double>;
 * auto pts=segInter(P(0, 0), P(2, 2), P(0, 2), P(2, 0));
 * if(!pts.empty())cout<<pts[0]; // (1,1)
 * Status: stress-tested, tested on kattis:intersection
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"

template<class P>vector<P>segInter(P a, P b, P c, P d) {
	auto oa=c.cross(d, a), ob=c.cross(d, b),
	     oc=a.cross(b, c), od=a.cross(b, d);
	// Checks if intersection is single non-endpoint point.
	if (sgn(oa)*sgn(ob)<0&&sgn(oc)*sgn(od)<0)
		return {(a*ob-b*oa)/(ob-oa)};
	set<P>s;
	if (onSegment(c, d, a)) s.insert(a);
	if (onSegment(c, d, b)) s.insert(b);
	if (onSegment(a, b, c)) s.insert(c);
	if (onSegment(a, b, d)) s.insert(d);
	return {all(s)};
}
