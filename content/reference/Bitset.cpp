// GCC hardware tuning for builtins and bitset.
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include<bits/stdc++.h>
using namespace std; const int MAXN=5005;
// 1. Basic operations and queries
void basic_operations() { bitset<MAXN>bs; bs.set();
// Set all bits.
	bs.reset(); // Clear all bits.
	bs.set(3); // Set bit 3.
	bs.set(4, 0); // Clear bit 4.
	bs.flip(); // Flip all bits.
	bs.flip(3); // Flip bit 3.
	int cnt=bs.count(); // Count set bits.
	bool has_1=bs.any(); // Any set bit?
	bool all_0=bs.none(); // All bits zero?
	bool is_1=bs.test(3); // Test bit 3 with bounds checking.
}
// 2. Fast set-bit iteration (GCC/libstdc++)
void fast_iterate() { bitset<MAXN>bs;
	bs.set(10); bs.set(100); bs.set(5000);
// GCC extensions: _Find_first() and _Find_next().
// O(MAXN/64+number of set bits); skips zero runs.
	for (int i=bs._Find_first(); i<bs.size(); i=bs._Find_next(i)) {
// i is a valid index of a set bit.
// Here i visits 10, 100 and 5000.
	} }
// 3. Mask for the inclusive interval [L,R]
void create_interval_mask() { int L=20, R=30;
// A. Shifts; constant bitset storage, no preprocessing.
	bitset<MAXN>mask_A; int len=R-L+1; mask_A.set();
// 11111111...
	mask_A>>=(MAXN-len); // Keep the lowest len bits.
	mask_A<<=L; // Shift to position L.
// B. Precomputed prefix masks; XOR costs O(MAXN/64).
	static bitset<MAXN>pre_masks[MAXN];
	static bool init=false; if (!init) { pre_masks[0].reset();
		for (int i=1; i<MAXN;++i) {
			pre_masks[i]=pre_masks[i-1]; pre_masks[i].set(i-1);
		} init=true; }
// XOR [0,R] and [0,L-1] to get [L,R]; R+1 < MAXN.
	bitset<MAXN>mask_B=pre_masks[R+1]^pre_masks[L]; }
// 4. DP transitions
void bitset_dp_transition() { bitset<MAXN>dp; dp.set(0);
// Initial state: sum zero is attainable.
// Case 1. Shift all states, e.g. a 0/1 item of weight W.
	int W=3; dp|=(dp<<W);
// Keep old states and add states increased by W.
// Case 2. Restrict transitions with a mask.
// Only states in [20,30] may increase by 5.
	int L=20, R=30, add_val=5; bitset<MAXN>mask;
	mask.set(); mask>>=(MAXN-(R-L+1)); mask<<=L;
	dp|=((dp&mask)<<add_val);
// Filter with &, shift, then merge with |.
}
