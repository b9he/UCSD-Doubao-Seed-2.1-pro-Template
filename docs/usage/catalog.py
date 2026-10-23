"""Concise usage contracts and examples for every printed algorithm."""
from pathlib import Path
import json,re,textwrap,hashlib,sys
sys.path.insert(0,str(Path(__file__).resolve().parent))
from cppstyle import compact_cpp
ROOT=Path(__file__).resolve().parents[2]
ENTRIES={}
def add(name,io,example,*,setup='',mode='normal',adapt=None):
    ENTRIES[name]=dict(io=io,example=example.strip(),setup=setup,mode=mode,adapt=adapt or {})

add('OrderStatisticTree.h','Input: distinct keys. insert changes t; order_of_key returns a rank and find_by_order returns an iterator (0-based).', '''Tree<int> t;t.insert(8);t.insert(10);
cout<<t.order_of_key(10); // 1
cout<<*t.find_by_order(0); // 8''')
add('HashMap.h','Input: integer keys/values. h[key] inserts or updates; find returns an iterator; h is a global table.', '''h[7]=3;auto it=h.find(7);
if(it!=h.end())cout<<it->second; // 3''')
add('LazySegmentTree.h','Input: Info array and tags. modify changes the tree, not the source array. query returns Info; kth returns an index.', '''vec<Info> a={Info(1),Info(5),Info(3)};
LazySegmentTree<Info,Tag> st(a);st.modify(0,2,Tag{2});
auto ans=st.query(0,3);
cout<<ans.sum<<' '<<ans.max_val; // 13 7
vec<Info> f={Info(1),Info(0),Info(1)};
LazySegmentTree<Info,Tag> freq(f);
cout<<freq.kth(2); // 2 (rank starts at 1)''')
add('XorBasis.h','Input: n and n integers from cin. The fragment updates basis and prints max_xor; it is not a callable struct.', '''int n=3;
// Feed cin: 1 2 3. Paste the fragment here.
// basis contains the pivots; max_xor is 3.''', mode='fragment',setup='int n=3;')
add('PersistentSegmentTree.h','Input: array, node capacity and saved roots. build/set return new root IDs; rangeSum returns a sum on inclusive [l,r].', '''PersistentSegtree st(3,100);
vec<int> a={1,2,3};int r0=st.build(a);
int r1=st.set(r0,1,9);
cout<<st.rangeSum(r0,0,2); // 6, old version
cout<<st.rangeSum(r1,0,2); // 13, new version''')
add('UnionFind.h','Input: vertex count, then unions. join mutates uf and reports whether a merge occurred; find returns a representative.', '''UF uf(4);uf.join(0,1);
cout<<uf.sameSet(0,1)<<' '<<uf.size(0); // 1 2''')
add('UnionFindRollback.h','Input: unions and saved time stamps. rollback restores uf; queries return component representatives/sizes.', '''RollbackUF uf(3);int t=uf.time();uf.join(0,1);
cout<<uf.size(0); // 2
uf.rollback(t);cout<<uf.size(0); // 1''')
add('SubMatrix.h','Input: nonempty rectangular matrix, unchanged. sum(u,l,d,r) returns the sum over rows [u,d), columns [l,r).', '''vec<vec<int>> a={{1,2},{3,4}};
SubMatrix<int> sm(a);
cout<<sm.sum(0,0,2,2); // 10''')
add('Matrix.h','Input: entries in d, a vector, or a nonnegative exponent. Operators return new matrices/vectors; operands are unchanged.', '''Matrix<ll,2> A;
A.d={{{1,1},{1,0}}};array<ll,2> x={1,0};
auto y=(A^5)*x;
cout<<y[0]<<' '<<y[1]; // 8 5''')
add('LineContainer.h','Input: lines k*x+m and query x. add mutates the container; query returns the maximum value. Query only when nonempty.', '''LineContainer lc;lc.add(2,1);lc.add(-1,4);
cout<<lc.query(3); // 7''')
add('Treap.h','Input: a root pointer and zero-based positions. split/merge/ins change links and return roots; move changes root by reference.', '''Node* root=nullptr;
root=ins(root,new Node(4),0);
root=ins(root,new Node(7),1);
auto [a,b]=split(root,1);
cout<<a->val<<' '<<b->val; // 4 7
root=merge(a,b);''')
add('FenwickTree.h','Input: size and point increments. update changes ft; query(r) returns sum [0,r). lower_bound requires nonnegative frequencies.', '''FT ft(4);ft.update(1,5);ft.update(2,3);
cout<<ft.query(3)-ft.query(1); // 8
cout<<ft.lower_bound(6); // index 2''')
add('FenwickTree2d.h','Input: x limit and ALL future update coordinates. Register with fakeUpdate, then init. update changes ft; query(x,y) sums [0,x)*[0,y).', '''FT2 ft(4);ft.fakeUpdate(1,2);ft.init();
ft.update(1,2,7);cout<<ft.query(2,3); // 7''')
add('RMQ.h','Input: a static array, unchanged. query(l,r) returns its minimum on nonempty [l,r).', '''vec<int> a={4,2,7};RMQ<int> rmq(a);
cout<<rmq.query(0,3); // 2''')
add('MoQueries.h','Input: queries [l,r). Output: answers in original query order. Implement add/del/calc for the maintained statistic; tree version toggles vertices.', '''// Range-sum callbacks: add => cur+=a[ind];
// del => cur-=a[ind]; calc => return cur.
auto ans=mo({{0,2},{1,3}});
cout<<ans[0]<<' '<<ans[1]; // 5 8 for a={2,3,5}''',mode='adapt',setup='vi a={2,3,5};int cur=0;',adapt={'void add(int ind, int end) { ... }':'void add(int ind, int end) { cur+=a[ind]; }','void del(int ind, int end) { ... }':'void del(int ind, int end) { cur-=a[ind]; }','int calc() { ... }':'int calc() { return cur; }'})

add('KMP.h','Input: text and nonempty pattern, unchanged; neither contains a nul separator. match returns zero-based match starts; pi returns prefix lengths.', '''auto ans=match("ababa","aba");
for(int i:ans)cout<<i<<' '; // 0 2''')
add('Zfunc.h','Input: string, unchanged. Returns z[i], the prefix match length at i; z[0]=0.', '''auto z=Z("ababa");cout<<z[2]; // 3''')
add('Manacher.h','Input: string, unchanged. Returns two radius arrays: even length=2*p[0][i], odd length=2*p[1][i]+1.', '''auto p=manacher("aba");
cout<<2*p[1][1]+1; // 3, centered at index 1''')
add('MinRotation.h','Input: string, unchanged by minRotation. Returns the start index; rotate must be called to change the string.', '''string s="baca";int k=minRotation(s);
rotate(s.begin(),s.begin()+k,s.end());
cout<<s; // abac''')
add('SuffixArray.h','Input: string without nul, unchanged. Read sa and lcp from the object; sa includes sentinel suffix n at index 0.', '''SuffixArray sa("aba");
for(int i:sa.sa)cout<<i<<' '; // 3 2 0 1
cout<<sa.lcp[2]; // 1''')
add('SuffixTree.h','Input: lowercase string; construction stores it in a. Read t/l/r for edges; t[node][c]=-1 means absent. N bounds the node pool.', '''// Heap allocation avoids a large local stack object.
auto st=make_unique<SuffixTree>("aba");
int child=st->t[0]['a'-'a'];
if(child!=-1)cout<<st->a.substr(st->l[child],
 st->r[child]-st->l[child]); // root edge label
// LCS helper additionally requires ALPHA=28.''')
add('Hashing.h','Input: string, unchanged. HashInterval stores prefix hashes; hashInterval(l,r) returns an H for [l,r); get() yields uint64_t.', '''string s="ababa";HashInterval h(s);
cout<<(h.hashInterval(0,3)==h.hashInterval(2,5)); // 1
cout<<h.hashInterval(0,3).get(); // numeric hash''')
add('AhoCorasick.h','Input: nonempty a..z patterns with IDs below MAXN, then text. Global ac stores the automaton. MAXN must exceed total pattern length. insert all words, init once, match texts, build_tree once, dfs(0) once; cnt[end[i]] counts overlapping matches for ID i. Duplicate words share counts. match returns false unless optional early exit is enabled. clear before reuse and reinsert queried IDs.', '''ac.insert(1,"a");ac.insert(2,"aa");ac.init();
ac.match("aaa");ac.build_tree();ac.dfs(0);
cout<<ac.cnt[ac.end[1]]<<' '<<ac.cnt[ac.end[2]]; // 3 2
ac.clear(); // next case''')
add('SAM.h','Input: a..z string shorter than MAXN. Global sam stores up to 2*MAXN states. Call init, insert every character, build_tree once, then dfs(0) once. cnt stores occurrence counts after DFS; its return is the maximum length*count over substrings occurring at least twice. Separator { requires 27 transition columns and loops. Keep sam global and allow enough stack for DFS.', '''string str="ababa";sam.init();for(char c:str)sam.insert(c);
sam.build_tree();cout<<sam.dfs(0); // 6''')
add('Trie.h','Input: lowercase a..z words. insert changes the trie; find returns the number of equal inserted words (0 if absent).', '''Trie tr;tr.insert("abc");tr.insert("abc");
cout<<tr.find("abc")<<' '<<tr.find("ab"); // 2 0''')
add('Polynomial.h','Input: coefficients a[i] for x^i. Evaluation returns a scalar; diff/divroot overwrite a (nonempty polynomial; divroot assumes a known root).', '''Poly p{{2,-3,1}};cout<<p(3); // 2
p.diff();cout<<p(3); // 3 (derivative 2*x-3)''')
add('PolyRoots.h','Input: polynomial by value and search bounds. Returns real roots; original coefficients stay unchanged. Use a nonconstant polynomial.', '''auto roots=polyRoots(Poly{{2,-3,1}},0,3);
for(double x:roots)cout<<x<<' '; // approximately 1 2''')
add('PolyInterpolate.h','Input: n distinct x values and matching y values, copied. Returns coefficients in increasing power order.', '''auto a=interpolate({0,1,2},{1,2,5},3);
cout<<a[0]<<' '<<a[2]; // approximately 1 1''')
add('BerlekampMassey.h','Input: nonempty sample sequence modulo mod, copied. Returns recurrence coefficients c[j]: s[i]=sum(c[j]*s[i-j-1]).', '''auto c=berlekampMassey({0,1,1,3,5,11});
cout<<c[0]<<' '<<c[1]; // 1 2''')
add('LinearRecurrence.h','Input: initial terms, recurrence coefficients, zero-based k; vectors are copied. Returns term k modulo mod (choose mod once).', '''cout<<linearRec({0,1},{1,1},8); // 21 % mod
// Original source test modulus is 5; PDF omits that line.''')
add('GoldenSectionSearch.h','Input: interval and unimodal function pointer. Returns the minimizing x, not the minimum value.', '''auto f=+[](double x){return (x-2)*(x-2);};
double x=gss(-5,5,f);cout<<x<<' '<<f(x); // about 2 0''')
add('HillClimbing.h','Input: starting 2D point and objective, unchanged. Returns {minimum value, minimizing point}; heuristic assumes a suitable unimodal objective.', '''auto [value,p]=hillClimb(P{0,0},[](P p){
 return (p[0]-2)*(p[0]-2)+p[1]*p[1];});
cout<<value<<' '<<p[0]; // about 0 2''')
add('Integrate.h','Input: bounds, function, and positive subdivision count. Returns an approximate integral; no caller data is overwritten.', '''double area=quad(0,1,[](double x){return x*x;});
cout<<area; // about 1/3''')
add('IntegrateAdaptive.h','Input: bounds, function and positive error tolerance. Returns approximate integral; does not mutate input bounds.', '''double area=quad(0,1,[](double x){return x*x;},1e-9);
cout<<area; // about 1/3''')
add('Simplex.h','Input: A,b,c copied into solver. solve(x) overwrites x and solver state, returning optimum; -inf infeasible, +inf unbounded. Solve once per object.', '''vvd A={{1,1},{1,0},{0,1}};
vd b={4,2,3},c={3,2},x;
LPSolver lp(A,b,c);T value=lp.solve(x);
cout<<value<<' '<<x[0]<<' '<<x[1]; // 10 2 2''')
add('Determinant.h','Input/output: square matrix a is destroyed by elimination. Return value is its determinant; pass a copy to retain the original.', '''vec<vec<double>> a={{2,1},{3,4}},copy=a;
double value=det(copy);cout<<value; // 5; a unchanged''')
add('IntDeterminant.h','Input/output: square integer matrix is destroyed. Returns determinant in [0,mod); source default mod=12345.', '''vec<vec<ll>> a={{2,1},{3,4}};
ll value=det(a);cout<<value; // 5; a is modified''')
add('SolveLinear.h','Input: A,b and x pre-sized to variable count. A,b are destroyed. Returns rank and writes a solution into x, or -1 if inconsistent (x is not a valid result).', '''vec<vd> A={{2,1},{1,-1}};vd b={5,1},x(2);
int rank=solveLinear(A,b,x);
if(rank!=-1)cout<<x[0]<<' '<<x[1]; // 2 1''')
add('SolveLinear2.h','This is a patch for SolveLinear.h, not a separate callable algorithm. After applying it, x contains unique values or the chosen undefined sentinel; A,b are destroyed.', '''// Apply the printed changes inside SolveLinear.h;
// define undefined as numeric_limits<double>::quiet_NaN().
vec<vd> A={{1,0}};vd b={2},x(2);
int rank=solveLinear(A,b,x);
cout<<x[0]; // 2; x[1] is undefined, rank=1''',mode='patch')
add('SolveLinearBinary.h','Input: bitset rows, RHS b and m<=1000. A,b are destroyed. Returns rank and writes solution bits into x, or -1 if inconsistent (x is not a valid result).', '''vec<bs> A(2);A[0].set(0);A[0].set(1);A[1].set(1);
vi b={1,0};bs x;
int rank=solveLinear(A,b,x,2);
if(rank!=-1)cout<<x[0]<<' '<<x[1]; // 1 0''')
add('MatrixInverse.h','Input/output: square A is modified in place. It contains the inverse only when returned rank equals its dimension; otherwise its contents are not a valid inverse.', '''vec<vec<double>> A={{2,0},{0,4}};
int rank=matInv(A);
if(rank==2)cout<<A[0][0]<<' '<<A[1][1]; // .5 .25''')
add('Tridiagonal.h','Input: diagonal, super/subdiagonals and RHS; arguments are copied or read-only. Returns x solving the tridiagonal system.', '''auto x=tridiagonal({2,2},{-1},{-1},{1,1});
cout<<x[0]<<' '<<x[1]; // 1 1''')
add('FastFourierTransform.h','Input: fft takes a nonempty power-of-two complex vector and overwrites it. conv reads two real coefficient vectors and returns their convolution.', '''vd a={1,2},b={3,4};auto c=conv(a,b);
for(double x:c)cout<<llround(x)<<' '; // 3 10 8''')
add('FastFourierTransformMod.h','Input: coefficient vectors in [0,M), unchanged. Returns convolution modulo template parameter M; FFT rounding bounds still apply.', '''vl a={1,2},b={3,4};auto c=convMod<1000000007>(a,b);
for(ll x:c)cout<<x<<' '; // 3 10 8''')
add('NumberTheoreticTransform.h','Input: residues modulo 998244353. ntt overwrites its power-of-two vector; conv leaves inputs unchanged and returns a new vector.', '''// Use ModPow with this same modulus and keep only ONE
// definition of mod when combining the two printed templates.
vl a={1,2},b={3,4};auto c=conv(a,b);
for(ll x:c)cout<<x<<' '; // 3 10 8''',mode='adapt-ntt')
add('FastSubsetTransform.h','Input: equal power-of-two arrays. FST(a,inv) overwrites a; conv copies arguments and returns AND convolution with the default branch.', '''vi a={1,2},b={3,4};auto c=conv(a,b);
cout<<c[0]<<' '<<c[1]; // 13 8, AND convolution''')

add('ModularArithmetic.h','Input: integers normalized modulo mod (default 17). Operators return new Mod objects; read .x. Division asserts invertibility.', '''Mod a(8),b(6);Mod sum=a+b,quotient=a/b;
cout<<sum.x<<' '<<quotient.x; // 14 7''')
add('ModInverse.h','Input: prime mod and LIM<=mod. Paste the precomputation fragment inside a function; it fills inv[1..LIM-1]. inv[0] is not defined.', '''const ll mod=7,LIM=7;
// Paste the precomputation fragment here.
cout<<inv[3]; // 5, because 3*5=1 mod 7''',mode='fragment-inverse')
add('ModPow.h','Input: base in [0,mod), nonnegative exponent. Returns base^exponent modulo the fixed mod; inputs are copied.', '''ll result=modpow(2,10);cout<<result; // 1024''')
add('ModLog.h','Input: a,b and positive m; values must avoid multiplication overflow. Returns smallest positive exponent, or -1 if no solution.', '''ll exponent=modLog(2,8,13);
cout<<exponent; // 3''')
add('ModSum.h','Input: count to, offset c, step k, modulus m>0. Returns sum of remainders; divsum returns sum of floored quotients for unsigned inputs.', '''cout<<modsum(4,1,2,5); // 1+3+0+2 = 6
cout<<divsum(4,1,2,5); // 0+0+1+1 = 2''')
add('ModMulLL.h','Input: unsigned residues and positive modulus. Returns modular product/power; arguments unchanged. Respect the long-double precision bound in Description.', '''cout<<modmul(7,8,13); // 4
cout<<modpow(2,10,13); // 10''')
add('ModSqrt.h','Input: a and odd prime p, with a a quadratic residue. Returns one root (other root is p-root); asserts if no root.', '''// Dependency needs modpow(b,e,p), i.e. the 3-argument
// version from ModMulLL.h, instead of fixed-mod ModPow.h.
ll r=sqrt(4LL,7LL);cout<<(r*r%7); // 4''',mode='adapt-sqrt')
add('MathSieve.h','Input: maximum n; constructor fills primes/spf. factorize(x) returns pairs for 1<=x<=n. Optional arrays require enabling their commented modules.', '''MathSieve sieve(1000);cout<<(sieve.spf[97]==97); // 1
for(auto [p,e]:sieve.factorize(120))
 cout<<p<<'^'<<e<<' '; // 2^3 3^1 5^1''')
add('MillerRabin.h','Input: unsigned n within the documented arithmetic range. Returns a primality boolean; no sieve initialization required.', '''cout<<isPrime(97)<<' '<<isPrime(100); // 1 0''')
add('Factor.h','Input: n>=1 within ModMulLL limits. Returns prime factors with multiplicity in arbitrary order; n is unchanged.', '''auto primes=factor(120);sort(all(primes));
for(auto p:primes)cout<<p<<' '; // 2 2 2 3 5''')
add('euclid.h','Input: a,b (use nonnegative values for a positive gcd). Returns gcd and overwrites reference outputs x,y to satisfy a*x+b*y=gcd.', '''ll x,y;ll g=euclid(30,18,x,y);
cout<<g<<' '<<(30*x+18*y); // 6 6''')
add('CRT.h','Input: two residues and positive moduli, with compatible residues modulo gcd and product <2^62. Returns the merged residue; inputs unchanged.', '''ll x=crt(2,3,3,5);cout<<x; // 8''')
add('BigInt.h','Input: nonnegative integer/string. Arithmetic returns new BigInt values; stream input overwrites the object and stream output prints decimal digits.', '''BigInt a(string("1000000000000000000")),b(7);
BigInt c=a+b;cout<<c; // 1000000000000000007
cout<<(a-b<a); // 1; subtraction requires a>=b''')
add('ContinuedFractions.h','Input: x>=0 and positive bound N. Returns numerator/denominator (p,q), each <=N; no arguments are modified.', '''auto [p,q]=approximate(3.141592653589793,1000);
cout<<p<<'/'<<q; // 355/113''')
add('FracBinarySearch.h','Input: monotone fraction predicate and bound N. Returns Frac{p,q}; f(1/1) must be true, f(0/1) may be true.', '''Frac r=fracBS([](Frac f){return 3*f.p>=f.q;},10);
cout<<r.p<<'/'<<r.q; // 1/3''')
add('Combination.h','Input: prime MOD and MAXN constants; init_comb fills global fac/invFac. C(n,m) returns a modular binomial coefficient without modifying them.', '''init_comb();cout<<C(5,2); // 10
cout<<fac[5]; // 120''')
add('IntPerm.h','Input: permutation of 0..n-1, read-only despite non-const reference. Returns a bijective integer code in [0,n!-1], not lexicographic rank.', '''vi p={0,1,2};int code=permToInt(p);
cout<<code; // 0; p is unchanged''')
add('multinomial.h','Input: nonnegative group counts, read-only. Returns the integer multinomial coefficient; intermediate arithmetic must fit ll.', '''vi counts={2,1,1};ll ways=multinomial(counts);
cout<<ways; // 12''')
add('ZeroOneBFS.h','Input: vertex count, directed 0/1 edges and source. run resets object dist/parent. Read dist[t] or get_path(t); unreachable is INF/empty.', '''ZeroOneBFS bfs(3);bfs.add_edge(0,1,0);
bfs.add_edge(1,2,1);bfs.run(0);
cout<<bfs.dist[2]; // 1
for(int v:bfs.get_path(2))cout<<v; // 012''')
add('BellmanFord.h','Input/output: nodes is overwritten with dist/prev; edges is sorted in place. inf=unreachable, -inf=reachable from a negative cycle.', '''vec<Node> nodes(3);vec<Ed> edges={{0,1,2},{1,2,-1}};
bellmanFord(nodes,edges,0);
cout<<nodes[2].dist<<' '<<nodes[2].prev; // 1 1''')
add('DifferenceConstraints.h','Difference-constraints modeling recipe using BellmanFord.h. Integer strict inequalities can subtract one. Keep reference z separate from reachability super-source S, connect S to all variables and z with zero edges, and start with fresh Node objects. Any dist==-inf means a negative cycle and infeasible constraints; otherwise dist[v]-dist[z] satisfies values relative to z=0. The included example uses b in [3,4], z=0,b=1,S=2. Edge weights use int. No cycle-vertex recovery is provided.','vec<Node>nodes(3);\nvec<Ed>edges={{1,0,-3},{0,1,4},{2,0,0},{2,1,0}};\nbellmanFord(nodes,edges,2);\nbool ok=true;for(auto&v:nodes)if(v.dist==-inf)ok=false;\ncout<<ok; // 1: constraints are feasible\nif(ok)cout<<nodes[1].dist-nodes[0].dist; // 3')
add('FloydWarshall.h','Input/output: m is the distance matrix, overwritten with shortest distances. Initialize missing arcs to inf; -inf marks negative-cycle reachability.', '''vec<vec<ll>> m={{0,2,inf},{inf,0,3},{inf,inf,0}};
floydWarshall(m);cout<<m[0][2]; // 5''')
add('TopoSort.h','Input: directed adjacency list, unchanged. Returns a topological order; size<n means a cycle (only an acyclic prefix was returned).', '''vec<vi> g={{1},{2},{}};auto order=topoSort(g);
if(sz(order)==sz(g))for(int v:order)cout<<v; // 012''')
add('Dinic.h','Directed nonnegative capacities, distinct source/sink. n is the largest vertex ID; MAXN>n and MAXM includes both arc directions plus reserved slots. init_flow resets adjacency and vis. dinic returns additional max flow and mutates residual capacities. min_cut(source) then marks the source side in vis; reset vis before repeating that traversal. Independent snippet, do not combine global names with MinCostMaxFlow.',"init_flow(3);add_edge(1,2,4);add_edge(2,3,3);\ncout<<dinic(3,1,3); // 3\nmin_cut(1);cout<<vis[1]<<' '<<vis[3]; // 1 0")
add('MinCostMaxFlow.h','Directed capacity/cost network with distinct source/sink. init_flow resets adjacency; add_edge adds a zero-capacity reverse arc with opposite cost. dinic returns {additional flow,additional cost}. Negative costs are allowed but reachable negative-cost residual cycles are unsupported; the cycle guard returns a partial result. n is the largest vertex ID. Independent snippet, separate from Dinic.',"init_flow(3);add_edge(1,2,2,3);add_edge(2,3,2,1);\nauto [flow,cost]=dinic(3,1,3);\ncout<<flow<<' '<<cost; // 2 8")
add('DinicMatching.h','Input: g[left] contains right IDs in [0,m), btoa has m slots. Each call rebuilds and overwrites the global personal Dinic network. dfsMatching returns size and fills btoa[right]=left or -1. hopcroftKarp is an alias. cover returns left IDs u and right IDs n+v; its complement is a maximum independent set. g remains unchanged.',"vec<vi>g={{0,1},{1}};vi r(2,-1);\ncout<<dfsMatching(g,r); // 2\nauto cv=cover(g,2,2);vi used(4);\nfor(int v:cv)used[v]=1;\nrep(v,0,4)if(!used[v])cout<<v<<' '; // maximum independent set")
add('GlobalMinCut.h','Input: symmetric nonnegative capacity matrix, copied. Returns {minimum cut weight, vertex IDs on one side}; requires at least two vertices.', '''vec<vi> m={{0,3,1},{3,0,2},{1,2,0}};
auto [value,side]=globalMinCut(m);cout<<value; // 3
for(int v:side)cout<<v<<' '; // cut-side vertices''')
add('GomoryHu.h','Input: N and undirected edges {u,v,capacity}, copied. Returns N-1 tree edges {u,v,cut value}; minimum along a tree path is pairwise min-cut.', '''vec<Edge> edges={{0,1,4},{1,2,3}};
auto tree=gomoryHu(3,edges);
for(auto [u,v,w]:tree)cout<<u<<' '<<v<<' '<<w<<' ';''')
add('WeightedMatching.h','Input: complete cost matrix with rows<=columns, read-only. Returns {minimum cost, match}, with match[row]=column.', '''vec<vec<ll>> cost={{1,5},{4,2}};
auto [value,match]=weightedMatching(cost);
cout<<value<<' '<<match[0]<<' '<<match[1]; // 3 0 1''')
add('GeneralMatching.h','Input: N and undirected edge pairs, read-only. Returns matched vertex pairs; randomized and dependent on modular matrix inversion.', '''vec<pii> edges={{0,1},{2,3}};
auto pairs=generalMatching(4,edges);
cout<<pairs.size(); // 2; pairs may be in either order''')
add('SCC.h','Input: one-based directed graph in mp, n<MAXN. Run tarjan(i) for every unvisited vertex. cc is the number of SCCs; belong[u] is the 1-based component ID. IDs decrease along edges between SCCs, so cc..1 is a topological order. scc vertex lists are only filled after uncommenting both push statements. Clear mp/scc and zero dfn/low/belong/timer/cc/top between cases. Independent global snippet.',"mp[1]={2};mp[2]={1,3};mp[3]={};\nfor(int i=1;i<=3;i++)if(!dfn[i])tarjan(i);\ncout<<cc<<' '<<(belong[1]==belong[2]); // 2 1")
add('EBCC.h','One-based undirected graph using paired directed arcs. Add each edge as consecutive add_edge(u,v), add_edge(v,u), preserving xor-1 reverse IDs. MAXN>n; MAXM includes both arc directions and reserved slots. Run tarjan(i,0) for unvisited vertices. bcc stores component vertices, belong maps vertices to components, cut marks both arcs of each bridge, and cc counts components. Isolated vertices are included. The commented bridge-only loop builds the component forest in mp. Reset all state between cases; independent snippet.',"add_edge(1,2);add_edge(2,1);\nadd_edge(2,3);add_edge(3,2);\nfor(int i=1;i<=4;i++)if(!dfn[i])tarjan(i,0);\ncout<<cc<<' '<<cut[2]; // 4 1, vertex 4 is isolated")
add('VBCC.h','One-based undirected graph; add both directions and ignore self-loops. MAXN>n; MAXM includes both directions and reserved slots. Run tarjan(i,true) for unvisited roots, then append isolated vertices using the supplied loop. vbcc stores vertex blocks; cut marks articulation vertices and cutcnt counts them. Root vertices are popped on return. mp reserves an optional block-cut forest. Reset all state between cases; independent snippet.',"add_edge(1,2);add_edge(2,1);\nadd_edge(2,3);add_edge(3,2);\nfor(int i=1;i<=4;i++)if(!dfn[i])tarjan(i,true);\nfor(int i=1;i<=4;i++)if(!head[i])vbcc[++cc].push_back(i);\ncout<<cc<<' '<<cutcnt; // 3 1, vertex 4 is isolated")
add('2sat.h','Comment-only 2-SAT modeling recipe, not a TwoSat class. Build the implication graph with two complementary literals per variable and run Tarjan from SCC.h. Equal SCC IDs for complementary literals mean UNSAT; otherwise choose the literal with the smaller SCC ID. Threshold encodings must include monotonicity implications between consecutive ordered thresholds. Reserve MAXN for every literal vertex.','// Build the implication graph, then use tarjan(i) from SCC.h.')
add('EulerWalk.h','Input: adjacency of {neighbor,edge ID}, edge count and start, read-only. Undirected reverse arcs share an ID. Returns vertex walk or empty if invalid.', '''vec<vec<pii>> g={{{1,0}},{{0,0}}};
auto walk=eulerWalk(g,1,0);
for(int v:walk)cout<<v; // 01''')
add('EdgeColoring.h','Input: simple undirected graph edges, copied. Returns one zero-based color per edge in original order.', '''auto colors=edgeColoring(3,{{0,1},{1,2},{2,0}});
cout<<(colors[0]!=colors[1]); // 1''')
add('MaximalCliques.h','Input: symmetric adjacency bitsets without self edges, read-only. Callback receives each maximal clique mask. Limit initial P to actual vertices.', '''vec<B> g(3);g[0][1]=g[1][0]=1;B P;
rep(i,0,3)P[i]=1;int count=0;
cliques(g,[&](B mask){++count;},P);
cout<<count; // 2: {0,1} and {2}''')
add('MaximumClique.h','Input: nonempty symmetric adjacency bitsets, copied. maxClique mutates search state and returns maximum-clique vertex IDs; call once per object.', '''vb g(3);g[0][1]=g[1][0]=1;
Maxclique solver(g);vi answer=solver.maxClique();
cout<<answer.size(); // 2''')
add('MaximumIndependentSet.h','This is a reduction, not a separate function. Build the complement without diagonal bits, then a maximum clique is an independent set of the original graph.', '''vb g(3),complement(3);g[0][1]=g[1][0]=1;
rep(i,0,3)rep(j,0,3)
 complement[i][j]=(i!=j&&!g[i][j]);
Maxclique solver(complement);auto answer=solver.maxClique();
cout<<answer.size(); // 2''',setup='#include "content/graph/MaximumClique.h"')
add('BinaryLifting.h','Input: one-based undirected tree in mp. Set MAXN>n and 2^LOGN>=n. dfs(root,0,1) fills dep and immediate parents; precompute(n) builds st; get_lca returns a vertex ID. Clear mp between cases; use HLD if memory is tight.', '''mp[1]={2,3};mp[2]={1,4};mp[3]={1};mp[4]={2};
dfs(1,0,1);precompute(4);
cout<<get_lca(4,3)<<' '<<get_lca(4,2); // 1 2''')
add('LCA.h','Input: nonempty rooted tree adjacency, root=0, unchanged. Construction fills object tables; lca(u,v) returns a vertex ID.', '''vec<vi> g={{1,2},{0,3},{0},{1}};LCA tree(g);
cout<<tree.lca(3,2); // 0''')
add('CompressTree.h','Input: LCA object and nonempty vertex subset, read-only. Returns {parent index,original vertex ID}; first item {0,root ID}.', '''vec<vi> g={{1,2},{0},{0}};LCA lca(g);
auto small=compressTree(lca,vi{1,2});
for(auto [parent,id]:small)cout<<parent<<':'<<id<<' ';
// 0:0 0:1 0:2''')
add('HLDLazyAdapter.h','Input: coordinate interval [l,r). Adapter stores values initially -1e9. add mutates it, query returns a maximum.', '''HLDCompat::Node st(0,3);st.add(0,3,1000000000);
st.add(1,3,5);cout<<st.query(0,3); // 5''')
add('HLD.h','Input: nonempty undirected tree, copied; root 0. Path updates mutate the internal tree. Query methods return maxima. Values start at -1e9; edge mode excludes the LCA.', '''vec<vi> g={{1},{0,2},{1}};HLD<false> hld(g);
hld.modifyPath(0,2,1000000000); // initialize to zero
hld.modifyPath(1,2,5);
cout<<hld.queryPath(0,2)<<' '<<hld.querySubtree(1); // 5 5''')
add('DSUOnTree.h','Input: one-based undirected tree in mp and colors in val. Set MAXN>n and compress colors into [0,MAXN). dfs1 computes sizes/heavy children; dfs_dsu fills ans[u] with the distinct-color count in each subtree. Use keep=false at the root to clear counters, or reset color/diff before reuse; clear mp between cases. Independent snippet with global names.', '''mp[1]={2,3};mp[2]={1};mp[3]={1};
val[1]=val[2]=1;val[3]=2;
dfs1(1,0);dfs_dsu(1,0,false);
cout<<ans[1]<<' '<<ans[2]; // 2 1''')
add('LinkCutTree.h','Input: vertex count then link/cut operations, mutating the forest. connected returns a boolean; link requires disconnected endpoints and cut requires an existing edge.', '''LinkCut forest(3);forest.link(0,1);forest.link(1,2);
cout<<forest.connected(0,2); // 1
forest.cut(1,2);cout<<forest.connected(0,2); // 0''')
add('DirectedMST.h','Input: n, root r and directed {a,b,weight} edges, read-only. Returns {total weight,parent IDs}, or {-1,empty} if impossible; root parent is -1.', '''vec<Edge> edges={{0,1,2},{0,2,5},{1,2,1}};
auto [weight,parent]=dmst(3,0,edges);
cout<<weight<<' '<<parent[2]; // 3 1''')
add('CentroidDecomposition.h','Input: global adj; size is_removed/subtree_size first. build marks all vertices removed and runs the marked callback location; it does not return or store a decomposition tree.', '''adj={{1},{0,2},{1}};
is_removed.assign(3,false);subtree_size.resize(3);
int c=get_centroid(0,get_subtree_size(0));cout<<c; // 1
// Put answer/parent bookkeeping at the marked callback.
build_centroid_decomp();''')
add('Point.h','Input: coordinates and other points, unchanged by arithmetic. Operators return points; dot/cross/dist2 return scalars. Read coordinates from .x/.y.', '''Point<ll> a(1,2),b(3,4);auto c=a+b;
cout<<c.x<<' '<<c.y<<' '<<a.dot(b); // 4 6 11''')
add('lineDistance.h','Input: distinct line endpoints a,b and point p, unchanged. Returns signed perpendicular distance, positive on the left of a->b.', '''using P=Point<double>;
cout<<lineDist(P(0,0),P(2,0),P(1,3)); // 3''')
add('SegmentDistance.h','Input: segment endpoints and query point, unchanged. Returns nonnegative shortest distance, including degenerate segments.', '''cout<<segDist(P(0,0),P(2,0),P(3,1)); // sqrt(2)''')
add('SegmentIntersection.h','Input: four segment endpoints, unchanged. Returns 0/1/2 points for no intersection, a point, or overlap endpoints. Use floating points for noninteger crossings.', '''using P=Point<double>;
auto pts=segInter(P(0,0),P(2,2),P(0,2),P(2,0));
if(!pts.empty())cout<<pts[0]; // (1,1)''')
add('lineIntersection.h','Input: two infinite lines, unchanged. Returns {status,point}: 1 unique, 0 parallel disjoint, -1 coincident. Point is meaningful only for status 1.', '''using P=Point<double>;
auto [status,p]=lineInter(P(0,0),P(2,2),P(0,2),P(2,0));
if(status==1)cout<<p; // (1,1)''')
add('sideOf.h','Input: directed line s->e and query p, unchanged. Returns 1/0/-1 for left/on/right; optional eps is distance tolerance.', '''using P=Point<ll>;
cout<<sideOf(P(0,0),P(2,0),P(1,1)); // 1''')
add('OnSegment.h','Input: segment endpoints and point, unchanged. Returns boolean, including endpoints; exact equality is intended for integer coordinates.', '''using P=Point<ll>;
cout<<onSegment(P(0,0),P(2,0),P(1,0)); // 1''')
add('linearTransformation.h','Input: p0,p1 mapped to q0,q1, plus query r; p0!=p1. Returns the transformed point; all inputs unchanged.', '''P out=linearTransformation(P(0,0),P(1,0),
 P(2,3),P(4,3),P(0,1));cout<<out; // (2,5)''')
add('Angle.h','Input: nonzero integer direction and full-turn count t. Angle operations return new objects; ordering compares unwrapped angles.', '''Angle a(1,0),b(0,1);cout<<(a<b); // 1
Angle c=a.t90();cout<<c.x<<' '<<c.y; // 0 1''')
add('CircleIntersection.h','Input: centers/radii plus output pointer. Returns success and writes *out only on success; equal coincident circles assert.', '''pair<P,P> pts;
if(circleInter(P(0,0),P(2,0),1,1,&pts))
 cout<<pts.first; // (1,0), tangent point repeated''')
add('CircleTangents.h','Input: centers/radii, unchanged; negate second radius for internal tangents. Returns pairs of tangency points, one per common tangent.', '''using P=Point<double>;
auto lines=tangents(P(0,0),1,P(4,0),1);
cout<<lines.size(); // 2 external tangents
cout<<lines[0].first<<' '<<lines[0].second;''')
add('CirclePolygonIntersection.h','Input: circle center/radius and a CCW polygon (copied). Returns signed intersection area; clockwise order reverses its sign.', '''vec<P> p={P(0,0),P(2,0),P(2,2),P(0,2)};
cout<<circlePoly(P(1,1),10,p); // 4''')
add('circumcircle.h','Input: three noncollinear points, unchanged. ccCenter returns the circumcenter and ccRadius its radius.', '''P a(0,0),b(2,0),c(0,2);
cout<<ccCenter(a,b,c)<<' '<<ccRadius(a,b,c);
// (1,1), approximately 1.41421''')
add('MinimumEnclosingCircle.h','Input: nonempty point vector by value (copy is shuffled). Returns {center,radius}; original point order is retained.', '''vec<P> p={P(0,0),P(2,0)};
auto [center,radius]=mec(p);
cout<<center<<' '<<radius; // (1,0) 1''')
add('InsidePolygon.h','Input: polygon and query point, read-only. Returns membership; strict=false includes the boundary, strict=true excludes it.', '''vec<P> p={P(0,0),P(2,0),P(2,2),P(0,2)};
cout<<inPolygon(p,P(1,1)); // 1
cout<<inPolygon(p,P(0,1),false); // 1''')
add('PolygonArea.h','Input: nonempty cyclic polygon vertex list, read-only. Returns twice the signed area; positive CCW, negative CW.', '''using P=Point<ll>;
vec<P> p={P(0,0),P(2,0),P(0,2)};
cout<<polygonArea2(p); // 4; area is 2''')
add('PolygonCenter.h','Input: cyclic polygon vertices with nonzero signed area, unchanged. Returns its area centroid as a point.', '''vec<P> p={P(0,0),P(2,0),P(2,2),P(0,2)};
P center=polygonCenter(p);cout<<center; // (1,1)''')
add('PolygonCut.h','Input: polygon and directed cut line, unchanged. Returns a new polygon after removing the left side (keeps the right side).', '''vec<P> p={P(0,0),P(2,0),P(2,2),P(0,2)};
auto kept=polygonCut(p,P(1,-1),P(1,3));
cout<<kept.size(); // 4, right half of the square''')
add('HalfPlaneIntersection.h','Input: SnippetHPI::HLine boundaries, legal side left. Function sorts/overwrites lines and returns polygon vertices. Only bounded nondegenerate cases are supported by this original snippet.', '''using namespace SnippetHPI;
vec<HLine> h={{Point(0,0),Point(1,0)},
 {Point(1,0),Point(1,1)},{Point(1,1),Point(0,1)},
 {Point(0,1),Point(0,0)}};
auto polygon=halfPlaneIntersection(h);
cout<<polygon.size(); // 4''')
add('ConvexHull.h','Input: integer points by value, original unchanged. Returns convex-hull vertices CCW, without duplicate closing vertex or collinear edge-interior points.', '''vec<P> p={P(0,0),P(2,0),P(0,2),P(0,0)};
auto hull=convexHull(p);cout<<hull.size(); // 3''')
add('HullDiameter.h','Input: nonempty CCW convex hull, copied. Returns the two farthest points; squared distance comes from their difference.', '''vec<P> h={P(0,0),P(2,0),P(2,2),P(0,2)};
auto pair=hullDiameter(h);
cout<<(pair[0]-pair[1]).dist2(); // 8''')
add('PointInsideHull.h','Input: nonempty strictly convex CCW hull, query point, strict flag; unchanged. Returns membership, with boundary included only if strict=false.', '''vec<P> h={P(0,0),P(2,0),P(2,2),P(0,2)};
cout<<inHull(h,P(1,1)); // 1
cout<<inHull(h,P(0,1),false); // 1''')
add('LineHullIntersection.h','Input: infinite line and strictly convex CCW polygon, read-only. Returns edge/vertex indices as specified in Description; {-1,-1} means no hit.', '''using P=Point<ll>;
vec<P> h={P(0,0),P(2,0),P(2,2),P(0,2)};
auto hit=lineHull(P(-1,1),P(3,1),h);
cout<<hit[0]<<' '<<hit[1]; // intersected edge indices''')
add('ClosestPair.h','Input: at least two integer points, copied and sorted internally. Returns the closest pair of point values, not original indices.', '''auto [a,b]=closest(vec<P>{P(0,0),P(1,0),P(9,9)});
cout<<(a-b).dist2(); // 1''')
add('kdTree.h','Input: nonempty point list, copied into tree. nearest(p) returns {squared distance,point}; the point itself is eligible by default.', '''vec<P> p={P(0,0),P(5,0)};KDTree tree(p);
auto [d,q]=tree.nearest(P(1,0));
cout<<d<<' '<<q; // 1 (0,0)''')
add('FastDelaunay.h','Input: distinct integer points, copied. Returns a flat vertex list in groups of three, each group one CCW triangle; empty if no triangles.', '''vec<P> p={P(0,0),P(2,0),P(0,2)};
auto triangles=triangulate(p);
cout<<triangles.size()/3; // 1''')
add('PolyhedronVolume.h','Input: 3D points and outward-oriented faces with fields a,b,c, unchanged. Returns signed volume; reversing all faces reverses the sign.', '''using P=Point3D<double>;struct Face{int a,b,c;};
vec<P> p={P(0,0,0),P(1,0,0),P(0,1,0),P(0,0,1)};
vec<Face> f={{0,2,1},{0,1,3},{0,3,2},{1,2,3}};
cout<<signedPolyVolume(p,f); // 1/6''',setup='#include "content/geometry/Point3D.h"')
add('Point3D.h','Input: coordinates and vectors, unchanged. Arithmetic returns new vectors; dot/dist2 return scalars. Read .x/.y/.z.', '''Point3D<double> a(1,0,0),b(0,1,0);
auto c=a.cross(b);cout<<c.x<<' '<<c.y<<' '<<c.z;
// 0 0 1''')
add('3dHull.h','Input: at least four 3D points, read-only, with no four coplanar. Returns faces F with original indices a,b,c and outward normal q.', '''vec<P3> p={P3(0,0,0),P3(1,0,0),P3(0,1,0),P3(0,0,1)};
auto faces=hull3d(p);cout<<faces.size(); // 4
for(auto f:faces)cout<<f.a<<' '<<f.b<<' '<<f.c<<' ';''')
add('sphericalDistance.h','Input: longitudes f, polar angles t from the +z axis, and radius, all in radians. Returns shortest surface distance; arguments unchanged.', '''double pi=acos(-1.0);
cout<<sphericalDistance(0,pi/2,pi/2,pi/2,1);
// pi/2, a quarter of the unit-circle circumference''')

add('IntervalContainer.h','Input/output: set of disjoint [L,R) intervals is mutated by add/remove; add returns the merged-interval iterator (end if empty). Touching intervals merge.', '''set<pii> intervals;addInterval(intervals,1,4);
addInterval(intervals,3,7);removeInterval(intervals,2,5);
for(auto [l,r]:intervals)cout<<l<<','<<r<<' ';
// 1,2 5,7''')
add('IntervalCover.h','Input: target [L,R) and candidate intervals, copied. Returns original interval indices in greedy covering order; empty for failure or empty target.', '''vec<pii> intervals={{0,2},{1,4},{2,3}};
auto ids=cover(pii{0,4},intervals);
for(int i:ids)cout<<i<<' '; // 0 1''')
add('ConstantIntervals.h','Input: integer domain [from,to), monotone f and callback g(l,r,value). Returns void; results are emitted through the callback.', '''vec<tuple<int,int,int>> runs;
constantIntervals(0,6,[](int i){return i/2;},
 [&](int l,int r,int v){runs.emplace_back(l,r,v);});
for(auto [l,r,v]:runs)cout<<l<<','<<r<<':'<<v<<' ';
// 0,2:0 2,4:1 4,6:2''')
add('TernarySearch.h','Input: inclusive integer interval and unimodal objective. Returns a maximizing index, not the maximum objective value.', '''auto f=[](int x){return -(x-3)*(x-3);};
int pos=ternSearch(0,10,f);
cout<<pos<<' '<<f(pos); // 3 0''')
add('LIS.h','Input: sequence, unchanged. Returns increasing-subsequence indices, not the values. Current comparison is strictly increasing.', '''vec<int> a={3,1,2,5};auto ids=lis(a);
for(int i:ids)cout<<a[i]<<' '; // 1 2 5''')
add('FastKnapsack.h','Input: nonnegative weights and target, copied. Returns maximum achievable sum <=target, not a subset reconstruction.', '''cout<<knapsack(vi{3,5,7},10); // 10''')
add('DigitDP.h','Generic digit-DP recipe. Customize MAX_STATE, initial_state, boundary_return_val, lead_zero_state, lead_first_digit_state, next_state, and optional invalid_condition. State must determine all future transitions. count_valid(x) counts accepted numbers in [0,x], with the treatment of zero chosen by the boundary result; negative x returns zero. Count [L,R] by subtracting prefix counts. Memo is reset for each bound. The example adapter uses one state and counts positive integers.', '''// Customize all state placeholders first.
long long L=1,R=100;
cout<<count_valid(R)-count_valid(L-1);''',mode='adapt',setup='const int MAX_STATE=1,initial_state=0;',adapt={'boundary_return_val':'!is_lead','lead_zero_state':'0','lead_first_digit_state':'0','next_state':'0'})
add('KnuthDP.h','This is a recurrence/optimization recipe, not a callable function. Store interval DP and optimal split positions; the answer is the full interval entry.', '''// For merging piles w={1,2,3}, initialize dp[i][i]=0.
// cost(l,r)=sum(w[l..r]); try k from opt[l][r-1]
// through opt[l+1][r], respecting l<=k<r.
// dp[l][r]=min(dp[l][k]+dp[k+1][r]+cost(l,r)).
// Output dp[0][2]=9, by merging 1+2 before 3.''',mode='recipe')
add('DivideAndConquerDP.h','Input: customized lo/hi/f and an index range [L,R). solve overwrites results via store; the printed dp/res are user-supplied globals. Optimal split indices must be monotone.', '''// Example: set dp[i][k]=(i-k)*(i-k), 0<=k<i;
// res stores {best split,best cost}.
DP solver;solver.solve(1,4);
cout<<res[3].first<<' '<<res[3].second; // 2 1''',mode='adapt-dp')
add('FastMod.h','Input: nonzero fixed divisor, then unsigned dividends. reduce returns a remainder possibly plus divisor; normalize once to get a%b.', '''FastMod fm(7);auto r=fm.reduce(100);
if(r>=fm.b)r-=fm.b;cout<<r; // 2''')
add('FastInput.h','Input: integer tokens from stdin. readInt consumes input and returns an int; call only when another token exists (not an EOF iterator).', '''int a=readInt(),b=readInt();
cout<<a+b; // stdin: 12 -5 => 7''')
add('BumpAllocator.h','Input: new allocations use the global fixed buffer. Returns object pointers; delete does not reclaim space. Install once per program, with suitable alignment for allocated types.', '''int* p=new int(7);cout<<*p; // 7
// delete p does not restore the allocation cursor.''')
add('SmallPtr.h','Input: pointers allocated inside BumpAllocator buffer. Stores an offset; dereference/arrow access the original object; zero offset denotes null.', '''ptr<int> p=new int(7);
if(p)cout<<*p; // 7''')
add('BumpAllocatorSTL.h','Input: container allocations use a shared fixed arena. The container exposes ordinary STL output; deallocate does not reclaim arena space.', '''vec<int,small<int>> a;a.push_back(7);
cout<<a[0]; // 7
// Keep total allocation below the arena size.''')
add('SIMD.h','Input: packed SIMD registers or short arrays. Helpers return scalars/registers; the example dot-product reads arrays without changing them. Requires x86 AVX2.', '''mi v=_mm256_set1_epi32(3);
cout<<sumi32(v); // 24
short a[2]={1,5},b[2]={2,3};
cout<<example_filteredDotProduct(2,a,b); // 2''',mode='x86')
add('Random.h','Input: v, inclusive bounds L/R and positive mod, defined before the fragment. shuffle changes v; rand_val/simple_rand are scalar outputs. Seed is fixed.', '''vec<int> v={1,2,3};int L=1,R=10,mod=7;
// Paste the fragment here, inside the function.
cout<<rand_val; // in [1,10]
for(int x:v)cout<<x<<' '; // shuffled permutation''',mode='fragment-random')
add('Timer.h','Input: current clock and timeLimit. Fragment returns no value; its timeout branch exits the process. Put it inside your search loop and print the saved answer at the marked location.', '''int best=42;
// Keep start/timeLimit outside the loop; refresh now inside.
// At the marked timeout location, print best before exit(0).
cout<<best; // current best answer, e.g. 42''',mode='fragment-timer')
# The printed reference sections are intentionally independent snippets.
REFERENCES={
 'template.cpp':dict(io='Common GNU C++17 preamble. Put input and output inside main; define ll/vec before copying templates that use them.',example='''int n;cin>>n; // read input, e.g. 5
cout<<n*n; // output 25'''),
 '.bashrc':dict(io='Shell configuration fragment, sourced by Bash. Commands affect the shell or compile/run a file; terminal output contains diagnostics/program output.',example='''source ~/.bashrc
# Run the aliases/functions shown below in that shell.'''),
 '.vimrc':dict(io='Vim configuration fragment. Sourcing changes editor settings/mappings, not the C++ program output.',example='''# In Vim, source the file with :source ~/.vimrc
# Use the mappings shown below while editing a C++ file.'''),
 'hash.sh':dict(io='Shell filter: C++ source arrives on stdin; stdout is its normalized short hash. This is separate from algorithm inputs/outputs.',example='''sh content/contest/hash.sh < solution.cpp'''),
 'troubleshoot.txt':dict(io='Manual debugging checklist, not executable code. Review it against the current program and failing input.',example='''# Compare expected/actual output on a minimal failing case.
# Check the listed overflow, bounds and initialization cases.'''),
 'techniques.txt':dict(io='Technique index, not an executable template. Choose the relevant technique, then use its algorithm template.',example='''# For offline connectivity with undo, use RollbackUF:
RollbackUF uf(3);int t=uf.time();uf.join(0,1);
cout<<uf.size(0); // 2
uf.rollback(t);cout<<uf.size(0); // 1'''),
}

def active_headers():
    paths=[]
    for chapter in sorted((ROOT/'content').glob('*/chapter.tex')):
        for line in chapter.read_text().splitlines():
            m=re.match(r'\s*\\kactlimport\{([^}]+\.h)\}',line)
            if m:paths.append(chapter.parent/m[1])
    return paths

# Corrections found by reading the source interfaces.
ENTRIES['KnuthDP.h']['mode']='normal'
ENTRIES['KnuthDP.h']['example']='''// Small recurrence example; restrict k using opt for Knuth.
ll dp[3][3]={},pref[4]={0,1,3,6};
for(int len=2;len<=3;++len)for(int l=0;l+len<=3;++l){
 int r=l+len-1;dp[l][r]=LLONG_MAX;
 for(int k=l;k<r;++k)dp[l][r]=min(dp[l][r],
  dp[l][k]+dp[k+1][r]+pref[r+1]-pref[l]);
}
cout<<dp[0][2]; // 9'''

# Narrative belongs in Description; Usage keeps code and short result notes.
DESCRIPTION_OVERRIDES=json.loads((ROOT/'docs/usage/descriptions.json').read_text())
USAGE_OVERRIDES={'XorBasis.h': 'int n=3; // cin: 1 2 3\n// Paste fragment here.\n// output: 3', 'MoQueries.h': "auto ans=mo({{0,2},{1,3}});\ncout<<ans[0]<<' '<<ans[1]; // 5 8 for a={2,3,5}", 'SuffixTree.h': 'auto st=make_unique<SuffixTree>("aba");\nint child=st->t[0][\'a\'-\'a\'];\nif(child!=-1)cout<<st->a.substr(st->l[child],\n st->r[child]-st->l[child]); // root edge label', 'LinearRecurrence.h': 'cout<<linearRec({0,1},{1,1},8); // 21 % mod', 'SolveLinear2.h': 'vec<vd> A={{1,0}};vd b={2},x(2);\nint rank=solveLinear(A,b,x);\ncout<<x[0]; // 2; x[1] is undefined, rank=1', 'NumberTheoreticTransform.h': "vl a={1,2},b={3,4};auto c=conv(a,b);\nfor(ll x:c)cout<<x<<' '; // 3 10 8", 'ModInverse.h': 'const ll mod=7,LIM=7;\n// Paste fragment here.\ncout<<inv[3]; // 5, because 3*5=1 mod 7', 'ModSqrt.h': 'll r=sqrt(4LL,7LL);cout<<(r*r%7); // 4', 'BigInt.h': 'BigInt a(string("1000000000000000000")),b(7);\nBigInt c=a+b;cout<<c; // 1000000000000000007\ncout<<(a-b<a); // 1', 'Dinic.h': "init_flow(3);add_edge(1,2,4);add_edge(2,3,3);\ncout<<dinic(3,1,3); // 3\nmin_cut(1);cout<<vis[1]<<' '<<vis[3]; // 1 0", 'MinCostMaxFlow.h': "init_flow(3);add_edge(1,2,2,3);add_edge(2,3,2,1);\nauto [flow,cost]=dinic(3,1,3);\ncout<<flow<<' '<<cost; // 2 8", 'GeneralMatching.h': 'vec<pii> edges={{0,1},{2,3}};\nauto pairs=generalMatching(4,edges);\ncout<<pairs.size(); // 2', 'CentroidDecomposition.h': 'adj={{1},{0,2},{1}};\nis_removed.assign(3,false);subtree_size.resize(3);\nint c=get_centroid(0,get_subtree_size(0));cout<<c; // 1\nbuild_centroid_decomp();', 'sphericalDistance.h': 'double pi=acos(-1.0);\ncout<<sphericalDistance(0,pi/2,pi/2,pi/2,1);\n// pi/2', 'KnuthDP.h': 'll dp[3][3]={},pref[4]={0,1,3,6};\nfor(int len=2;len<=3;++len)for(int l=0;l+len<=3;++l){\n int r=l+len-1;dp[l][r]=LLONG_MAX;\n for(int k=l;k<r;++k)dp[l][r]=min(dp[l][r],\n  dp[l][k]+dp[k+1][r]+pref[r+1]-pref[l]);\n}\ncout<<dp[0][2]; // 9', 'DivideAndConquerDP.h': "DP solver;solver.solve(1,4);\ncout<<res[3].first<<' '<<res[3].second; // 2 1", 'BumpAllocator.h': 'int* p=new int(7);cout<<*p; // 7', 'BumpAllocatorSTL.h': 'vec<int,small<int>> a;a.push_back(7);\ncout<<a[0]; // 7', 'Random.h': "vec<int> v={1,2,3};int L=1,R=10,mod=7;\n// Paste fragment here.\ncout<<rand_val; // in [1,10]\nfor(int x:v)cout<<x<<' '; // shuffled permutation", 'Timer.h': 'int best=42;\ncout<<best; // 42'}

USAGE_OVERRIDES['LazySegmentTree.h']="""vec<Info> a={Info(1),Info(5),Info(3)};
LazySegmentTree<Info,Tag> st(a);
st.modify(0,2,Tag{2}); // add 2 to [0,2)
auto ans=st.query(0,3);
cout<<ans.sum<<' '<<ans.max_val; // 13 7
vec<Info> f={Info(1),Info(0),Info(1)};
LazySegmentTree<Info,Tag> freq(f);
cout<<freq.kth(2); // index: 2 (rank starts at 1)"""
add('Utf8Split.h','Valid UTF-8 string; returns one string per code point.',r'''auto parts=split_utf8("A\u4E2D\U0001F60A");
cout<<parts.size()<<' '<<parts[1].size(); // 3 3''')
add('LineProjectionReflection.h','Line endpoints and point; returns projection or reflection.', '''using P=Point<double>;P a(0,0),b(2,0),p(1,3);
cout<<lineProj(a,b,p); // (1,0)
cout<<lineProj(a,b,p,true); // (1,-3)''')
add('CircleLine.h','Circle center/radius and line endpoints; returns intersection points.', '''using P=Point<double>;
auto pts=circleLine(P(0,0),1,P(-2,0),P(2,0));
for(P p:pts)cout<<p; // (-1,0)(1,0)''')
USAGE_OVERRIDES['Trie.h']='''Trie tr;tr.insert("abc");tr.insert("abc");
cout<<tr.find("abc")<<' '<<tr.find("ab"); // 2 0
cout<<tr.countPrefix("ab"); // 2'''
USAGE_OVERRIDES['Zfunc.h']='''string pat="aba",s="ababa";auto z=Z(pat+'#'+s);
rep(i,0,sz(s))cout<<z[sz(pat)+1+i]<<' '; // 3 0 3 0 1'''
USAGE_OVERRIDES['Manacher.h']='''string s="abba";auto p=manacher(s);int start=0,len=0;
rep(z,0,2)rep(i,0,sz(p[z])) {
 int k=2*p[z][i]+z;
 if(k>len)len=k,start=i-p[z][i];
}
cout<<s.substr(start,len); // abba'''
USAGE_OVERRIDES['CRT.h']='''ll a=2,m=6,b=8,n=9;
if((a-b)%gcd(m,n))cout<<-1;
else cout<<crt(a,m,b,n)<<' '<<lcm(m,n); // 8 18'''
USAGE_OVERRIDES['HLD.h']='''vec<vi>g={{1},{0,2},{1}};HLD<false>hld(g);
hld.modifyPath(0,2,1000000000); // initialize to zero
hld.modifyPath(1,2,5);
cout<<hld.queryPath(0,2)<<' '<<hld.querySubtree(1); // 5 5
hld.tree->add(hld.pos[1],hld.pos[1]+hld.siz[1],2);
cout<<hld.querySubtree(1); // 7, subtree add above
vi rev(3);rep(v,0,3)rev[hld.pos[v]]=v;
cout<<rev[hld.pos[2]]; // 2, inverse DFS order'''
add('GeometryExtras.h','Bisector, incircle and circular-segment area.', '''auto [a,b]=perpen(P(0,0),P(2,0));cout<<a; // (1,0)
auto [c,r]=incircle(P(0,0),P(4,0),P(0,3));
cout<<c<<' '<<r; // (1,1) 1
cout<<circularSegmentArea(2,acos(-1.0)); // 2*pi''')
USAGE_OVERRIDES['OrderStatisticTree.h']='''Tree<int> t;t.insert(8);t.insert(10);
cout<<t.order_of_key(10); // 1
cout<<*t.find_by_order(0); // 8
Tree<pii> ms;ms.insert({8,0});ms.insert({8,1});
cout<<ms.order_of_key({8,INT_MIN}); // 0, strictly less
cout<<ms.find_by_order(1)->first; // 8, second copy'''
USAGE_OVERRIDES['euclid.h']='''ll a=6,b=9,c=3,x,y;ll g=euclid(a,b,x,y);
if(c%g)cout<<-1;
else { // ax+by=c; here a,b>0
 ll step=b/g;
 x=(__int128)x*(c/g)%step;x=(x+step)%step;
 if(!x)x+=step;
 y=(c-(__int128)a*x)/b;
 cout<<x<<' '<<y; // 2 -1; smallest positive x
}'''
USAGE_OVERRIDES['FenwickTree.h']='''FT ft(5);ft.update(2,7);
cout<<ft.query(3); // 7, sum on [0,3)
FT diff(5);diff.update(1,4);diff.update(4,-4);
cout<<diff.query(3); // 4, value at index 2 after [1,4)+=4'''
for name,example in USAGE_OVERRIDES.items():ENTRIES[name]['example']=example

def apply():
    paths=active_headers()
    assert len(paths)==len(ENTRIES)
    assert {p.name for p in paths}==set(ENTRIES)
    before={}
    for p in paths:
        text=p.read_text();head,body=text.split('*/',1)
        before[str(p.relative_to(ROOT))]=hashlib.sha256(body.encode()).hexdigest()
        e=ENTRIES[p.name]
        lines=compact_cpp(e['example']).splitlines()
        usage=' * Usage:\n'+'\n'.join(' * '+line for line in lines)+'\n'
        pattern=r'(?m)^[ \t]*\* Usage:.*?(?=^[ \t]*\* (?:Author|Date|License|Source|Description|Usage|Time|Memory|Status|Details):|\Z)'
        head,n=re.subn(pattern,'',head,flags=re.S)
        if p.name in DESCRIPTION_OVERRIDES:
            value=DESCRIPTION_OVERRIDES[p.name]
            description=' * Description: '+value.replace('\n','\n * ')+'\n'
            dpat=r'(?m)^[ \t]*\* Description:.*?(?=^[ \t]*\* (?:Author|Date|License|Source|Usage|Time|Memory|Status|Details):|\Z)'
            head,count=re.subn(dpat,lambda match:description,head,flags=re.S)
            assert count==1,p
        # Insert before Time/Status with a stable metadata boundary.
        at=re.search(r'(?m)^\s*\* (?:Time|Status):',head)
        pos=at.start() if at else len(head.rstrip())
        head=head[:pos].rstrip()+'\n'+usage+head[pos:].lstrip('\n')
        p.write_text(head.rstrip()+'\n */'+body)
        assert p.read_text().split('*/',1)[1]==body
    (ROOT/'build/usage-body-hashes.json').write_text(json.dumps(before,indent=2))
    (ROOT/'docs/usage/reference.json').write_text(json.dumps(REFERENCES,indent=2)+'\n')
    print('Updated Usage for all',len(paths),'active algorithm templates; implementation bodies unchanged.')

if __name__=='__main__':apply()
