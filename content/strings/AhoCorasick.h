/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: Lowercase AC automaton with completed trie transitions and
 * fail-tree frequency accumulation. Keep ac global; MAXN must exceed the sum
 * of pattern lengths and every pattern ID. Duplicate patterns share a node.
 * Insert all words before init; match counts visits without early exit.
 * Build the fail tree and accumulate once, then cnt[end[i]] is word i's count.
 * clear before reuse; insert every queried ID again. Deep fail trees need
 * enough stack for recursive dfs. Uncomment the alert return for early exit
 * only; it stops counting. init and build\_tree must each run once per case.
 * Usage:
 * ac.insert(1,"a");ac.insert(2,"aa");ac.init();
 * ac.match("aaa");ac.build_tree();ac.dfs(0);
 * cout<<ac.cnt[ac.end[1]]<<' '<<ac.cnt[ac.end[2]]; // 3 2
 * ac.clear(); // next case
 * Time: $O(26S+T+P)$ for total pattern length S, text length T, pattern count P.
 * Memory: $O(26\cdot MAXN)$.
 * Status: Tested against brute-force substring counts
 */
#pragma once
struct ACAM {
	static const int MAXN=200005; // > total pattern length and pattern IDs
	int trie[MAXN][26]{},fail[MAXN]{},cnt[MAXN]{},alert[MAXN]{},end[MAXN]{},tot=0;
	vector<int>mp[MAXN];
	ACAM(){clear();}
	void clear(){
		for(int i=0;i<=tot;i++){
			memset(trie[i],0,sizeof(trie[i]));mp[i].clear();
			fail[i]=alert[i]=cnt[i]=0;
		}tot=0;
	}
	int insert(int i,const string&s){
		int u=0;for(char c:s){int v=c-'a';
			if(!trie[u][v]){trie[u][v]=++tot;}u=trie[u][v];
		}alert[u]=1;end[i]=u;return u;
	}
	void init(){
		queue<int>q;for(int i=0;i<26;i++)if(trie[0][i])q.push(trie[0][i]);
		while(!q.empty()){
			int u=q.front();q.pop();alert[u]|=alert[fail[u]];
			for(int i=0;i<26;i++)if(trie[u][i]){
				fail[trie[u][i]]=trie[fail[u]][i];q.push(trie[u][i]);
			}else trie[u][i]=trie[fail[u]][i];
		}
	}
	bool match(const string&t){
		int u=0;for(char c:t){u=trie[u][c-'a'];cnt[u]++;
			// if(alert[u])return true; // early exit disables full counts
		}return false;
	}
	void build_tree(){for(int i=1;i<=tot;i++)mp[fail[i]].push_back(i);}
	void dfs(int u){for(int v:mp[u]){dfs(v);cnt[u]+=cnt[v];}}
}ac;
