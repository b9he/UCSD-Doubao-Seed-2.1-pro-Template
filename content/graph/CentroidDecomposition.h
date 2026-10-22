/**
 * Author: USACO
 * Date: 2025-10-10
 * License: None
 * Source: https://usaco.guide/plat/centroid?lang=cpp
 * Description: Recursively find the centroid of a tree and its subtrees.
 * Add answer or parent bookkeeping at the marked callback.
 * Usage:
 * adj={{1}, {0, 2}, {1}};
 * is_removed.assign(3, false);subtree_size.resize(3);
 * int c=get_centroid(0, get_subtree_size(0));cout<<c; // 1
 * build_centroid_decomp();
 * Time: O(N \log N)
 * Status: Unknown
 */

vector<vector<int>>adj;
vector<bool>is_removed;
vector<int>subtree_size;

int get_subtree_size(int node, int parent=-1) {
	subtree_size[node]=1;
	for (int child:adj[node]) {
		if (child==parent||is_removed[child]) { continue; }
		subtree_size[node]+=get_subtree_size(child, node);
	}
	return subtree_size[node];
}

int get_centroid(int node, int tree_size, int parent=-1) {
	for (int child:adj[node]) {
		if (child==parent||is_removed[child]) { continue; }
		if (subtree_size[child]*2>tree_size) {
			return get_centroid(child, tree_size, node);
		}
	}
	return node;
}

void build_centroid_decomp(int node=0) {
	int centroid=get_centroid(node, get_subtree_size(node));
	// <- do something
	is_removed[centroid]=true;
	for (int child:adj[centroid]) {
		if (is_removed[child]) { continue; }
		build_centroid_decomp(child);
	}
}