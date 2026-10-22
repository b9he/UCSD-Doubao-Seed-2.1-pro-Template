/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true iff p lies on the line segment from s to e.
 * Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using Point<double>.
 * Usage:
 * using P=Point<ll>;
 * cout<<onSegment(P(0, 0), P(2, 0), P(1, 0)); // 1
 * Status:
 */
#pragma once

#include "Point.h"

template<class P>bool onSegment(P s, P e, P p) {
	return p.cross(s, e)==0&&(s-p).dot(e-p)<=0;
}
