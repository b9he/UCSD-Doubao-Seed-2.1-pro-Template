/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: Suffix automaton for a..z. Keep sam global; MAXN bounds the
 * string length. Build the suffix-link tree and run dfs(0) once to accumulate
 * occurrence counts. dfs returns the maximum of length times occurrences
 * over substrings occurring at least twice. Call init before each case.
 * The separator '\{' needs 27 transition columns and both loops changed to 27.
 * Recursive dfs needs enough stack for a deep suffix-link tree.
 * Usage:
 * string str="ababa";sam.init();for(char c:str)sam.insert(c);
 * sam.build_tree();cout<<sam.dfs(0); // 6
 * Time: $O(26N)$ for a string of length N.
 * Memory: $O(26\cdot MAXN)$, with space for $2\cdot MAXN$ states.
 * Status: User-provided template; compile-checked
 */
#pragma once
struct SAM {
	static const int MAXN=1000007;
	int tot=0,last=0,len[2*MAXN],link[2*MAXN],cnt[2*MAXN];
	int tran[2*MAXN][26];vector<int>mp[2*MAXN];
	void init(){
		for(int i=0;i<=tot;i++){
			mp[i].clear();cnt[i]=len[i]=link[i]=0;
			for(int j=0;j<26;j++)tran[i][j]=0;
		}last=tot=0;link[0]=-1;
	}
	void insert(char ori){
		int c=ori-'a',np=++tot;
		cnt[np]=1;tran[last][c]=np;len[np]=len[last]+1;
		int p=link[last];last=np;
		while(p!=-1&&!tran[p][c]){tran[p][c]=np;p=link[p];}
		if(p==-1){link[np]=0;return;}
		int q=tran[p][c];
		if(len[q]==len[p]+1){link[np]=q;return;}
		int nq=++tot;link[nq]=link[q];
		link[q]=link[np]=nq;len[nq]=len[p]+1;
		for(int i=0;i<26;i++)tran[nq][i]=tran[q][i];
		while(p!=-1&&tran[p][c]==q){tran[p][c]=nq;p=link[p];}
	}
	void build_tree(){for(int i=1;i<=tot;i++)mp[link[i]].push_back(i);}
	ll dfs(int i){
		ll maxn=0;for(int v:mp[i]){maxn=max(maxn,dfs(v));cnt[i]+=cnt[v];}
		if(cnt[i]>1){maxn=max(maxn,(ll)cnt[i]*len[i]);}return maxn;
	}
}sam;
