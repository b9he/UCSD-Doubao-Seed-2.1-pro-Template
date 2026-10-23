/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: Edge-biconnected components and bridges in a one-based
 * undirected graph. Add both directions consecutively so reverse IDs are
 * paired by xor 1. MAXN exceeds n; MAXM includes both arcs and reserved slots.
 * bcc[c] lists vertices, belong[u] gives its component, and cut marks both
 * arcs of a bridge. Isolated vertices form singleton components. The final
 * commented loop builds the bridge forest in mp. Reset arrays, vectors and
 * counters between cases. Independent snippet with shared global names.
 * Usage:
 * add_edge(1,2);add_edge(2,1);
 * add_edge(2,3);add_edge(3,2);
 * for(int i=1;i<=4;i++)if(!dfn[i])tarjan(i,0);
 * cout<<cc<<' '<<cut[2]; // 4 1, vertex 4 is isolated
 * Time: $O(V+E)$.
 * Memory: $O(MAXN+MAXM)$.
 * Status: User-provided template; compile-checked
 */
#pragma once
const int MAXN=500005,MAXM=4000007; // 双向建边注意开2倍
int dfn[MAXN],low[MAXN],stk[MAXN],belong[MAXN];
vector<int>bcc[MAXN],mp[MAXN];
int timer=0,cc=0,top=0,e[MAXM];
int head[MAXN],nxt[MAXM],cnt=1;bool cut[MAXM];
inline void add_edge(int u,int v){
	e[++cnt]=v;nxt[cnt]=head[u];head[u]=cnt;
}
void tarjan(int i,int eid){
	dfn[i]=low[i]=++timer;stk[++top]=i;
	for(int cur=head[i];cur;cur=nxt[cur]){
		int v=e[cur];
		if(dfn[v]>dfn[i]||(eid^1)==cur)continue; // 弃边或反向边
		if(dfn[v]){ // 回边
			low[i]=min(low[i],dfn[v]);
		}else{ // 树边
			tarjan(v,cur);low[i]=min(low[i],low[v]);
			if(low[v]>dfn[i]){
				cut[cur]=cut[cur^1]=true;
				//因此就算要去重也一定要保证反向边相邻
			}
		}
	}
	if(low[i]==dfn[i]){
		cc++;while(stk[top]!=i){
			bcc[cc].push_back(stk[top]);belong[stk[top--]]=cc;
		}bcc[cc].push_back(i);belong[i]=cc;top--;
	}
}
//for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i,0);
//for(int i=1;i<=n;i++){
//    for(int cur=head[i];cur;cur=nxt[cur]){
//        int v=e[cur];
//        if(cut[cur]){
//            mp[belong[i]].push_back(belong[v]);//这样建图自动去重
//        }
//    }
//}
