multiset<ll>ms;
// 1. Insert: O(log N).
ms.insert(x);
// 2. Erase one occurrence safely: O(log N).
auto it=ms.find(x); if (it!=ms.end()) {
	ms.erase(it); }
// 3. Erase all occurrences: O(log N + K).
size_t erased_count=ms.erase(x);
// 4. First >= value: O(log N).
auto lb=ms.lower_bound(val); // First iterator >= val.
if (lb!=ms.end()) { ll value=*lb; }
// 5. First > value: O(log N).
auto ub=ms.upper_bound(val); // First iterator > val.
if (ub!=ms.end()) { ll value=*ub; }
// 6. Minimum/maximum: O(1).
if (!ms.empty()) { ll min_val=*ms.begin();
	ll max_val=*ms.rbegin(); }
