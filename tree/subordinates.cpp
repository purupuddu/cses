#include<bits/stdc++.h>
using namespace std;

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

void init()
{
	#ifndef TIE
		cin.tie(0)->sync_with_stdio(false);
	#endif
}

vvi gr;
vi sz;
int dfs(int p)
{
	for(int x:gr[p])
		sz[p] += dfs(x);
	return sz[p]+1;
}
int main()
{
	init();
	int n;
	cin>>n;
	gr.resize(n);
	sz.resize(n);
	rep(i, 1, n)
	{
		int t;
		cin>>t;
		t--;
		gr[t].pb(i);
	}
	dfs(0);
	rep(i, 0, n)
		cout<<sz[i]<<' ';

}
