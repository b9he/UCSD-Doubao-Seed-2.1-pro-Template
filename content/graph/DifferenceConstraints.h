/**
 * Author: User-provided notes
 * Source: Personal difference-constraints notes supplied in chat
 * Description: Difference constraints via BellmanFord.h. Keep reference z
 * separate from super-source S; add zero-cost edges from S to all variables
 * and z. Start with fresh nodes: any dist=-inf means infeasible; otherwise
 * use dist[b]-dist[z]. Example: $3\le b\le4$, z=0,b=1,S=2. Ed weights use int.
 * Usage:
 * vec<Node>nodes(3);
 * vec<Ed>edges={{1,0,-3},{0,1,4},{2,0,0},{2,1,0}};
 * bellmanFord(nodes,edges,2);
 * bool ok=true;for(auto&v:nodes)if(v.dist==-inf)ok=false;
 * cout<<ok; // 1: constraints are feasible
 * if(ok)cout<<nodes[1].dist-nodes[0].dist; // 3
 * Time: $O(VE)$ using BellmanFord.
 * Status: Modeling notes; example syntax-checked
 */
#pragma once
#include "BellmanFord.h"
//x-y<=c -> y到x连+c的边
//x-y<c -> x-y<=c-1
//b<=a+3 -> a->b连一条+3的边
//b>=a+4 -> b->a连一条-4的边
//b>=3 -> b到限制源点连一条-3的边
//b<=4 -> 限制源点到b连一条+4的边
//为保证连通性,让一个超级源点向所有真点连0的边
//这个连法最后需要找负环
//严格不等式减1只适用于整数变量
//限制源点z与超级源点S分开,S还要向z连0边
//无负环时,有常数界的变量取dist[b]-dist[z]
