/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: DSU on tree; ans[u] counts distinct values in u's subtree.
 * Vertices are 1-based, with 0 meaning no parent or heavy child. Set MAXN
 * greater than n and compress values into $[0,MAXN)$. dfs1 resets heavy
 * children. Use keep=false at the root to clear counts after answering;
 * otherwise reset color and diff before reuse. Clear mp between cases.
 * This is an independent snippet; allow enough stack for recursive DFS.
 * Usage:
 * mp[1]={2,3};mp[2]={1};mp[3]={1};
 * val[1]=val[2]=1;val[3]=2;
 * dfs1(1,0);dfs_dsu(1,0,false);
 * cout<<ans[1]<<' '<<ans[2]; // 2 1
 * Time: $O(N\log N)$.
 * Memory: $O(MAXN)$.
 * Status: User-provided template; compile-checked
 */
#pragma once
const int MAXN=200005;
vector<int>mp[MAXN];
vector<int>sz=vector<int>(MAXN),val(MAXN),hc(MAXN);
vector<int>ans(MAXN),color(MAXN);int diff=0;
void dfs1(int u,int fa){
	sz[u]=1;hc[u]=0;
	for(int v:mp[u])if(v!=fa){
		dfs1(v,u);sz[u]+=sz[v];
		if(!hc[u]||sz[v]>sz[hc[u]])hc[u]=v;
	}
}
void update(int u,int fa,int flag,int skip){
	if(flag==1){if(++color[val[u]]==1)diff++;}
	else if(--color[val[u]]==0)diff--;
	for(int v:mp[u])if(v!=fa&&v!=skip)update(v,u,flag,skip);
}
void dfs_dsu(int u,int fa,bool keep){
	for(int v:mp[u])if(v!=fa&&v!=hc[u])dfs_dsu(v,u,false);
	if(hc[u])dfs_dsu(hc[u],u,true);
	update(u,fa,1,hc[u]);ans[u]=diff;
	if(!keep)update(u,fa,-1,0);
}
