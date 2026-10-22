unordered_map<int, int>mp; mp.reserve(100005);
// Reserve to reduce rehashing.
// mp[key]=val; // Insert/update.
// mp.count(key); // Test existence: 1 or 0.
// mp.erase(key); // Erase.
// for (auto const& [k, v] : mp) { /* use k and v */ }
unordered_set<int>us; us.reserve(100005);
// Custom hash
struct custom_hash { static uint64_t splitmix64(uint64_t x) {
		x+=0x9e3779b97f4a7c15;
		x=(x^(x>>30))*0xbf58476d1ce4e5b9;
		x=(x^(x>>27))*0x94d049bb133111eb;
		return x^(x>>31); }
	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x+FIXED_RANDOM); } };
unordered_map<ll, int, custom_hash>safe_map;
