/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: Tarjan SCC for a one-based directed graph in mp. Set MAXN
 * greater than n. cc is the component count and belong[u] is its 1-based ID.
 * For an edge between components, $belong[u]>belong[v]$; component IDs
 * cc down to 1 give a topological order. Uncomment the two push statements
 * to collect vertices in scc. Before another case, clear mp and scc, zero
 * dfn/low/belong, and reset timer, cc, top. This is an independent snippet.
 * Usage:
 * mp[1]={2};mp[2]={1,3};mp[3]={};
 * for(int i=1;i<=3;i++)if(!dfn[i])tarjan(i);
 * cout<<cc<<' '<<(belong[1]==belong[2]); // 2 1
 * Time: $O(V+E)$.
 * Memory: $O(MAXN+E)$.
 * Status: User-provided template; compile-checked
 */
#pragma once
const int MAXN=10005;
vector<int>mp[MAXN],scc[MAXN];
int dfn[MAXN],low[MAXN],belong[MAXN],stk[MAXN];
int timer=0,cc=0,top=0;
void tarjan(int i){
	dfn[i]=low[i]=++timer;stk[++top]=i;
	for(int v:mp[i]){
		if(belong[v])continue;
		if(dfn[v])low[i]=min(low[i],dfn[v]);
		else{tarjan(v);low[i]=min(low[i],low[v]);}
	}
	if(low[i]==dfn[i]){
		cc++;while(stk[top]!=i){
			// scc[cc].push_back(stk[top]);
			belong[stk[top--]]=cc;
		}
		// scc[cc].push_back(i);
		belong[stk[top--]]=cc;
	}
}
//for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
//强连通分量的逆序就是拓扑序
