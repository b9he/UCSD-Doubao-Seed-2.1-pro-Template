/**
 * Author: Chengxi Meng
 * Source: Personal VS Code snippets
 * Description: Generic lazy segment tree using Info, Tag and apply. Zero-based [l,r).
 * kth(k) returns the zero-based index of the 1-based rank, or -1;
 * requires a nonempty tree and nonnegative frequency sums.
 * Usage:
 * vec<Info>a={Info(1), Info(5), Info(3)};
 * LazySegmentTree<Info, Tag>st(a);
 * st.modify(0, 2, Tag{2}); // add 2 to [0,2)
 * auto ans=st.query(0, 3);
 * cout<<ans.sum<<' '<<ans.max_val; // 13 7
 * vec<Info>f={Info(1), Info(0), Info(1)};
 * LazySegmentTree<Info, Tag>freq(f);
 * cout<<freq.kth(2); // index: 2 (rank starts at 1)
 * Time: O(N) build and space; O(\log N) per operation.
 * Status: Layout preview; original implementation retained
 */
#pragma once
struct Info {
 ll sum=0;ll max_val=-1e18;ll len=0;
 Info() {} Info(ll val):sum(val), max_val(val), len(1) {}
 friend Info operator+(const Info&a, const Info&b) {
  Info c;c.sum=a.sum+b.sum;
  c.max_val=max(a.max_val, b.max_val);
  c.len=a.len+b.len;return c;
 }
};
struct Tag {
 ll add=0;bool has_tag() const {return add!=0;}
 void clear() {add=0;}
};
void apply(Info&info, const Tag&tag) {
 if (!tag.has_tag()) return;
 info.sum+=tag.add*info.len;info.max_val+=tag.add;
}
void apply(Tag&old_tag, const Tag&new_tag) {
 old_tag.add+=new_tag.add;
}
template<class Info, class Tag>
class LazySegmentTree {
private:
 int n;vec<Info>info;vec<Tag>tag;
 void push_up(int p) {info[p]=info[2*p]+info[2*p+1];}
 void apply_node(int p, const Tag&v) {
  apply(info[p], v);apply(tag[p], v);
 }
 void push_down(int p) {
  if (tag[p].has_tag()) {
   apply_node(2*p, tag[p]);apply_node(2*p+1, tag[p]);
   tag[p].clear();
  }
 }
 void build(int p, int l, int r, const vec<Info>&init_info) {
  if (l+1==r) {info[p]=init_info[l];return;}
  int m=(l+r)/2;build(2*p, l, m, init_info);
  build(2*p+1, m, r, init_info);push_up(p);
 }
 void modify(int p, int l, int r, int ql, int qr, const Tag&v) {
  if (ql<=l&&r<=qr) {apply_node(p, v);return;}
  push_down(p);int m=(l+r)/2;
  if (ql<m) modify(2*p, l, m, ql, qr, v);
  if (qr>m) modify(2*p+1, m, r, ql, qr, v);
  push_up(p);
 }
 Info query(int p, int l, int r, int ql, int qr) {
  if (ql<=l&&r<=qr) {return info[p];}
  push_down(p);int m=(l+r)/2;
  if (qr<=m) return query(2*p, l, m, ql, qr);
  if (ql>=m) return query(2*p+1, m, r, ql, qr);
  return query(2*p, l, m, ql, qr)+query(2*p+1, m, r, ql, qr);
 }
 int kth(int p, int l, int r, ll k) {
  if (l+1==r) {return l;}
  push_down(p);int m=(l+r)/2;
  ll left_count=info[2*p].sum;
  if (k<=left_count) {
   return kth(2*p, l, m, k);
  } else {
   return kth(2*p+1, m, r, k-left_count);
  }
 }
public:
 LazySegmentTree(const vec<Info>&init_info) {
  n=init_info.size();info.assign(4*n, Info());
  tag.assign(4*n, Tag());
  if (n>0) build(1, 0, n, init_info);
 }
 void modify(int l, int r, const Tag&v) {
  if (l<r) modify(1, 0, n, l, r, v);
 }
 Info query(int l, int r) {
  if (l<r) return query(1, 0, n, l, r);
  return Info();
 }
 int kth(ll k) {
  if (k<1||k>info[1].sum) return-1;
  return kth(1, 0, n, k);
 }
};
