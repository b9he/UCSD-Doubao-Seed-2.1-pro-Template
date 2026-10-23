/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: SPFA plus admissible-path DFS for min-cost max-flow.
 * add\_edge(u,v,w,c) adds capacity w and cost c, with a reverse arc of cost
 * -c. n is the largest vertex ID and $s\ne t$. Negative costs are allowed,
 * but reachable negative-cost residual cycles are unsupported; the guard
 * returns accumulated partial flow/cost when one is detected. dinic returns
 * additional flow and cost, modifying residual capacities. MAXM includes both
 * arc directions and reserved slots. Copy separately from Dinic.
 * Usage:
 * init_flow(3);add_edge(1,2,2,3);add_edge(2,3,2,1);
 * auto [flow,cost]=dinic(3,1,3);
 * cout<<flow<<' '<<cost; // 2 8
 * Time: Each SPFA round is $O(VE)$; total depends on augmentations.
 * Memory: $O(MAXN+MAXM)$.
 * Status: User-provided template; compile-checked
 */
#pragma once
const int MAXN=5007,MAXM=200007; //2倍
struct Edge{int to;long long cap,v;}e[MAXM];
int head[MAXN],nxt[MAXM],cur_edge[MAXN],cnt=1,len[MAXN];
long long dist[MAXN];bool in_queue[MAXN],vis[MAXN];
inline void init_flow(int n){cnt=1;for(int i=0;i<=n;i++)head[i]=0;}
inline void add_edge(int u,int v,long long w,long long c){
	e[++cnt]={v,w,c};nxt[cnt]=head[u];head[u]=cnt;
	e[++cnt]={u,0,-c};nxt[cnt]=head[v];head[v]=cnt;
}
long long dfs(int u,int t,long long rem){
	if(u==t)return rem;
	long long tmp=rem;vis[u]=true; //防 0 环
	for(int cur=cur_edge[u];cur&&rem;cur=nxt[cur]){
		cur_edge[u]=cur; //当前弧优化
		int v=e[cur].to;long long w=e[cur].cap,c=e[cur].v;
		if(!vis[v]&&dist[v]==dist[u]+c&&w>0){
			long long d=dfs(v,t,min(w,rem));
			if(d>0){
				e[cur].cap-=d;e[cur^1].cap+=d;rem-=d;
				if(rem==0)break; //已经没有剩余流量了
			}else dist[v]=1000000000000000000LL;
			//最大费用这里改,这个点push不了更多
		}
	}vis[u]=false; //回溯时一定要取消标记
	return tmp-rem;
}
pair<long long,long long>dinic(int n,int s,int t){
	long long ans=0,cost=0;while(true){
		for(int i=0;i<=n;i++){
			cur_edge[i]=head[i];dist[i]=1000000000000000000LL;
			//最大费用这里改-1e18
			vis[i]=in_queue[i]=false;len[i]=0;
		}dist[s]=0;queue<int>q;in_queue[s]=true;q.push(s);
		while(!q.empty()){
			int u=q.front();q.pop();in_queue[u]=false;
			for(int cur=head[u];cur;cur=nxt[cur]){
				if(e[cur].cap==0)continue;
				int v=e[cur].to;long long w=e[cur].v;
				if(dist[u]+w<dist[v]){ //最大费用这里改
					dist[v]=dist[u]+w;len[v]=len[u]+1;
					if(len[v]>n)return {ans,cost}; //负环
					if(!in_queue[v]){q.push(v);in_queue[v]=true;}
				}
			}
		}if(dist[t]==1000000000000000000LL)break;
		//最大费用这里改-1e18
		long long curans;
		//榨干当前最短路网络
		while((curans=dfs(s,t,1000000000000000000LL))>0){
			ans+=curans;cost+=curans*dist[t];
		}
	}return {ans,cost};
}
