/**
 * Author: Chengxi Meng
 * Source: Personal VS Code snippets
 * Description: Intersects the left half-planes of directed lines using the original snippet.
 * Uses its own Point/Vector helpers inside namespace SnippetHPI.
 * Assumes a nonempty, well-conditioned system forming a bounded nondegenerate polygon;
 * empty, unbounded and degenerate classification is not provided. Mutates line order.
 * Usage:
 * using namespace SnippetHPI;
 * vec<HLine>h={{Point(0, 0), Point(1, 0)},
 *  {Point(1, 0), Point(1, 1)}, {Point(1, 1), Point(0, 1)},
 *  {Point(0, 1), Point(0, 0)}};
 * auto polygon=halfPlaneIntersection(h);
 * cout<<polygon.size(); // 4
 * Time: O(N\log N) time, O(N) space.
 * Status: Layout preview; original implementation retained
 */
#pragma once
namespace SnippetHPI { const double eps=1e-8;
int sgn(double x) { if (fabs(x)<eps) return 0;
	if (x<0) return-1; return 1; } struct Point { double x, y;
	Point(double _x=0, double _y=0):x(_x), y(_y) {}
	Point operator+(const Point&b) const { return Point(x+b.x, y+b.y); }
	Point operator-(const Point&b) const { return Point(x-b.x, y-b.y); }
	Point operator*(const double&k) const { return Point(x*k, y*k); }
	Point operator/(const double&k) const { return Point(x/k, y/k); }
	bool operator==(const Point&b) const {
		return sgn(x-b.x)==0&&sgn(y-b.y)==0; } };
typedef Point Vector; double dot(Vector a, Vector b) {
	return a.x*b.x+a.y*b.y; }
double cross(Vector a, Vector b) {
	return a.x*b.y-a.y*b.x; } double length(Vector a) {
	return sqrt(dot(a, a)); } double dist(Point a, Point b) {
	return length(a-b); } bool isUp(Vector a) {
	return sgn(a.y)>0||(sgn(a.y)==0&&sgn(a.x)>=0); }
bool polarCmp(Point a, Point b) {
	bool upA=isUp(a), upB=isUp(b);
	if (upA!=upB) return upA>upB;
	return sgn(cross(a, b))>0; } struct HLine { Point s, e;
	double angle; HLine() {}
	HLine(Point _s, Point _e):s(_s), e(_e) {
		angle=atan2(e.y-s.y, e.x-s.x); } };
bool isPointOnRight(Point p, HLine L) {
	return sgn(cross(L.e-L.s, p-L.s))<0; }
bool cmpHLine(const HLine&a, const HLine&b) {
	int d=sgn(a.angle-b.angle); if (d!=0) return d<0;
	return sgn(cross(a.e-a.s, b.e-a.s))>0; }
Point getIntersect(HLine l1, HLine l2) {
	Vector u=l1.s-l2.s, v=l1.e-l1.s, w=l2.e-l2.s;
	double t=cross(w, u)/cross(v, w); return l1.s+v*t; }
vec<Point>halfPlaneIntersection(vec<HLine>&lines) {
	int n=lines.size();
	sort(lines.begin(), lines.end(), cmpHLine); int m=1;
	for (int i=1; i<n; i++) {
		if (sgn(lines[i].angle-lines[i-1].angle)!=0) {
			lines[m++]=lines[i]; } } n=m; deque<HLine>q;
	deque<Point>pts; q.push_back(lines[0]);
	for (int i=1; i<n; i++) {
		while (pts.size()>0&&isPointOnRight(pts.back(), lines[i])) {
			q.pop_back(); pts.pop_back(); }
		while (pts.size()>0&&isPointOnRight(pts.front(), lines[i])) {
			q.pop_front(); pts.pop_front(); }
		if (sgn(cross(q.back().e-q.back().s, lines[i].e-lines[i].s))==0) continue;
		pts.push_back(getIntersect(q.back(), lines[i]));
		q.push_back(lines[i]); }
	while (pts.size()>0&&isPointOnRight(pts.back(), q.front())) {
		q.pop_back(); pts.pop_back(); }
	while (pts.size()>0&&isPointOnRight(pts.front(), q.back())) {
		q.pop_front(); pts.pop_front(); } if (q.size()>1) {
		pts.push_back(getIntersect(q.back(), q.front())); }
	return vec<Point>(pts.begin(), pts.end()); } }
