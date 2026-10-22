/**
 * Author: Mattias de Zalenski
 * Date: 2002-11-04
 * Description: Magic formula for the volume of a polyhedron. Faces should point outwards.
 * Usage:
 * using P=Point3D<double>;struct Face{int a, b, c;};
 * vec<P>p={P(0, 0, 0), P(1, 0, 0), P(0, 1, 0), P(0, 0, 1)};
 * vec<Face>f={{0, 2, 1}, {0, 1, 3}, {0, 3, 2}, {1, 2, 3}};
 * cout<<signedPolyVolume(p, f); // 1/6
 * Status: tested
 */
#pragma once

template<class V, class L>
double signedPolyVolume(const V&p, const L&trilist) {
	double v=0;
	for (auto i:trilist) v+=p[i.a].cross(p[i.b]).dot(p[i.c]);
	return v/6;
}
