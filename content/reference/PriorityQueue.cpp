priority_queue<int>maxheap;
priority_queue<int, vec<int>, greater<int>>minheap;
auto cmp=[](pair<int, int>a, pair<int, int>b){
 return a.second>b.second; };
priority_queue<pair<int, int>, vec<pair<int, int>>, decltype(cmp)>pq(cmp);
struct Type{int property;};vec<Type>arr;
sort(arr.begin(),arr.end(),[=](const auto&a,const auto&b){
 return a.property<b.property; // ascending
});
auto byProperty=[=](const auto&a,const auto&b){
 return a.property>b.property; // min-heap: larger values have lower priority
};
priority_queue<Type,vec<Type>,decltype(byProperty)>propertyHeap(byProperty);
// [=] captures outer local variables by value.
// Check empty() before top()/pop().
