#include <bits/stdc++.h>
using namespace std;

void init()
{
#ifndef TIE
	cin.tie(0)->sync_with_stdio(false);
#endif
}

#define all(c) begin(c), end(c)
#define rep(ind, st, end) for (int ind = st; ind < end; ind++)
#define revp(ind, end, st) for (int ind = st; ind-- > end;)
#define modfor(ind, st, mod) for (int ind = st, _fl = false; ind != st || !_fl; ind = (i + 1) % mod, _fl = true)
#define ssize(c) static_cast<int>(c.size())
#define lg2(x) (__builtin_clz(1) - __builtin_clz(x))
#define pb push_back
#define F first
#define S second
#define endl '\n'
#define vv vector < vector

#define ans(x)             \
	{                      \
		cout << x << endl; \
		return 0;          \
	}

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vvi = vector<vector<int >> ;
using vvll = vector<vector<ll >> ;
using vvpii = vector<vector<pii >> ;

struct LazyST
{
	using Node = ll;
	using Update = ll;

	Node unit = Node(0);		  // s.t. for every x merge(x, unit) = x
	Update no_update = Update(0); // null update

	Node merge(Node a, Node b)
	{
		return a + b;
	}
	void update_node(Node &a, Update upd, int l, int r)
	{
		a += upd * (r - l + 1);
	}
	Update combine_updates(Update prev, Update upd)
	{
		return prev + upd;
	}

	int n;
	vector<Node> st;
	vector<Update> lz;

	LazyST(const vector<int> &data)
	{
		n = 1;
		while (n < ssize(data))
			n *= 2;
		st.assign(2 * n, unit);
		lz.assign(n, no_update);

		for (int i = 0; i < ssize(data); i++)
			st[i + n] = Node{data[i]};
		for (int i = n - 1; i > 0; i--)
			st[i] = merge(st[2 * i], st[2 * i + 1]);
	}
	void push(int u, int l, int r)
	{
		if (u >= n)
			return;
		if (lz[u] != no_update)
		{
			update_node(st[2 * u], lz[u], l, (l + r) / 2);
			update_node(st[2 * u + 1], lz[u], (l + r) / 2 + 1, r);
			if (2 * u < n)
			{
				lz[2 * u] = combine_updates(lz[2 * u], lz[u]);
				lz[2 * u + 1] = combine_updates(lz[2 * u + 1], lz[u]);
			}
			lz[u] = no_update;
		}
	}
	Node query(int u, int l, int r, int x, int y)
	{
		if (r < x || l > y)
			return unit;
		if (l >= x && r <= y)
			return st[u];
		push(u, l, r);
		return merge(
			query(2 * u, l, (l + r) / 2, x, y),
			query(2 * u + 1, (l + r) / 2 + 1, r, x, y));
	}
	void update(int u, int l, int r, int x, int y, Update v)
	{
		if (r < x || l > y)
			return;
		if (l >= x && r <= y)
		{
			update_node(st[u], v, l, r);
			if (u < n)
				lz[u] = combine_updates(lz[u], v);
		}
		else
		{
			push(u, l, r);
			update(2 * u, l, (l + r) / 2, x, y, v);
			update(2 * u + 1, (l + r) / 2 + 1, r, x, y, v);
			st[u] = merge(st[2 * u], st[2 * u + 1]);
		}
	}
	// [x, y]
	Node query(int x, int y) { return query(1, 0, n - 1, x, y); }
	void update(int x, int y, Update v) { return update(1, 0, n - 1, x, y, v); }
};

int main()
{
	init();
	int n, q;
	cin >> n >> q;
	vi v(n);
	rep(i, 0, n)
		cin >> v[i];
	LazyST st(v);
	rep(i, 0, q)
	{
		int tp; cin >> tp;
		if(tp == 1)
		{
			int l, r, val; cin >> l >> r >> val;
			st.update(l-1, r-1, val);
		}
		else 
		{
			int l; cin >> l;
			cout << st.query(l-1, l-1) << endl;
		}
	}
}
