/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: Array-based Dinic for directed nonnegative capacities and
 * distinct source and sink. n is the largest vertex ID; set MAXN greater
 * than n. MAXM includes forward/reverse arcs and two reserved slots.
 * Call init\_flow before each case. dinic mutates residual capacities and
 * returns additional flow. Afterwards min\_cut(s) marks the source side in
 * vis; clear vis before repeating that traversal. Copy this snippet separately
 * from MinCostMaxFlow, which uses the same global names.
 * Usage:
 * init_flow(3);add_edge(1,2,4);add_edge(2,3,3);
 * cout<<dinic(3,1,3); // 3
 * min_cut(1);cout<<vis[1]<<' '<<vis[3]; // 1 0
 * Time: $O(V^2E)$.
 * Memory: $O(MAXN+MAXM)$.
 * Status: User-provided template; compile-checked
 */
#pragma once
const int MAXN=100007,MAXM=400007; //2倍
struct Edge{int to;long long cap;}e[MAXM];
int head[MAXN],nxt[MAXM],level[MAXN],cur_edge[MAXN],cnt=1;
bool vis[MAXN];
inline void init_flow(int n){
	cnt=1;for(int i=0;i<=n;i++){head[i]=0;vis[i]=false;}
}
inline void add_edge(int u,int v,long long w){
	e[++cnt]={v,w};nxt[cnt]=head[u];head[u]=cnt;
	e[++cnt]={u,0};nxt[cnt]=head[v];head[v]=cnt;
}
void min_cut(int u){
	if(vis[u])return;
	vis[u]=true;for(int i=head[u];i;i=nxt[i]){
		auto [v,w]=e[i];if(w>0)min_cut(v);
	}
}
long long dfs(int u,int t,long long rem){
	if(u==t)return rem;
	long long tmp=rem;
	for(int cur=cur_edge[u];cur;cur=nxt[cur]){
		cur_edge[u]=cur; //当前弧优化
		int v=e[cur].to;long long w=e[cur].cap;
		if(level[v]==level[u]+1&&w>0){
			long long d=dfs(v,t,min(w,rem));
			if(d>0){
				e[cur].cap-=d;e[cur^1].cap+=d;rem-=d;
				if(rem==0)break; //已经没有剩余流量了
			}else level[v]=-1; //这个点push不了更多
		}
	}return tmp-rem;
}
long long dinic(int n,int s,int t){
	long long ans=0;while(true){
		for(int i=0;i<=n;i++){cur_edge[i]=head[i];level[i]=-1;}
		level[s]=0;queue<int>q;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int cur=head[u];cur;cur=nxt[cur]){ //分层图
				int v=e[cur].to;long long w=e[cur].cap;
				if(w>0&&level[v]==-1){level[v]=level[u]+1;q.push(v);}
			}if(u==t)break;
		}if(level[t]==-1)break;
		ans+=dfs(s,t,1000000000000000000LL);
	}return ans;
}
//init_flow(n);//如果多组数据
//for()add_edge(u,v,w);cout<<dinic(n,s,t)<<"\n";
//min_cut(s);//所有vis标记的点就是S
