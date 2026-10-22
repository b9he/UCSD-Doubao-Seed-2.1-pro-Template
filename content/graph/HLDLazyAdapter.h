/**
 * Author: Chengxi Meng
 * Source: Personal VS Code snippets
 * Description: Adapter between the original HLD and the Info/Tag lazy segment tree.
 * Preserves initial values of -1e9 and the original add/max interface.
 * Usage:
 * HLDCompat::Node st(0, 3);st.add(0, 3, 1000000000);
 * st.add(1, 3, 5);cout<<st.query(0, 3); // 5
 * Time: O(N) build and space; O(\log N) add/query.
 * Status: Layout preview; original implementation retained
 */
#pragma once
#include "../data-structures/LazySegmentTree.h"
namespace HLDCompat { struct Node { int lo;
 LazySegmentTree<Info, Tag>st;
 Node(int l, int r):lo(l), st(vec<Info>(r-l, Info(-1000000000))){}
 void add(int l, int r, int x){ st.modify(l-lo, r-lo, Tag{x}); }
 int query(int l, int r){ return l==r?-1000000000:int(st.query(l-lo, r-lo).max_val); }
}; }
