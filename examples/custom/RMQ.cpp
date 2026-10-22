#include "examples/preamble.h"
#include "content/data-structures/RMQ.h"
int main() {
 RMQ<int> rmq(vector<int>{4,2,7});
 assert(rmq.query(0,3)==2);
}
