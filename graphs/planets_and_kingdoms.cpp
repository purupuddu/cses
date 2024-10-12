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

// sets res to last n in range [l, r] s.t. f is true
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

vvi gr;
vi vis;
struct Kosaraju {
	vector<vi> adj, radj, cond_adj;
	vector<bool> vis;
	vi comp, order;
	int cc = 0;

	void init_radj() {
		int n = ssize(adj);
		radj.resize(n);
		for (int u = 0; u < n; ++u)
			for (int v : adj[u])
				radj[v].push_back(u);
	}

	void dfs1(int u) {
		vis[u] = true;
		for (int v : adj[u])
			if (!vis[v])
				dfs1(v);
		order.push_back(u);
	}

	void dfs2(int u) {
		vis[u] = true;
		comp[u] = cc;
		for (int v : radj[u])
			if (!vis[v])
				dfs2(v);
	}


	void init_cond_adj()
	{
		vector<vi> complist(cc);
		vi added(cc, -1);
		cond_adj.resize(cc);

		for(int i=0;i<ssize(adj);i++)
			complist[comp[i]].push_back(i);
		for(int i=0;i<cc;i++)
			for(int from:complist[i])
				for(int to:adj[from])
					if(comp[to] != i && added[comp[to]]!=i) {
						cond_adj[i].push_back(comp[to]);
						added[comp[to]] = i;
					}
	}

	Kosaraju(vector<vi>& g) {
		adj = g;
		init_radj();
		int n = ssize(adj);
		vis.resize(n);
		comp.resize(n);
		for (int u = 0; u < n; ++u)
			if (!vis[u])
				dfs1(u);
		vis.assign(n, false);
		reverse(all(order));
		for (int u : order)
			if (!vis[u])
				dfs2(u), ++cc;
		init_cond_adj();
	}
};


signed main()
{
	init();
	int n, m; cin >> n >> m;
	gr.resize(n);
	vis.assign(n, 0);
	rep(i, 0, m)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		gr[a].pb(b);
	}
	Kosaraju kos(gr);
	cout<<kos.cc<<endl;
	rep(i, 0, n)
		cout<<kos.comp[i]+1<<' ';

	cout<<endl;
}
