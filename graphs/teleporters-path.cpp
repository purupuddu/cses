#include<bits/stdc++.h>
using namespace std;

void init() {
	cout.precision(17);
	cin.tie(0)->sync_with_stdio(false);
	#ifndef TIE
		//freopen("input.txt", "r", stdin);
		//freopen("output.txt", "w", stdout);
	#endif
}

// #define int long long
#define all(c) begin(c), end(c)
#define rep(ind, st, end) for(int ind = st; ind<end; ind++)
#define revp(ind, end, st) for(int ind = st; ind-->end; )
#define modfor(ind, st, mod) for(int ind = st, _fl=false; ind!=st || !_fl; ind = (i+1)%mod, _fl=true)
#define ssize(c) static_cast<int>(c.size())
#define lg2(x) (__builtin_clz(1) - __builtin_clz(x))
#define pb push_back
#define F first
#define S second
#ifndef TIE
	#define endl '\n'
#endif
#define vv vector<vector
#define rdup(a, b)  (a%b ? (a/b+1) : a/b)


using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vvi = vector<vector<int >> ;
using vvll = vector<vector<ll >> ;
using vvpii = vector<vector<pii >> ;

#define binsearch(l, r, f, res) { \
	ll cpl = l, cpr = r, mid; \
	while(cpl < cpr)\
	{\
		mid = (cpl+cpr)/2; \
		if(f) cpl = mid+1; \
		else cpr = mid; \
	}\
	res = cpl-1; \
}

template<class T>
int max(const vector<T> &v) { int r = 0; rep(i, 1, ssize(v)) if(v[i]>v[r]) r = i; return r; }
template<class T>
int min(const vector<T> &v) { int r = 0; rep(i, 1, ssize(v)) if(v[i]<v[r]) r = i; return r; }
template<class T>
istream& operator >> (istream &input, vector<T>& vec) { rep(i, 0, ssize(vec)) input >> vec[i]; return input; }
template<class T>
ostream& operator << (ostream &out, const vector<T>& vec){ out << "["; rep(i, 0, ssize(vec)) out << ' ' << vec[i]; out << " ]\n"; return out; }
template<class T, size_t Z>
istream& operator >> (istream &input, array<T, Z>& vec) { rep(i, 0, ssize(vec)) input >> vec[i]; return input; }
template<class T, size_t Z>
ostream& operator << (ostream &out, const array<T, Z>& vec){ out << "["; rep(i, 0, ssize(vec)) out << ' ' << vec[i]; out << " ]\n"; return out; }
template<class A, class B>
istream& operator >> (istream &input, pair<A, B>& pp) { input >> pp.first >> pp.second; return input; }
template<class A, class B>
ostream& operator << (ostream &out, const pair<A, B>& pp) { out << "(" << pp.F << ", " << pp.S << ")"; return out; }
#define ans(x) {cout << x << endl; return 0; }

// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓


vi euler_walk(vector<vector<pair<int, int>>>& adj, int E, int src = 0, bool directed = 0) {
	int n = ssize(adj), odds = 0;
	vi indeg(n, 0);
	if(directed)
		for(auto &v: adj)
			for(auto [dest, ind]: v)
				indeg[dest]++;
	bool srcgood = (directed? indeg[src] != ssize(adj[src]) : ssize(adj[src]) % 2 == 1);
	for(int i = 0; i < n; ++i) {
		int incr = (directed? abs(ssize(adj[i]) - indeg[i]) : ssize(adj[i]) % 2);
		odds += incr;
		if(!srcgood && incr) src = i;
	}
	if(odds > 2) return {};
	vi result, inds(n, 0);
	vector<bool> used(E, 0);
	stack<int> st;
	st.push(src);
	while(st.size()) {
		int v = st.top();
		if(inds[v] == ssize(adj[v])) {
			result.push_back(v);
			st.pop();
			continue;
		}
		int ind = inds[v]++;
		auto [dst, id] = adj[v][ind];
		if(used[id]) continue;
		used[id] = true;
		st.push(dst);
	}
	if(ssize(result) != E+1) return {};
	reverse(all(result));
	return result;
}

signed main()
{
	init();
	int n, m; cin >> n >> m;
	vvpii adj(n);
	rep(i, 0, m)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		adj[a].pb({b, i});
	}
	auto res = euler_walk(adj, m, 0, true);
	if(res.empty() || res[0] != 0 || res[m] != n-1)
		ans("IMPOSSIBLE")
	for(auto x:res)
		cout<<x+1<<' ';
	cout<<endl;
}
