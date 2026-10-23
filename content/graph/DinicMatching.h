/**
 * Author: Personal adaptation
 * Source: Existing matching/cover helpers adapted to the personal Dinic
 * Description: Bipartite matching and minimum vertex cover using Dinic.
 * g[u] lists right IDs in $[0,m)$; btoa has m entries and receives matched
 * left IDs, or -1. g is unchanged. cover returns left IDs u and right IDs
 * n+v; its complement is a maximum independent set. Each call rebuilds and
 * overwrites the global Dinic network. Respect Dinic's vertex/arc capacities.
 * hopcroftKarp is an alias for the same max-flow implementation.
 * Usage:
 * vec<vi>g={{0,1},{1}};vi r(2,-1);
 * cout<<dfsMatching(g,r); // 2
 * auto cv=cover(g,2,2);vi used(4);
 * for(int v:cv)used[v]=1;
 * rep(v,0,4)if(!used[v])cout<<v<<' '; // maximum independent set
 * Status: Compile-checked
 */
#pragma once
#include "Dinic.h"
namespace dinic_detail {
void bipartite(const vec<vi>&g,int m){
	int n=sz(g),s=n+m,t=s+1;init_flow(t);
	rep(u,0,n){add_edge(s,u,1);for(int v:g[u])add_edge(u,n+v,1);}
	rep(v,0,m)add_edge(n+v,t,1);
	dinic(t,s,t);
}
}
int dfsMatching(vec<vi>&g,vi&btoa){
	int n=sz(g),m=sz(btoa),res=0;
	dinic_detail::bipartite(g,m);fill(all(btoa),-1);
	rep(u,0,n)for(int i=head[u];i;i=nxt[i])
		if(!(i&1)&&e[i].to>=n&&e[i].to<n+m&&e[i^1].cap>0)
			btoa[e[i].to-n]=u,++res;
	return res;
}
int hopcroftKarp(vec<vi>&g,vi&r){return dfsMatching(g,r);}
vi cover(vec<vi>&g,int n,int m){
	assert(n==sz(g));dinic_detail::bipartite(g,m);min_cut(n+m);vi ans;
	rep(u,0,n)if(!vis[u])ans.push_back(u);
	rep(v,0,m)if(vis[n+v])ans.push_back(n+v);
	return ans;
}
