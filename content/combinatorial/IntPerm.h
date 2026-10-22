/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * Description: Permutation -> integer conversion. (Not order preserving.)
 * Integer -> permutation can use a lookup table.
 * Usage:
 * vi p={0, 1, 2};int code=permToInt(p);
 * cout<<code; // 0; p is unchanged
 * Time: O(n)
 */
#pragma once

int permToInt(vi&v) {
	int use=0, i=0, r=0;
	for(int x:v) r=r*++i+__builtin_popcount(use&-(1<<x)),
		use|=1<<x;                     // (note: minus, not ~!)
	return r;
}
