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

#define int long long
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define ans(x) {cout << x << endl; return 0; }
struct LazyST {
	using Node = ll;
	
	struct Update{
		ll step, base;
		// int len;
	};

	Node unit = Node(0); // s.t. for every x merge(x, unit) = x
	Update no_update = Update{0, 0}; // null update

	Node merge(Node a, Node b) {
		return a + b;
	}
	void update_node(Node& a, Update upd, int l, int r) {
		// a += upd * (r - l + 1);
		a += upd.step * ((r-l+1) * (r-l+2) / 2) + upd.base*(r-l+1);
	}

	Update combine_updates(Update prev, Update upd) {
		return {prev.step + upd.step, prev.base + upd.base};
	}

	int n;
	vector<Node> st;
	vector<Update> lz;

	LazyST(const vector<int>& data) {
		n = 1;
		while(n < ssize(data)) n *= 2;
		st.assign(2*n, unit);
		lz.assign(n, no_update);

		for(int i = 0; i < ssize(data); i++) st[i+n] = Node{data[i]};
		for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
	}
	void push(int u, int l, int r) {
		if(u >= n) return;
		if(lz[u].step != 0 || lz[u].base != 0) {
			Update upl = lz[u];
			Update upr = {upl.step, lz[u].base + ((l+r)/2 - l + 1) * upl.step};
			
			update_node(st[2*u], upl, l, (l+r)/2);

			update_node(st[2*u+1], upr, (l+r)/2+1, r);
			if(2*u < n) {
				lz[2*u] = combine_updates(lz[2*u], upl);
				lz[2*u+1] = combine_updates(lz[2*u+1], upr);
			}
			lz[u] = no_update;
		}
	}
	Node query(int u, int l, int r, int x, int y) {
		if(r < x || l > y) return unit;
		if(l >= x && r <= y) return st[u];
		push(u, l, r);
		return merge(
			query(2*u, l, (l+r)/2, x, y),
			query(2*u+1, (l+r)/2+1, r, x, y)
		);
	}
	void update(int u, int l, int r, int x, int y, Update v) {
		if(r < x || l > y) return;
		if(l >= x && r <= y) {
			update_node(st[u], v, l, r);
			if(u < n)
				lz[u] = combine_updates(lz[u], v);
		} else {
			push(u, l, r);
			update(2*u, l, (l+r)/2, x, y, v);
			int xx = max(x, l);
			if (xx <= (l+r) / 2)
			{
				v.base += ((l+r)/2 - xx + 1) * v.step;
			}
			update(2*u+1, (l+r)/2+1, r, x, y, v);
			st[u] = merge(st[2*u], st[2*u+1]);
		}
	}
	// [x, y]
	Node query(int x, int y) { return query(1, 0, n-1, x, y); }
	void update(int x, int y, Update v) { return update(1, 0, n-1, x, y, v); }
};






// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓





signed main()
{
	init();
	int n, q; cin >> n >> q;
	vi v(n); cin >> v;
	LazyST st(v);
	rep(i, 0, q)
	{
		int t, l, r; cin >> t >> l >> r;
		l--; r--;
		if (t == 1)
		{
			st.update(l, r, {1, 0});
			// cout << st.st << endl;
			// cout.flush();
		}
		else cout << st.query(l, r) << endl;
	}
}


