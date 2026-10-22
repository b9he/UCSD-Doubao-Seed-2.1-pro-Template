/**
 * Author: Chengxi Meng
 * Source: First Draft Template, pages 7-9
 * Description: perpen returns two points on the perpendicular bisector of distinct a,b.
 * incircle returns center/radius of a nondegenerate triangle.
 * circularSegmentArea uses radius r and central angle theta in [0,2*pi].
 * Usage:
 * auto [a, b]=perpen(P(0, 0), P(2, 0));cout<<a; // (1,0)
 * auto [c, r]=incircle(P(0, 0), P(4, 0), P(0, 3));
 * cout<<c<<' '<<r; // (1,1) 1
 * cout<<circularSegmentArea(2, acos(-1.0)); // 2*pi
 * Time: O(1).
 */
#pragma once
#include "Point.h"
using P=Point<double>;
pair<P, P>perpen(P a, P b) {
 P M=(a+b)/2, c=b-M, d(-c.y, c.x);return {M, M+d};
}
pair<P, double>incircle(P A, P B, P C) {
 double a=(B-C).dist(), b=(A-C).dist(), c=(A-B).dist();
 P center=(A*a+B*b+C*c)/(a+b+c);
 double r=abs((B-A).cross(C-A))/(a+b+c);
 return {center, r};
}
double circularSegmentArea(double r, double theta) {
 return 0.5*r*r*(theta-sin(theta));
}
