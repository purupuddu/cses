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

struct SegmentTree {
	using Node = int;
	Node unit = 1e9; // s.t. for every x merge(x, unit) = x
	Node merge(Node a, Node b) { return min(a, b); }

	int n;
	vector<Node> st;

	SegmentTree(const vector<int>& data) {
		n = 1;
		while(n < ssize(data)) n *= 2;
		st.assign(2*n, unit);
		for(int i = 0; i < ssize(data); i++) st[i+n] = Node{data[i]};
		for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]);
	}
	void update(int p, int v) {
		st[p += n] = Node{v};
		for(p /= 2; p > 0; p /= 2) st[p] = merge(st[2*p], st[2*p+1]);
		// cout<<st;
	}
	Node query(int x, int y) { // [x, y]
		Node left = unit, right = unit;
		for(x += n, y += n + 1; x < y; x /= 2, y /= 2) {
			if(x&1) left = merge(left, st[x++]);
			if(y&1) right = merge(st[--y], right);
		}
		return merge(left, right);
	}
};
// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

signed main()
{
	init();
	// freopen("test_input.txt", "r", stdin);
	int n, q; cin >> n >> q;
	vi v(n); cin >> v;
	map<int, set<int>> occur;
	
	rep(i, 0, n)
		occur[v[i]].insert(i);
	vi nx(n);
	rep(i, 0, n)
	{
		auto it = occur[v[i]].upper_bound(i);
		if(it == occur[v[i]].end())
		{
			nx[i] = 1e9;
		}
		else 
			nx[i] = *it;
	}
	// cout<<nx;
	SegmentTree st(nx);

	rep(i, 0, q)
	{
		int t, a, b; cin >> t >> a >> b;
		if (t == 1) // update
		{
			a--;
			if(v[a] == b)
				continue;
			occur[v[a]].erase(a);
			occur[b].insert(a);
			if (occur[v[a]].size() && *occur[v[a]].begin() < a)
			{
				auto prev = --occur[v[a]].upper_bound(a);
				auto next = occur[v[a]].upper_bound(a);
				if(next == occur[v[a]].end())
					st.update(*prev, 1e9);
				else st.update(*prev, *next);
			}
			if (*occur[b].begin() < a)
			{
				auto prev = --occur[b].lower_bound(a);
				st.update(*prev, a);
			}
			auto next = occur[b].upper_bound(a);
			if(next == occur[b].end())
				st.update(a, 1e9);
			else 
				st.update(a, *next);
			v[a] = b;
			// CHECK
			// for (auto &[x, setto]:occur)
			// {
			// 	for (auto y:setto)
			// 	{
			// 		assert(v[y] == x);
			// 		int res = st.query(y, y);
			// 		if(res == 1e9)
			// 		{
			// 			assert(setto.size() == 0 || setto.upper_bound(y) == setto.end());
			// 		}
			// 		else{
			// 			assert(v[res] == x);
			// 			assert(*occur[x].upper_bound(y) == res);
			// 		}
			// 	}
			// }
					
		}
		else if(st.query(a-1, b-1) <= b-1)
		{
			cout<<"NO"<<endl;
		}
		else
			cout<<"YES"<<endl;
	}


}
