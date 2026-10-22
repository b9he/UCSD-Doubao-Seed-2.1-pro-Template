/**
 * Author: USACO
 * Date: 2025-11-11
 * License: Unknown
 * Source: https://usaco.guide/adv/persistent?lang=cpp
 * Description: Persistent segment tree. Note MXN is O(2n + qlog(n)). Queries are [l,r].
 * Usage:
 * PersistentSegtree st(3, 100);
 * vec<int>a={1, 2, 3};int r0=st.build(a);
 * int r1=st.set(r0, 1, 9);
 * cout<<st.rangeSum(r0, 0, 2); // 6, old version
 * cout<<st.rangeSum(r1, 0, 2); // 13, new version
 * Time: O(\log N)
 * Status: Unknown
 */
#pragma once

struct PersistentSegtree {
	struct Node {
		ll sum=0;
		int l=0, r=0;
	};

	const int n;
	vector<Node>tree;
	int timer=1;

	Node join(int l, int r) { return Node{tree[l].sum+tree[r].sum, l, r}; }

	int build(int tl, int tr, const vector<int>&arr) {
		if (tl==tr) {
			tree[timer]={arr[tl], 0, 0};
			return timer++;
		}
		int mid=(tl+tr)/2;
		tree[timer]=join(build(tl, mid, arr), build(mid+1, tr, arr));
		return timer++;
	}

	int set(int v, int pos, int val, int tl, int tr) {
		if (tl==tr) {
			tree[timer]={val, 0, 0};
			return timer++;
		}
		int mid=(tl+tr)/2;
		if (pos<=mid) {
			tree[timer]=join(set(tree[v].l, pos, val, tl, mid), tree[v].r);
		} else {
			tree[timer]=join(tree[v].l, set(tree[v].r, pos, val, mid+1, tr));
		}
		return timer++;
	}

	ll rangeSum(int v, int ql, int qr, int tl, int tr) {
		if (qr<tl||tr<ql) { return 0ll; }
		if (ql<=tl&&tr<=qr) { return tree[v].sum; }
		int mid=(tl+tr)/2;
		return rangeSum(tree[v].l, ql, qr, tl, mid)+
		       rangeSum(tree[v].r, ql, qr, mid+1, tr);
	}

	PersistentSegtree(int n, int MXN):n(n), tree(MXN) {}
	int build(const vector<int>&arr) { return build(0, n-1, arr); }
	int set(int root, int pos, int val) { return set(root, pos, val, 0, n-1); }
	ll rangeSum(int root, int l, int r) { return rangeSum(root, l, r, 0, n-1); }
	int addCopy(int root) {
		tree[timer]=tree[root];
		return timer++;
	}
};