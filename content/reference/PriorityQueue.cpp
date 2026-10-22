priority_queue<int>maxheap;
priority_queue<int, vec<int>, greater<int>>minheap;
auto cmp=[](pair<int, int>a, pair<int, int>b){
 return a.second>b.second; };
priority_queue<pair<int, int>, vec<pair<int, int>>, decltype(cmp)>pq(cmp);
// Check empty() before top()/pop().
