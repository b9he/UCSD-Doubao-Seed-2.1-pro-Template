/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: One-based binary-lifting LCA for a tree. Set MAXN greater than n
 * and choose LOGN with $2^{LOGN} \ge n$. Vertex 0 is the null ancestor.
 * Add both directions to mp, then run DFS and preprocessing. Clear mp between
 * test cases. Use HLD if memory is tight.
 * Usage:
 * mp[1]={2,3};mp[2]={1,4};mp[3]={1};mp[4]={2};
 * dfs(1,0,1);precompute(4);
 * cout<<get_lca(4,3)<<' '<<get_lca(4,2); // 1 2
 * Time: $O(N\log N)$ preprocessing, $O(\log N)$ per query.
 * Memory: $O(MAXN\cdot LOGN)$.
 * Status: Tested against an independent LCA implementation
 */
#pragma once
const int MAXN=200005,LOGN=20;
vector<int>mp[MAXN];
int dep[MAXN],st[MAXN][LOGN+1];
void dfs(int u,int p,int d){
	dep[u]=d;st[u][0]=p;
	for(int v:mp[u])if(v!=p)dfs(v,u,d+1);
}
void precompute(int n){
	for(int j=1;j<=LOGN;j++)for(int i=1;i<=n;i++)
		st[i][j]=st[st[i][j-1]][j-1];
}
int get_lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	for(int i=LOGN;i>=0;i--)
		if(dep[u]-(1<<i)>=dep[v])u=st[u][i];
	if(u==v)return u;
	for(int i=LOGN;i>=0;i--)if(st[u][i]!=st[v][i])
		u=st[u][i],v=st[v][i];
	return st[u][0];
}
