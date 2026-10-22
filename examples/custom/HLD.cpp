#include "examples/preamble.h"
#include "content/graph/HLD.h"
int main() {
 vector<vi> adj={{1},{0,2},{1}};
 HLD<false> hld(adj);
 hld.modifyPath(0,2,1000000000);
 hld.modifyPath(1,2,5);
 assert(hld.queryPath(0,2)==5);
}
