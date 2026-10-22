#include "examples/preamble.h"
#include "content/number-theory/MathSieve.h"
int main() {
 MathSieve sieve(1000);
 auto f=sieve.factorize(120);
 assert(f.size()==3);
 assert(sieve.spf[97]==97);
}
