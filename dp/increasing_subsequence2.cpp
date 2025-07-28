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
template<class T, size_t Z>
istream& operator >> (istream &input, array<T, Z>& vec) { rep(i, 0, ssize(vec)) input >> vec[i]; return input; }
template<class T, size_t Z>
ostream& operator << (ostream &out, const array<T, Z>& vec){ out << "["; rep(i, 0, ssize(vec)) out << ' ' << vec[i]; out << " ]\n"; return out; }
template<class T>
istream& operator >> (istream &input, vector<T>& vec) { rep(i, 0, ssize(vec)) input >> vec[i]; return input; }
template<class T>
ostream& operator << (ostream &out, const vector<T>& vec){ out << "["; rep(i, 0, ssize(vec)) out << ' ' << vec[i]; out << " ]\n"; return out; }
template<class A, class B>
istream& operator >> (istream &input, pair<A, B>& pp) { input >> pp.first >> pp.second; return input; }
template<class A, class B>
ostream& operator << (ostream &out, const pair<A, B>& pp) { out << "(" << pp.F << ", " << pp.S << ")"; return out; }

#define ans(x) {cout << x << endl; return 0; }

// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
int mod = 1e9+7;
struct SparseST {

	using Value = ll;
	using Update = ll;
	ll inf = 1e9+5;
	Value unit = Value(0);
	static const Update no_update = Update{0}; // null update

	Value merge(Value a, Value b) { return (a + b) % mod; }

	struct Vertex {
		Value val;
		int l = -1, r = -1;
		Update upd = no_update;
		Vertex(Value v, ll _sx, ll _dx) : val(v), l(_sx), r(_dx) {}
		Vertex(Value v) : val(v) {}
	};


	void update_node(Vertex& a, Update upd, ll l, ll r) {
		a.val += (upd * ((r - l + 1) % mod)) % mod;
		a.val %= mod;
	}
	Update combine_updates(Update prev, Update upd) {
		return (upd + prev) % mod;
	}

	vector<Vertex> st{Vertex{unit}};


	void push(int u, ll l, ll r) {
		if(l == r) return;
		if(st[u].l == -1) {
			st[u].l = ssize(st);
			st.push_back(Vertex(unit));
		}
		if(st[u].r == -1) {
			st[u].r = ssize(st);
			st.push_back(Vertex(unit));
		}
		if(st[u].upd != no_update) {
			update_node(st[st[u].l], st[u].upd, l, (l+r)/2);
			update_node(st[st[u].r], st[u].upd, (l+r)/2+1, r);
			if(l < r) {
				st[st[u].l].upd = combine_updates(st[st[u].l].upd, st[u].upd);
				st[st[u].r].upd = combine_updates(st[st[u].r].upd, st[u].upd);
			}
			st[u].upd = no_update;
		}
	}

	void update(int u, ll l, ll r, ll x, ll y, Update v) {
		if(r < x || y < l) return;
		if(x <= l && r <= y) {
			update_node(st[u], v, l, r);
			if(l != r)
				st[u].upd = combine_updates(st[u].upd, v);
		}
		else {
			push(u, l, r);
			update(st[u].l, l, (l+r)/2, x, y, v);
			update(st[u].r, (l+r)/2+1, r, x, y, v);
			st[u].val = merge(st[st[u].l].val, st[st[u].r].val);
		}
	}

	Value query(int u, ll l, ll r, ll x, ll y) {
		if(r < x || l > y) return unit;
		if(l >= x && r <= y)
		{
			return st[u].val;
		}
		push(u, l, r);
		return merge(
			query(st[u].l, l, (l+r)/2, x, y),
			query(st[u].r, (l+r)/2+1, r, x, y)
		);
	}

	// [x, y]
	Value query(ll x, ll y) { return query(0, 0, inf, x, y); }
	void update(ll x, ll y, Update v) { update(0, 0, inf, x, y, v); }
};

signed main()
{
	init();
	int n; cin >> n;
	vi v(n); cin >> v;
	vi seq = {-1}; // fake node
	SparseST w;
	w.update(0, 0, 1);

	for(int x:v)
	{
		w.update(x, x, w.query(0, x-1));
	}
	cout<<w.query(1, 1e9)<<endl;

}
