#include "../utilities/template.h"
#define vec vector
#include "../../content/graph/Dinic.h"

int bruteMatching(const vector<vi>& g,int m) {
 vector<bool> dp(1<<m);dp[0]=true;
 for(auto &row:g) {
  auto next=dp;
  rep(mask,0,1<<m)if(dp[mask])for(int v:row)
   if(!(mask>>v&1))next[mask|1<<v]=true;
  dp.swap(next);
 }
 int ans=0;rep(mask,0,1<<m)if(dp[mask])ans=max(ans,__builtin_popcount((unsigned)mask));
 return ans;
}
int main() {
 mt19937 rng(20261020);
 rep(it,0,20000) {
  int n=rng()%9,m=rng()%9;vector<vi> g(n);
  rep(u,0,n)rep(v,0,m)if(rng()%3==0) {
   g[u].push_back(v);if(rng()%5==0)g[u].push_back(v);
  }
  auto orig=g;int best=bruteMatching(g,m);
  vi r(m,-1),btoa(m,-1);
  assert(dfsMatching(g,btoa)==best&&hopcroftKarp(g,r)==best);
  for(auto match:{r,btoa}) {
   vi seen(n);int count=0;
   rep(v,0,m)if(match[v]!=-1) {
    int u=match[v];assert(0<=u&&u<n&&!seen[u]++);
    assert(find(all(g[u]),v)!=g[u].end());++count;
   }
   assert(count==best);
  }
  auto cv=cover(g,n,m);assert(sz(cv)==best);
  vi used(n+m);for(int v:cv)assert(0<=v&&v<n+m&&!used[v]++);
  rep(u,0,n)for(int v:g[u])assert(used[u]||used[n+v]);
  assert(g==orig); // all public wrappers keep the graph unchanged.
 }
 cout<<"20,000 bipartite cases passed: both old matching APIs, cover, independent-set complement.\n";
}
