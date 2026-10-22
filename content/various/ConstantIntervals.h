/**
 * Author: Simon Lindholm
 * Date: 2015-03-20
 * License: CC0
 * Source: me
 * Description: Split a monotone function on [from, to) into a minimal set of half-open intervals on which it has the same value.
 *  Runs a callback g for each such interval.
 * Usage:
 * vec<tuple<int, int, int>>runs;
 * constantIntervals(0, 6, [](int i){return i/2;},
 *  [&](int l, int r, int v){runs.emplace_back(l, r, v);});
 * for(auto [l, r, v]:runs)cout<<l<<','<<r<<':'<<v<<' ';
 * // 0,2:0 2,4:1 4,6:2
 * Time: O(k\log\frac{n}{k})
 * Status: tested
 */
#pragma once

template<class F, class G, class T>
void rec(int from, int to, F&f, G&g, int&i, T&p, T q) {
	if (p==q) return;
	if (from==to) {
		g(i, to, p);
		i=to; p=q;
	} else {
		int mid=(from+to)>>1;
		rec(from, mid, f, g, i, p, f(mid));
		rec(mid+1, to, f, g, i, p, q);
	}
}
template<class F, class G>
void constantIntervals(int from, int to, F f, G g) {
	if (to<=from) return;
	int i=from; auto p=f(i), q=f(to-1);
	rec(from, to-1, f, g, i, p, q);
	g(i, to, q);
}
