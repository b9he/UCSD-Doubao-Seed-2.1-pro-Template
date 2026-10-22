/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: When doing DP on intervals: $a[i][j] = \min_{i < k < j}(a[i][k] + a[k][j]) + f(i, j)$, where the (minimal) optimal $k$ increases with both $i$ and $j$,
 *  one can solve intervals in increasing order of length, and search $k = p[i][j]$ for $a[i][j]$ only between $p[i][j-1]$ and $p[i+1][j]$.
 *  This is known as Knuth DP. Sufficient criteria for this are if $f(b,c) \le f(a,d)$ and $f(a,c) + f(b,d) \le f(a,d) + f(b,c)$ for all $a \le b \le c \le d$.
 *  Consider also: LineContainer (ch. Data structures), monotone queues, ternary search.
 * The example evaluates a small recurrence directly; apply the optimal-split bounds above for the optimization.
 * Usage:
 * ll dp[3][3]={}, pref[4]={0, 1, 3, 6};
 * for(int len=2;len<=3;++len)for(int l=0;l+len<=3;++l){
 *  int r=l+len-1;dp[l][r]=LLONG_MAX;
 *  for(int k=l;k<r;++k)dp[l][r]=min(dp[l][r],
 *   dp[l][k]+dp[k+1][r]+pref[r+1]-pref[l]);
 * }
 * cout<<dp[0][2]; // 9
 * Time: O(N^2)
 */
