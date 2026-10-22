/**
 * Author: Simon Lindholm
 * Date: 2016-03-22
 * License: CC0
 * Source: hacKIT, NWERC 2015
 * Description: A set (not multiset!) with support for finding the n'th
 * element, and finding the index of an element.
 * To get a map, change \texttt{null\_type}.
 * For duplicates, use (value, unique ID) keys; the example uses IDs 0 and 1.
 * Usage:
 * Tree<int>t;t.insert(8);t.insert(10);
 * cout<<t.order_of_key(10); // 1
 * cout<<*t.find_by_order(0); // 8
 * Tree<pii>ms;ms.insert({8, 0});ms.insert({8, 1});
 * cout<<ms.order_of_key({8, INT_MIN}); // 0, strictly less
 * cout<<ms.find_by_order(1)->first; // 8, second copy
 * Time: O(\log N)
 */
#pragma once

#include<bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template<class T>
using Tree=tree<T, null_type, less<T>, rb_tree_tag,
    tree_order_statistics_node_update>;

void example() {
	Tree<int>t, t2; t.insert(8);
	auto it=t.insert(10).first;
	assert(it==t.lower_bound(9));
	assert(t.order_of_key(10)==1);
	assert(t.order_of_key(11)==2);
	assert(*t.find_by_order(0)==8);
	t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}
