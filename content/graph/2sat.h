/**
 * Author: User-provided notes
 * Source: Personal modeling notes supplied in chat
 * Description: 2-SAT modeling recipe; use SCC.h for Tarjan after building
 * the implication graph. There is no TwoSat class in this snippet.
 * For threshold encodings, also add monotonicity implications between
 * consecutive ordered thresholds. Reserve space for all literal vertices.
 * Usage:
 * // Build the implication graph, then use tarjan(i) from SCC.h.
 * Time: $O(V+E)$ after building the implication graph.
 * Status: Modeling notes
 */
#pragma once
// 2-SAT
// 假设每个变量只有a和b两种取值,把每个点拆成2份
// x==a 或 y==b 转化为 !xa -> yb 和 !yb -> xa
// x==a 转化为 !xa -> xa
// 在图上跑tarjan scc
// 如果某个变量的2个点在同个scc内,没有解
// 否则,变量的取值由拓扑序靠后(scc编号靠前)的点决定
// 数值问题可以转化成x>=k和x<k,结束时逆序遍历所有的k,第一个x>=k拓扑序靠后的点即为答案
