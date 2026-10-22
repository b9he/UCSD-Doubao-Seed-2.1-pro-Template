#include "../utilities/template.h"
#define vec vector
#include "../../content/graph/Dinic.h"

ll bruteCut(int n, const vector<array<ll,3>>& arcs, int s, int t) {
 ll best=LLONG_MAX;
 rep(mask,0,1<<n) if((mask>>s&1)&&!(mask>>t&1)) {
  ll sum=0;for(auto [u,v,c]:arcs)
   if((mask>>u&1)&&!(mask>>v&1))sum+=c;
  best=min(best,sum);
 }
 return best;
}
int main() {
 mt19937_64 rng(20261020);
 rep(it,0,20000) {
  int n=2+rng()%7,s=rng()%n,t=rng()%(n-1);if(t>=s)++t;
  Dinic f(n);vector<array<ll,3>> arcs;
  int m=rng()%35;
  rep(i,0,m) {
   int u=rng()%n,v=rng()%n;
   ll c=rng()%100,d=rng()%100;
   if(it%5==0)c<<=35,d<<=35;
   f.addEdge(u,v,c,d);arcs.push_back({u,v,c});arcs.push_back({v,u,d});
  }
  ll flow=f.calc(s,t);assert(flow==bruteCut(n,arcs,s,t));
  assert(f.leftOfMinCut(s)&&!f.leftOfMinCut(t));
  vector<ll> balance(n);ll cut=0;
  rep(u,0,n)for(auto &e:f.adj[u]) {
   assert(e.c>=0&&e.flow()<=e.oc);
   balance[u]+=e.flow();balance[e.to]-=e.flow();
   if(f.leftOfMinCut(u)&&!f.leftOfMinCut(e.to))cut+=e.oc;
  }
  assert(cut==flow&&balance[s]==flow&&balance[t]==-flow);
  rep(u,0,n)if(u!=s&&u!=t)assert(balance[u]==0);
  assert(f.calc(s,t)==0); // calc returns additional flow.
 }
 cout<<"20,000 Dinic cases passed: brute min-cut, flow conservation, residual cut.\n";
}
