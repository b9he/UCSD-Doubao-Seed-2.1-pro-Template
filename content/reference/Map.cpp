map<int, int>mp;
// 1. Counting and deletion
mp[x]++; // Increment count; missing keys start at 0.
if (--mp[x]==0) mp.erase(x);
// Erase zero counts so size() stays correct.
// 2. Existence and lookup; do not test with mp[x].
if (mp.count(x)) { /* key exists */ } // Test whether x exists: 0 or 1.
auto it=mp.find(x); // Find an iterator.
if (it!=mp.end()) { int val=it->second; }
// 3. Minimum/maximum key: O(1).
int min_k=mp.begin()->first; // Minimum key.
int max_k=mp.rbegin()->first; // Maximum key.
// 4. Predecessor/successor lookup
// Successor: >= x.
auto it1=mp.lower_bound(x);
if (it1!=mp.end()) { int ge=it1->first; }
// Strict successor: > x.
auto it2=mp.upper_bound(x);
if (it2!=mp.end()) { int gt=it2->first; }
// Predecessor <= x: previous before first > x.
auto it3=mp.upper_bound(x);
if (it3!=mp.begin()) { int le=prev(it3)->first; }
// Strict predecessor < x: before first >= x.
auto it4=mp.lower_bound(x);
if (it4!=mp.begin()) { int lt=prev(it4)->first; }
// 5. Iteration
for (auto&[k, v]:mp) {
// Keys k are strictly increasing.
}
