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


struct SegmentTree {
	using Node = int;
	Node unit = Node(-1e9); // s.t. for every x merge(x, unit) = x
	Node merge(Node a, Node b) { return max(a, b); }

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
	}
	Node query(int x, int y) { // [x, y]
		Node left = unit, right = unit;
		for(x += n, y += n + 1; x < y; x /= 2, y /= 2) {
			if(x&1) left = merge(left, st[x++]);
			if(y&1) right = merge(st[--y], right);
		}
		return merge(left, right);
	}
	// Optional features start here
	// condition on result of lower_bound(k)
	bool cmp(Node nd, int k) { return nd >= k; } 
	// Returns lowest i such that cmp(query(0, i), k) is true 
	// (or -1 if such i does not exist) in O(log N).
	// Only works where binary searching cmp(query(0, i), k) would work, but it's faster
	int lower_bound(int k) {
		if(!cmp(st[1], k))
			return -1;
		int p = 1;
		Node part = unit;
		while(p < n)
		{
			p <<= 1;
			if(!cmp(merge(part, st[p]), k)) {
				part = merge(part, st[p++]);
			}
		}
		return p - n;
	}
};



struct hld
{
	vi parent, depth, heavy, head, pos;
	vector<vi> adj;
	int cur_pos;

	SegmentTree seg{{}};

	int dfs(int v)
	{
		int size = 1;
		int mx = 0;
		for (int c : adj[v]) {
			if (c != parent[v]) {
				parent[c] = v;
				depth[c] = depth[v] + 1;
				int sub_s = dfs(c);
				size += sub_s;
				if (sub_s > mx)
					mx = sub_s, heavy[v] = c;
			}
		}
		return size;
	}

	void decompose(int v, int h)
	{
		head[v] = h, pos[v] = cur_pos++;
		if (heavy[v] != -1)
			decompose(heavy[v], h);
		for (int c : adj[v]) {
			if (c != parent[v] && c != heavy[v])
				decompose(c, c);
		}
	}

	hld(vector<vi> const& ad, vector<int> w, int root = 0)
	{
		adj = ad;
		int n = ssize(ad);
		parent = vi(n);
		depth = vi(n);
		heavy = vi(n, -1);
		head = vi(n);
		pos = vi(n);
		cur_pos = root;
		dfs(root);
		decompose(root, root);
		vi data(n);
		for(int i=0;i<n;i++)
			data[pos[i]] = w[i];
		seg = SegmentTree(data);
	}

	// update is kinda the same, so consider copying and changing what's different
	SegmentTree::Node query(int a, int b)
	{
		auto res = seg.unit;
		while(head[a] != head[b])
		{
			if(depth[head[a]] > depth[head[b]])
				swap(a, b);
			res = seg.merge(res, seg.query(pos[head[b]], pos[b]));
			b = parent[head[b]];
		}

		// query on vertices
		if(depth[a] > depth[b])
			swap(a, b);
		return seg.merge(res, seg.query(pos[a], pos[b]));

		// query on edges
		if(a == b)
			return res;
		if(depth[a] > depth[b])
			swap(a, b);
		return seg.merge(res, seg.query(pos[heavy[a]], pos[b]));
	}

	void update(int a, int v)
	{
		seg.update(pos[a], v);
	}
};




signed main()
{
	init();
	int n; cin >> n;
	int q; cin >> q;
	vi v(n); cin >> v;
	vvi gr(n);
	rep(i, 0, n-1)
	{
		int a, b; cin >> a >> b; a--; b--;
		gr[a].pb(b);
		gr[b].pb(a);
	}
	hld h(gr, v);
	rep(i, 0, q)
	{
		int t; cin >> t;
		if(t == 1)
		{
			int s, x; cin >> s >> x; s--;
			h.update(s, x);
		}
		else 
		{
			int a, b; cin >> a >> b;
			a--; b--;
			cout << h.query(a, b) << ' ';
		}
	}
}
