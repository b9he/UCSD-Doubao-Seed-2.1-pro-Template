#include "examples/preamble.h"
#include "content/data-structures/LazySegmentTree.h"
int main() {
 vector<Info> a={Info(1),Info(5),Info(3)};
 LazySegmentTree<Info,Tag> st(a);
 st.modify(0,2,Tag{2});
 assert(st.query(0,3).sum==13);
 assert(st.query(0,2).max_val==7);
}
