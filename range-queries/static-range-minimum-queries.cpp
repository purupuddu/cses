#include<bits/stdc++.h>
using namespace std;

void init() {
	#ifndef TIE
		cin.tie(0)->sync_with_stdio(false);
	#endif
}

#define all(c) begin(c), end(c)
#define rep(ind, st, end) for(int ind = st;ind<end; ind++)
#define revp(ind, end, st) for(int ind = st;ind-->end;)
#define modfor(ind, st, mod) for(int ind = st, _fl=false;ind!=st || !_fl; ind = (i+1)%mod, _fl=true)
#define ssize(c) static_cast<int>(c.size())
#define lg2(x) (__builtin_clz(1) - __builtin_clz(x))
#define pb push_back
#define F first
#define S second
#define endl '\n'
#define vv vector<vector

#define ans(x) {cout<<x<<endl;return 0;}

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vvi = vector<vector<int>>;
using vvll = vector<vector<ll>>;
using vvpii = vector<vector<pii>>;

struct SparseTable {
	// Any idempotent operation
	int op(int a, int b) { return min(a, b); }

	vector<vi> tab;
	SparseTable(const vi& data) {
		tab.push_back(vi(data));
		for(int p = 0; (2<<p) <= ssize(data); ++p) {
			tab.emplace_back(data.size() - (2<<p) + 1, 0);
			for(int i = 0; i + (2<<p) <= ssize(data); i++)
				tab[p+1][i] = op(tab[p][i], tab[p][i + (1<<p)]);
		}
	}
	int query(int a, int b) { // [a, b]
		// assert(a <= b);
		int p = __builtin_clz(1) - __builtin_clz(b-a+1);
		return op(tab[p][a], tab[p][b - (1<<p) + 1]);
	}
};


int main()
{
	init();
	int n, q;
	cin>>n>>q;
	

	vi v(n);
	rep(i, 0, n)
		cin>>v[i];
	SparseTable st(v);

	rep(i, 0, q)
	{
		int l, r; cin>>l>>r;
		cout<<st.query(l-1, r-1)<<endl;
	}
	
}
