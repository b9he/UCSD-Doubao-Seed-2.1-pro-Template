/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * If undo is not needed, skip st, time() and rollback().
 * Usage:
 * RollbackUF uf(3);int t=uf.time();uf.join(0, 1);
 * cout<<uf.size(0); // 2
 * uf.rollback(t);cout<<uf.size(0); // 1
 * Time: $O(\log(N))$
 * Status: tested as part of DirectedMST.h
 */
#pragma once

struct RollbackUF {
	vi e; vector<pii>st;
	RollbackUF(int n):e(n, -1) {}
	int size(int x) { return-e[find(x)]; }
	int find(int x) { return e[x]<0?x:find(e[x]); }
	int time() { return sz(st); }
	void rollback(int t) {
		for (int i=time(); i-->t;)
			e[st[i].first]=st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a=find(a), b=find(b);
		if (a==b) return false;
		if (e[a]>e[b]) swap(a, b);
		st.push_back({a, e[a]});
		st.push_back({b, e[b]});
		e[a]+=e[b]; e[b]=a;
		return true;
	}
};
