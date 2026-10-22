/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-10-29
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Projects point p onto line ab. Set refl=true to get reflection
 * of point p across line ab instead. The wrong point will be returned if P is
 * an integer point and the desired point doesn't have integer coordinates.
 * Products of three coordinates are used in intermediate steps so watch out
 * for overflow.
 * Usage:
 * using P=Point<double>;P a(0, 0), b(2, 0), p(1, 3);
 * cout<<lineProj(a, b, p); // (1,0)
 * cout<<lineProj(a, b, p, true); // (1,-3)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

template<class P>
P lineProj(P a, P b, P p, bool refl=false) {
	P v=b-a;
	return p-v.perp()*(1+refl)*v.cross(p-a)/v.dist2();
}
