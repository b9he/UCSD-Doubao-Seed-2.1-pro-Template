/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: One-based Kruskal reconstruction forest. Ascending edge order
 * gives minimax connection thresholds; descending gives maximin thresholds.
 * Set tot=n, clear ch between cases, DFS every DSU root, then precompute(tot).
 * Query distinct connected original vertices; handle u=v by the problem's
 * convention. MAXN must exceed n. Copy separately from BinaryLifting.h due
 * to shared global names. Recursive find/DFS can reach depth $O(N)$.
 * Usage:
 * int n=3;vec<Edge>edges={{1,2,5},{2,3,8}};
 * tot=n;kruskal(n,edges);
 * for(int i=1;i<=tot;i++)if(find(i)==i)dfs(i,0,1);
 * precompute(tot);cout<<val[get_lca(1,3)]; // 8
 * Time: $O(M\log M+(N+M)\log N)$ preprocessing, $O(\log N)$ per query.
 * Memory: $O(MAXNODES\cdot LOGN+M)$.
 * Status: User template; syntax-checked only
 */
#pragma once
// Kruskal 重构树
// 查询两点路径上的最大/最小边权 = LCA(u,v)的val
// 按边权从小到大排序 -> val[lca] = 路径最大边权
// 按边权从大到小排序 -> val[lca] = 路径最小边权
const int MAXN=100005,MAXNODES=2*MAXN,LOGN=20;
struct Edge{int u,v,w;
 bool operator<(const Edge&other)const{return w<other.w;} //TODO修改排序逻辑
};
vector<int>ch[MAXNODES]; // 重构树的子节点
int val[MAXNODES]; // 虚拟节点的点权值
int fa[MAXNODES],dep[MAXNODES],st[MAXNODES][LOGN+1],tot;
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void kruskal(int n,vector<Edge>&edges){
 sort(edges.begin(),edges.end());
 for(int i=1;i<=2*n;i++)fa[i]=i;
 memset(val,-1,sizeof(val));int cnt=0;
 for(auto&e:edges){int ru=find(e.u),rv=find(e.v);
  if(ru!=rv){++tot;fa[ru]=fa[rv]=tot;
   ch[tot].push_back(ru);ch[tot].push_back(rv);val[tot]=e.w;
   if(++cnt==n-1)break;}
 }
}
void dfs(int u,int p,int d){
 dep[u]=d;st[u][0]=p;for(int v:ch[u])dfs(v,u,d+1);
}
void precompute(int n){
 for(int j=1;j<=LOGN;j++)for(int i=1;i<=n;i++)
  st[i][j]=st[st[i][j-1]][j-1];
}
int get_lca(int u,int v){
 if(dep[u]<dep[v])swap(u,v);
 for(int i=LOGN;i>=0;i--)if(dep[u]-(1<<i)>=dep[v])u=st[u][i];
 if(u==v)return u;
 for(int i=LOGN;i>=0;i--)if(st[u][i]!=st[v][i])u=st[u][i],v=st[v][i];
 return st[u][0];
}
// === 使用方式 ===
// tot=n; // 多组数据先清空ch[1..2*n]
// kruskal(n,edges);
// for(int i=1;i<=tot;i++)
//  if(find(i)==i)dfs(i,0,1); // 处理不连通图
// dfs(tot,0,1); // 连通图,与上一种二选一
// precompute(tot);
// 查询:if(find(u)!=find(v)) "impossible";else val[get_lca(u,v)];
// u==v时叶子val=-1,同点查询按题意处理
