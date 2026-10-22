#include "examples/preamble.h"
#include "content/number-theory/BigInt.h"
int main() {
 BigInt a(string("1000000000000000000"));
 BigInt b(7);
 cout<<a+b<<"\n";
 assert(a-b<a);
}
