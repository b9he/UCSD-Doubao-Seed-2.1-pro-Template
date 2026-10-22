/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true if p lies within the polygon. If strict is true,
 * it returns false for points on the boundary. The algorithm uses
 * products in intermediate steps so watch out for overflow.
 * Usage:
 * vec<P>p={P(0, 0), P(2, 0), P(2, 2), P(0, 2)};
 * cout<<inPolygon(p, P(1, 1)); // 1
 * cout<<inPolygon(p, P(0, 1), false); // 1
 * Time: O(n)
 * Status: stress-tested and tested on kattis:pointinpolygon
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"
#include "SegmentDistance.h"

template<class P>
bool inPolygon(vector<P>&p, P a, bool strict=true) {
	int cnt=0, n=sz(p);
	rep(i, 0, n) {
		P q=p[(i+1)%n];
		if (onSegment(p[i], q, a)) return!strict;
		//or: if (segDist(p[i], q, a) <= eps) return !strict;
		cnt^=((a.y<p[i].y)-(a.y<q.y))*a.cross(p[i], q)>0;
	}
	return cnt;
}
