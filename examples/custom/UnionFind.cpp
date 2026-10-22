#include "examples/preamble.h"
#include "content/data-structures/UnionFind.h"
int main() {
 UF uf(4);
 uf.join(0,1);
 assert(uf.sameSet(0,1));
 assert(uf.size(0)==2);
}
