/**
 * Author: USACO, Jack Xiang
 * Date: 2025-10-08
 * License: Unknown
 * Source: https://usaco.guide/adv/string-search
 * Description: Lowercase dictionary with duplicate counts. \texttt{find} counts exact words;
 * \texttt{countPrefix} counts inserted words with the given prefix, including duplicates.
 * The empty prefix counts all inserted words.
 * Usage:
 * Trie tr;tr.insert("abc");tr.insert("abc");
 * cout<<tr.find("abc")<<' '<<tr.find("ab"); // 2 0
 * cout<<tr.countPrefix("ab"); // 2
 * Time: O(26N)
 * Status: Unknown
 */

#pragma once

struct Trie {
    struct TrieNode {
        array<int, 26>nxt={};
        int stop=0, pass=0;
    };

    int node_count=0;
    vector<TrieNode>info;

    Trie():info(1) {}
    Trie(int N):info(N) {}
    
    void insert(const string&word) {
        int node=0;
        info[node].pass++;
        for(const char&c:word) {
            // If a node with the current char doesn't exist create one.
            if(info[node].nxt[c-'a']==0) { 
                info[node].nxt[c-'a']=++node_count; 
                if(node_count>=sz(info)) {
                    info.emplace_back();
                }
            }
            // Move down the path in the trie.
            node=info[node].nxt[c-'a'];
            info[node].pass++;
        }
        info[node].stop++;
    }

    int find(const string&word) {
        int node=0;
        for(const char&c:word) {
            if(info[node].nxt[c-'a']==0) {return 0;}
            node=info[node].nxt[c-'a'];
        }
        return info[node].stop;
    }

    int countPrefix(const string&prefix) {
        int node=0;
        for(char c:prefix) {
            if(!info[node].nxt[c-'a'])return 0;
            node=info[node].nxt[c-'a'];
        }
        return info[node].pass;
    }
};
