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
#define ith_bit(n, i) (((n)>>(i))&1)


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

struct PersistentST {
	using Value = ll;
	Value unit = Value(0);
	Value merge(Value a, Value b) { return a + b; }

	struct Vertex {
		const Value val;
		int sx = -1, dx = -1;
		Vertex(Value v, int _sx, int _dx) : val(v), sx(_sx), dx(_dx) {}
		Vertex(Value v) : val(v) {}
	};

	int n;
	vector<Vertex> st;
	vector<int> roots;

	PersistentST(const vector<int>& data) {
		n = ssize(data);
		roots.push_back(build(0, n-1, data));
	}
	template<typename... Args> int alloc(Args... args) {
		st.emplace_back(args...);
		return ssize(st) - 1;
	}
	int build(int l, int r, const vector<int>& data) {
		if(l == r) return alloc(Value{data[l]});
		int sx = build(l, (l+r)/2, data);
		int dx = build((l+r)/2+1, r, data);
		return alloc(merge(st[sx].val, st[dx].val), sx, dx);
	}
	int update(int u, int l, int r, int p, int v) {
		if(r < p || l > p) return u;
		if(l == r) return alloc(Value{v});
		else {
			int sx = update(st[u].sx, l, (l+r)/2, p, v);
			int dx = update(st[u].dx, (l+r)/2+1, r, p, v);
			return alloc(merge(st[sx].val, st[dx].val), sx, dx);
		}
	}
	Value query(int u, int l, int r, int x, int y) {
		if(r < x || l > y) return unit;
		if(l >= x && r <= y) return st[u].val;
		return merge(
			query(st[u].sx, l, (l+r)/2, x, y),
			query(st[u].dx, (l+r)/2+1, r, x, y)
		);
	}
	void update(int ver, int p, int v) { roots[ver] = update(roots[ver], 0, n-1, p, v); }
	Value query(int ver, int x, int y) { return query(roots[ver], 0, n-1, x, y); }
	void duplicate(int ver) { roots.push_back(roots[ver]); }
};



signed main()
{
	init();
	int n, q; cin >> n >> q;
	vi v(n); cin >> v;
	PersistentST st(v);
	rep(i, 0, q)
	{
		int t, k;
		cin >> t >> k;
		k--;
		if(t == 1)
		{
			int a, x; cin >> a >> x;
			a--;
			st.update(k, a, x);
		}
		if(t == 2)
		{
			int a, b; cin >> a >> b;
			a--; b--;
			cout << st.query(k, a, b) <<endl;
		}
		if(t == 3)
		{
			st.duplicate(k);
		}
	}
}
