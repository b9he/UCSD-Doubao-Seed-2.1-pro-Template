/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Integer max-flow and s-t min-cut; capacities are nonnegative and $s\ne t$.
 * The fourth \texttt{addEdge} argument is reverse capacity (default 0; use $c$ for undirected edges).
 * \texttt{calc} returns additional flow and updates residual capacities \texttt{c}; signed edge flow is \texttt{oc-c}.
 * Read the source side with \texttt{leftOfMinCut} after \texttt{calc}.
 * \par For bipartite matching, \texttt{g[u]} lists right IDs $[0,m)$ and \texttt{r.size()=m}.
 * \texttt{dfsMatching} keeps \texttt{g} unchanged, returns the size and fills \texttt{r[right]=left} ($-1$ if unmatched).
 * \texttt{hopcroftKarp} is an alias.
 * \texttt{cover(g,n,m)} returns left IDs $u$ and right IDs $n+v$; its complement is a maximum independent set.
 * Usage:
 * // Max flow / min cut
 * Dinic f(3);
 * f.addEdge(0, 1, 4);f.addEdge(1, 2, 3);
 * cout<<f.calc(0, 2); // max flow: 3
 * cout<<f.adj[0][0].flow(); // edge 0->1 flow: 3
 * cout<<f.leftOfMinCut(0); // source side: 1
 * cout<<f.leftOfMinCut(2); // source side: 0
 * 
 * // Bipartite matching: 2 left, 2 right
 * vec<vi>g={{0, 1}, {1}};vi r(2, -1);
 * cout<<dfsMatching(g, r); // size: 2
 * cout<<r[0]<<' '<<r[1]; // right->left: 0 1
 * 
 * // Minimum vertex cover / maximum independent set
 * vi cv=cover(g, 2, 2);
 * for(int v:cv)cout<<v<<' '; // cover: 0 1
 * vi used(4);for(int v:cv)used[v]=1;
 * rep(v, 0, 4)if(!used[v])cout<<v<<' '; // independent: 2 3
 * Time: O(VE \log U), U=max capacity; O((E+V)\sqrt V) for matching/cover.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once
struct Dinic {
 struct Edge { int to, rev;ll c, oc;
  ll flow(){return max(oc-c, 0LL);} };
 vi lvl, ptr, q;vec<vec<Edge>>adj;
 Dinic(int n):lvl(n), ptr(n), q(n), adj(n){}
 void addEdge(int a, int b, ll c, ll rcap=0){
  adj[a].push_back({b, sz(adj[b]), c, c});
  adj[b].push_back({a, sz(adj[a])-1, rcap, rcap}); }
 ll dfs(int v, int t, ll f){if(v==t||!f)return f;
  for(int&i=ptr[v];i<sz(adj[v]);i++){Edge&e=adj[v][i];
   if(lvl[e.to]==lvl[v]+1)
    if(ll p=dfs(e.to, t, min(f, e.c))){
     e.c-=p, adj[e.to][e.rev].c+=p;return p; }
  }return 0; }
 ll calc(int s, int t){ll flow=0;q[0]=s;
  rep(L, 0, 31)do{ // 'int L=30' maybe faster for random data
   lvl=ptr=vi(sz(q));int qi=0, qe=lvl[s]=1;
   while(qi<qe&&!lvl[t]){int v=q[qi++];
    for(Edge e:adj[v])if(!lvl[e.to]&&e.c>>(30-L))
     q[qe++]=e.to, lvl[e.to]=lvl[v]+1; }
   while(ll p=dfs(s, t, LLONG_MAX))flow+=p;
  }while(lvl[t]);return flow; }
 bool leftOfMinCut(int a){return lvl[a]!=0;}
};
namespace dinic_detail {
Dinic bipartite(const vec<vi>&g, int m){
 int n=sz(g), s=n+m, t=s+1;Dinic f(t+1);
 rep(u, 0, n){f.addEdge(s, u, 1);
  for(int v:g[u])f.addEdge(u, n+v, 1);}
 rep(v, 0, m)f.addEdge(n+v, t, 1);f.calc(s, t);return f;
}}
int dfsMatching(vec<vi>&g, vi&btoa){
 int n=sz(g), m=sz(btoa), res=0;
 auto f=dinic_detail::bipartite(g, m);fill(all(btoa), -1);
 rep(u, 0, n)for(auto&e:f.adj[u])
  if(e.to>=n&&e.to<n+m&&e.flow())btoa[e.to-n]=u, ++res;
 return res;
}
int hopcroftKarp(vec<vi>&g, vi&r){return dfsMatching(g, r);}
vi cover(vec<vi>&g, int n, int m){
 assert(n==sz(g));auto f=dinic_detail::bipartite(g, m);vi ans;
 rep(u, 0, n)if(!f.leftOfMinCut(u))ans.push_back(u);
 rep(v, 0, m)if(f.leftOfMinCut(n+v))ans.push_back(n+v);
 return ans;
}
