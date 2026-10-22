/**
 * Author: chilli
 * Date: 2019-05-17
 * Source: Wikipedia
 * Description: To obtain a maximum independent set of a graph, find a max
 * clique of the complement. If the graph is bipartite, see cover() in Dinic.
 * Usage:
 * vb g(3), complement(3);g[0][1]=g[1][0]=1;
 * rep(i, 0, 3)rep(j, 0, 3)
 *  complement[i][j]=(i!=j&&!g[i][j]);
 * Maxclique solver(complement);auto answer=solver.maxClique();
 * cout<<answer.size(); // 2
 */
