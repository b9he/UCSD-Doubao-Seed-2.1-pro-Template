#include "examples/preamble.h"
#include "content/strings/KMP.h"
int main() {
 auto hits=match("ababa","aba");
 assert(hits==vi({0,2}));
}
