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
 
//#define int long long
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
 
int k1, k2;
ll tot = 0;
int calls = 0;
struct centroid
{
	int n;
	vector<vector<int>> adj;
	vi sz;
	vector<bool> rm;
	vll pref;

 
	int dfs(int p, int prev=-1)
	{
 
		sz[p] = 1;
		for(int nx:adj[p])
			if(nx!=prev && !rm[nx])
				sz[p] += dfs(nx, p);
		return sz[p];
	}
 
	int find(int p, int msz, int prev=-1)
	{
		for(int nx:adj[p])
			if(!rm[nx] && nx!=prev && sz[nx]>msz)
				return find(nx, msz, p);
		return p;
	}
 
	centroid(vector<vi> const &ad)
	{
		adj = ad;
		n = ssize(adj);
		sz.resize(n);
		rm.resize(n, 0);
		pref.resize(n+1, 0);
		deco(0);
	}
 
	vi acc, curr;
	void dpt(int p, int cdpt, int prev = -1)
	{
		if(cdpt == ssize(curr))
			curr.pb(0);
		curr[cdpt]++;
		cdpt++;
		for(int x : adj[p])
			if(x != prev && ! rm[x])
				dpt(x, cdpt, p);
	}
 
	void deco(int p) // important: in the custom visits DON'T visit nodes with rm[node] == true
	{
		int c = find(p, dfs(p)/2);
		rm[c] = true;

		int maxd = 0;
		pref[0] = 1;

		for(int x:adj[c])
		{
			curr.assign(1, 0);
			if(rm[x])
				continue;
			dpt(x, 1);
			maxd = max(maxd, ssize(curr)-1);
			rep(i, 0, ssize(curr))
			{
				tot += curr[i] * (pref[max(0, k1-i)] - pref[max(0, min(maxd, k2-i)+1)]);
			}
			ll sum = 0;
			revp(i, 0, ssize(curr))
			{
				sum += curr[i];
				pref[i] += sum;
			}
		}
		assert(sz[p] == pref[0]);
		rep(i, 0, maxd+1)
			pref[i] = 0;
		for(int x:adj[c])
			if(!rm[x])
				deco(x);
 
		// you can do bottom-up calculations here
		rm[c] = false; // for bottom-up only
	}
 
};
 
 
 
vvi adj;
 
 
 
signed main()
{
	init();
	int n; cin >> n >> k1 >> k2;
	adj.resize(n);
	rep(i, 0, n-1)
	{
		int a, b; cin >> a >> b;
		a--; b--;
		adj.at(a);
		adj.at(b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	centroid ct(adj);
	ans(tot);
}