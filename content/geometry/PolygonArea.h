/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns twice the signed area of a polygon.
 *  Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
 * Usage:
 * using P=Point<ll>;
 * vec<P>p={P(0, 0), P(2, 0), P(0, 2)};
 * cout<<polygonArea2(p); // 4; area is 2
 * Status: Stress-tested and tested on kattis:polygonarea
 */
#pragma once

#include "Point.h"

template<class T>
T polygonArea2(vector<Point<T>>&v) {
	T a=v.back().cross(v[0]);
	rep(i, 0, sz(v)-1) a+=v[i].cross(v[i+1]);
	return a;
}
