#include "examples/preamble.h"
#include "content/geometry/HalfPlaneIntersection.h"
int main() {
 using namespace SnippetHPI;
 vector<HLine> h={
  {Point(0,0),Point(1,0)},
  {Point(1,0),Point(1,1)},
  {Point(1,1),Point(0,1)},
  {Point(0,1),Point(0,0)}};
 auto poly=halfPlaneIntersection(h);
 assert(poly.size()==4);
}
