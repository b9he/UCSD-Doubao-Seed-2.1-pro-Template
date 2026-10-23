/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: Vertex-biconnected components and articulation points in a
 * one-based undirected graph. Add both arc directions; ignore self-loops.
 * MAXN exceeds n; MAXM includes both arcs and reserved slots. vbcc[c] lists
 * vertices; articulation vertices can occur in multiple blocks. cut[u] marks
 * articulation points and cutcnt counts them. Run the isolated-vertex loop
 * after DFS. The DFS root is popped on return. mp reserves space for an
 * optional block-cut forest. Reset arrays, vectors and counters between
 * cases. Independent snippet; copy separately from EBCC/SCC.
 * Usage:
 * add_edge(1,2);add_edge(2,1);
 * add_edge(2,3);add_edge(3,2);
 * for(int i=1;i<=4;i++)if(!dfn[i])tarjan(i,true);
 * for(int i=1;i<=4;i++)if(!head[i])vbcc[++cc].push_back(i);
 * cout<<cc<<' '<<cutcnt; // 3 1, vertex 4 is isolated
 * Time: $O(V+E)$.
 * Memory: $O(MAXN+MAXM)$.
 * Status: User-provided template; compile-checked
 */
#pragma once
const int MAXN=500005,MAXM=4000007; // 双向建边注意开2倍
int dfn[MAXN],low[MAXN],stk[MAXN];
vector<int>vbcc[MAXN],mp[2*MAXN];
int timer=0,e[MAXM],head[MAXN],nxt[MAXM],cnt=1,cc=0,top=0;
bool cut[MAXN];int cutcnt=0;
inline void add_edge(int u,int v){
	e[++cnt]=v;nxt[cnt]=head[u];head[u]=cnt;
}
void tarjan(int i,bool root){
	stk[++top]=i;dfn[i]=low[i]=++timer;int son=0;
	for(int cur=head[i];cur;cur=nxt[cur]){
		int v=e[cur];
		if(dfn[v]){ // 回边或弃边或重边
			low[i]=min(low[i],dfn[v]);
		}else{ // 树边
			son++;tarjan(v,false);low[i]=min(low[i],low[v]);
			if(low[v]>=dfn[i]){
				if(son>=2||!root){if(!cut[i])cutcnt++;cut[i]=true;}
				cc++;while(stk[top]!=v)vbcc[cc].push_back(stk[top--]);
				vbcc[cc].push_back(v);top--;vbcc[cc].push_back(i);
			}
		}
	}if(root)top--;
}
//for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i,1);
//for(int i=1;i<=n;i++){
//    if(head[i]==0){
//        cc++;
//        vbcc[cc].push_back(i);
//    }
//}
