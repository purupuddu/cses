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

// vvi dp;
// vv<bool>> vis;

// int sum_to_idx(int sum)
// {
// 	return sum + (n*(n+1))/4;
// }
// int solve(int sum, int i)
// {
// 	if (abs(sum) > n*(n+1) / 2 - i * (i+1) / 2)
// 		return 0;
// 	if (i == n)
// 		return sum == 0;
// 	int idx = sum_to_idx(sum);
// 	if (vis[idx][i])
// 		return dp[idx][i];
// 	int num = i+1;
// 	dp[idx][i] = (solve(sum-num, i+1) + solve(sum+num, i+1))%mod;
// 	vis[idx][i] = true;
// 	return dp[idx][i];
// }
int n;
int mod = 1e9+7;

int dp[2][250*251 + 100];
signed main()
{
	init();
	cin >> n;
	int last = 0, curr = 1;
	int mx = 1;
	dp[0][1] = 1;
	rep(i, 2, n+1)
	{
		memset(dp[curr], 0, sizeof(dp[curr]));
		int bound = min(mx +1, (n*(n+1) - i*(i-1))/2 + 1);
		rep(sum, 0, bound)
		{
			dp[curr][abs(sum - i)] += dp[last][sum];
			dp[curr][abs(sum - i)] %= mod;
			dp[curr][abs(sum + i)] += dp[last][sum];
			dp[curr][abs(sum + i)] %= mod;
			mx = max(mx, sum + i);
		}
		// cout<<i<<endl;
		// rep(j, 0, mx+1)
		// 	cout<<dp[curr][j]<<' ';
		// cout<<endl;
		last = !last;
		curr = !curr;
	}
	cout<<dp[last][0]<<endl;
}
