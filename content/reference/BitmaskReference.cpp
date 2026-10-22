// Personal bitmask snippet
#define bit(S, i) (((S)>>(i))&1) // Test bit i of S.
#define set_bit(S, i) ((S)|(1<<(i))) // Set bit i.
#define clear_bit(S, i) ((S)&~(1<<(i))) // Clear bit i.
#define toggle_bit(S, i) ((S)^(1<<(i))) // Toggle bit i.
#define lowbit(x) ((x)&-(x)) // Lowest set bit, as in a Fenwick tree.
// __builtin_popcount(S):set-bit count; use popcountll for ll.
// __builtin_ctz(S):trailing zeros/lowest set-bit index; S
// != 0.
// Enumerate every nonempty submask of S.
for (int sub=S; sub; sub=(sub-1)&S) {
// sub is a submask of S.
	int remain=S^sub; // The remaining elements of S.
// Example DP transition:
// dp[S]=min(dp[S], dp[sub]+dp[remain]);
	 }
// Integer widths: personal macros use int shifts.
// For set/clear/toggle, use 0 <= i < 31 on signed int.
// 64-bit unsigned versions allow 0 <= i < 64.
#define bit64(S, i) (((S)>>(i))&1ULL)
#define set_bit64(S, i) ((S)|(1ULL<<(i)))
#define clear_bit64(S, i) ((S)&~(1ULL<<(i)))
#define toggle_bit64(S, i) ((S)^(1ULL<<(i)))
// lowbit(x) is also valid for uint64_t; zero returns zero.
// Avoid negating the minimum signed integer.
__builtin_popcount(S); // 32-bit; zero is allowed.
__builtin_popcountll(S); // 64-bit; zero is allowed.
__builtin_ctz(S); __builtin_ctzll(S); // S != 0.
31-__builtin_clz(S); // Highest set bit, 32-bit; S != 0.
63-__builtin_clzll(S); // Highest set bit, 64-bit; S != 0.
// Only set-bit positions: O(popcount(S)).
for(uint64_t sub=S;sub;sub&=sub-1){ int i=__builtin_ctzll(sub);
}
// All submasks, including zero: O(2^popcount(S)).
for(int sub=S;;sub=(sub-1)&S){
// Process sub.
 if(!sub)break; }
// Original KACTL alternative: all submasks except S,
// including zero. O(2^popcount(S)).
for(int x=S;x;){--x&=S;
// Process x.
}
// All masks and all their submasks together: O(3^n).
// Supersets inside n bits: O(2^(n-popcount(S))).
// 0 <= n < 64; S must fit inside the lowest n bits.
uint64_t full=(1ULL<<n)-1; for(uint64_t sub=S;;sub=(sub+1)|S){
// Process sub.
 if(sub==full)break; }
// Gosper: next mask with the same number of set bits.
// Original KACTL expression, using unsigned arithmetic.
// x != 0; stop if r==0 or r is outside the n-bit range.
uint64_t c=x&-x, r=x+c; uint64_t next=(((r^x)>>2)/c)|r;
// Fixed-popcount enumeration: 0 <= k <= n < 64.
// Handle k==0 separately: only mask zero.
for(uint64_t sub=(1ULL<<k)-1;sub<(1ULL<<n);){
// Process sub; this loop requires k > 0.
 uint64_t c=sub&-sub, r=sub+c; if(r>=(1ULL<<n))break;
 sub=(((r^sub)>>2)/c)|r; }
// SOS DP: original KACTL subset transform, array D[1<<K].
// D[S] becomes the sum of original D[sub] for sub subset S.
rep(b, 0, K)rep(i, 0, (1<<K)) if(i&1<<b)D[i]+=D[i^(1<<b)];
// Superset transform: sum over all supersets of S.
rep(b, 0, K)rep(i, 0, (1<<K)) if(!(i&1<<b))D[i]+=D[i|(1<<b)];
// Inverse subset / superset transforms (Mobius).
rep(b, 0, K)rep(i, 0, (1<<K)) if(i&1<<b)D[i]-=D[i^(1<<b)];
rep(b, 0, K)rep(i, 0, (1<<K)) if(!(i&1<<b))D[i]-=D[i|(1<<b)];
// Each transform: O(K*2^K) time, O(2^K) space.
// Bitset 0/1 subset sum: each weight is used at most once.
bitset<MAXN>dp;dp[0]=1; for(int W:weights)dp|=dp<<W;
// About O(items*MAXN/word_bits); sums >= MAXN are dropped.
// See the bitset snippet for masks and restricted transitions.
// Power of two; exclude zero.
bool power_of_two=S&&!(S&(S-1));
// Remove the lowest set bit.
S&=S-1;
// Gray code: consecutive codes differ in one bit.
uint64_t gray=S^(S>>1);
