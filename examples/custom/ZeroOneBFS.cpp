#include "examples/preamble.h"
#include "content/graph/ZeroOneBFS.h"
int main() {
 ZeroOneBFS bfs(3);
 bfs.add_edge(0,1,0);
 bfs.add_edge(1,2,1); bfs.run(0);
 assert(bfs.dist[2]==1);
 assert(bfs.get_path(2)==vector<int>({0,1,2}));
}
