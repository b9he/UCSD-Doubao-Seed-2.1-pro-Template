/**
 * Author: User-provided template
 * Source: Personal template supplied in chat
 * Description: Generic digit-DP recipe for nonnegative decimal integers.
 * Fill in the state capacity, initial state, boundary result, transitions,
 * and optional invalid-state pruning for your problem. The state must retain
 * all information needed by future digits. Memoize only non-limited states
 * after the number has started. Each bound resets memo; choose the boundary
 * result to include or exclude zero. Counts must fit in long long.
 * Usage:
 * // Customize all state placeholders first.
 * long long L=1,R=100;
 * cout<<count_valid(R)-count_valid(L-1);
 * Time: $O(10DS)$ for D digits and S states.
 * Memory: $O(25S)$.
 * Status: Generic recipe; syntax-checked with example state bindings
 */
#pragma once
long long memo[25][MAX_STATE];string s;
long long dfs(int pos,int state,bool is_limit,bool is_lead){
	// 边界返回值 (通常是 1 或 !is_lead)
	if(pos==(int)s.length())return boundary_return_val;
	if(!is_limit&&!is_lead&&memo[pos][state]!=-1)return memo[pos][state];
	long long res=0;int up=is_limit?s[pos]-'0':9;
	for(int i=0;i<=up;++i){
		// if (invalid_condition) continue; // 非法条件剪枝
		if(is_lead){
			if(i==0)res+=dfs(pos+1,lead_zero_state,is_limit&&(i==up),true);
			else res+=dfs(pos+1,lead_first_digit_state,is_limit&&(i==up),false);
		}else res+=dfs(pos+1,next_state,is_limit&&(i==up),false);
	}
	if(!is_limit&&!is_lead)memo[pos][state]=res;
	return res;
}
long long count_valid(long long x){
	if(x<0)return 0;
	s=to_string(x);memset(memo,-1,sizeof(memo));
	return dfs(0,initial_state,true,true);
}
