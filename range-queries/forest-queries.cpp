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


int main()
{
	init();
	int n, m, q; cin >> n >> q;
	m = n;
	vvi tot(n+1, vi(m+1));
	tot[0].assign(m+1, 0);
	rep(i, 1, n+1)
	{
		int c = 0;
		tot[i][0] = 0;
		rep(j, 1, m+1)
		{
			char ch;
			cin>>ch;
			c += (ch == '*');
			tot[i][j] = tot[i-1][j]+c;
		}
	}
	rep(i, 0, q)
	{
		int up, l, dw, r;
		cin >> up >> l >> dw >> r;
		int res = tot[dw][r] - tot[up-1][r] - tot[dw][l-1] + tot[up-1][l-1];
		cout << res << endl;
	}
}
