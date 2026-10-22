/**
 * Author: chilli
 * Date: 2019-05-17
 * License: CC0
 * Source: https://github.com/ngthanhtrung23/ACM_Notebook_new
 * Description: Determine whether a point t lies inside a convex hull (CCW
 * order, with no collinear points). Returns true if point lies within
 * the hull. If strict is true, points on the boundary aren't included.
 * Usage:
 * vec<P>h={P(0, 0), P(2, 0), P(2, 2), P(0, 2)};
 * cout<<inHull(h, P(1, 1)); // 1
 * cout<<inHull(h, P(0, 1), false); // 1
 * Status: stress-tested
 * Time: O(\log N)
 */
#pragma once

#include "Point.h"
#include "sideOf.h"
#include "OnSegment.h"

typedef Point<ll>P;

bool inHull(const vector<P>&l, P p, bool strict=true) {
	int a=1, b=sz(l)-1, r=!strict;
	if (sz(l)<3) return r&&onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b])>0) swap(a, b);
	if (sideOf(l[0], l[a], p)>=r||sideOf(l[0], l[b], p)<=-r)
		return false;
	while (abs(a-b)>1) {
		int c=(a+b)/2;
		(sideOf(l[0], l[c], p)>0?b:a)=c;
	}
	return sgn(l[a].cross(l[b], p))<r;
}
