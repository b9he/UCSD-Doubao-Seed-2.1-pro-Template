// Coordinate compression: sorted distinct values, 0-based IDs.
vec<ll>values={7, 3, 7}, v=values;sort(all(v));
v.erase(unique(all(v)), v.end());
auto get_id=[&](ll x){
 return lower_bound(all(v), x)-v.begin();
};
cout<<get_id(7); // 1
// Precompute floor(log2(i)); query only i>=1.
int n=8;vi lg(n+1);
rep(i, 2, n+1)lg[i]=lg[i/2]+1;
cout<<lg[8]; // 3
// Read a whole line after >>; keep leading spaces.
int x;cin>>x;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
string line;getline(cin, line);cout<<line;
// stdin: 7\n  text\n -> line is "  text"
