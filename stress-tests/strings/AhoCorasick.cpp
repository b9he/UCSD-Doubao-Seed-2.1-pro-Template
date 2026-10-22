#include "../utilities/template.h"
#include "../../content/strings/AhoCorasick.h"

void test(const vector<string>& patterns,const vector<string>& texts) {
	ac.clear();
	for(int i=0;i<sz(patterns);i++)ac.insert(i+1,patterns[i]);
	ac.init();
	for(const string& text:texts){
		int u=0;
		for(int i=0;i<sz(text);i++){
			u=ac.trie[u][text[i]-'a'];
			bool expected=false;
			for(const string& p:patterns)
				if(sz(p)<=i+1&&text.compare(i+1-sz(p),sz(p),p)==0)
					expected=true;
			assert(bool(ac.alert[u])==expected);
		}
		ac.match(text);
	}
	ac.build_tree();ac.dfs(0);
	for(int i=0;i<sz(patterns);i++){
		int expected=0;
		for(const string& text:texts)
			for(int j=0;j+sz(patterns[i])<=sz(text);j++)
				expected+=text.compare(j,sz(patterns[i]),patterns[i])==0;
		assert(ac.cnt[ac.end[i+1]]==expected);
	}
}

int main(){
	// A non-static object must initialize its arrays and counter too.
	auto local=make_unique<ACAM>();
	local->insert(1,"ab");local->init();local->match("abab");
	local->build_tree();local->dfs(0);
	assert(local->cnt[local->end[1]]==2);local.reset();
	test({"a","aa","aaa","a"},{"aaaaa","aa",""});
	test({"he","she","hers","his","z"},{"ushers","hishers"});
	test({"a","a","a","a","a"},{"a"}); // IDs may exceed node count
	test({"abcdefghijklmnopqrstuvwxyz"},{"abcdefghijklmnopqrstuvwxyz"});
	test({string(4000,'a'),"a"},{string(5000,'a')});
	test({"b"},{"aaaa"}); // clear after a larger automaton
	test({}, {"abc",""});
	mt19937 rng(712367);
	auto word=[&](int n){string s(n,'a');for(char& c:s)c=char('a'+rng()%4);return s;};
	for(int t=0;t<5000;t++){
		vector<string> patterns,texts;
		int n=rng()%16;
		for(int i=0;i<n;i++)patterns.push_back(word(1+rng()%10));
		for(int i=0;i<3;i++)texts.push_back(word(rng()%60));
		test(patterns,texts);
	}
	cout<<"Tests passed: 5000 random cases and fixed overlap/reuse/alert cases!\n";
}
