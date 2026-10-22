/**
 * Author: Chengxi Meng
 * Date: 2026-10-20
 * License: CC0
 * Description: Directed shortest paths for weights 0 and 1.
 * Add both arcs for an undirected edge. run(s) resets distances
 * and parents. Unreachable distance is INF, path is empty.
 * Adding an edge invalidates paths until run is called again.
 * Usage:
 * ZeroOneBFS bfs(3);bfs.add_edge(0, 1, 0);
 * bfs.add_edge(1, 2, 1);bfs.run(0);
 * cout<<bfs.dist[2]; // 1
 * for(int v:bfs.get_path(2))cout<<v; // 012
 * Time: O(V+E) per run, O(V+E) space.
 * Status: Preview; example smoke-tested, full stress checks pending
 */
#pragma once
struct ZeroOneBFS { static constexpr int INF=INT_MAX;
 int n, source=-1; vec<vec<pair<int, int>>>adj;
 vec<int>dist, parent; explicit ZeroOneBFS(int N):n(N) {
  if (n<0) throw invalid_argument("negative size");
  adj.resize(n); dist.assign(n, INF); parent.assign(n, -1); }
 void check(int v) const {
  if (v<0||v>=n) throw out_of_range("vertex"); }
 void add_edge(int u, int v, int w) { check(u); check(v);
  if (w!=0&&w!=1) throw invalid_argument("weight");
  adj[u].push_back({v, w}); source=-1; } void run(int s) {
  check(s); source=s; fill(dist.begin(), dist.end(), INF);
  fill(parent.begin(), parent.end(), -1); vec<bool>done(n);
  deque<int>q; q.push_back(s); dist[s]=0; while (!q.empty()) {
   int u=q.front(); q.pop_front(); if (done[u]) continue;
   done[u]=true;
   for (auto [v, w]:adj[u]) if (dist[u]+w<dist[v]) {
	dist[v]=dist[u]+w; parent[v]=u;
	if (w) q.push_back(v); else q.push_front(v); } } }
 vec<int>get_path(int t) const { check(t);
  if (source<0||dist[t]==INF) return {}; vec<int>p;
  for (int v=t;v!=-1;v=parent[v]) p.push_back(v);
  reverse(p.begin(), p.end()); return p; } };
