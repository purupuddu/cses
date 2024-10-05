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


using Matrix = vector<vector<int>>;

Matrix mat_mul(const Matrix& a, const Matrix& b, ll mod) {
	assert(a[0].size() == b.size());

	vvi allocated(b.size(), vector<int>(b.size(), 0));
	for(int i = 0; i < ssize(allocated); i++)
		for(int j = 0; j < ssize(allocated[0]); j++)
			for(int k = 0; k < ssize(allocated[0]); k++)
				allocated[i][j] = (allocated[i][j] + ll(a[i][k]) * b[k][j]) % mod;
	return allocated;
}

vector<ll> mat_mul(const Matrix& a, const vector<ll>& b, ll mod) {
	assert(a[0].size() == b.size());

	vector<ll> res(a.size(), 0);
	for(int i = 0; i < ssize(a); i++)
		for(int j = 0; j < ssize(a[0]); j++)
			res[i] = (res[i] + a[i][j] * b[j]) % mod;
	return res;
}

Matrix mat_pow(const Matrix& b, ll e, ll mod) {
	assert(b[0].size() == b.size());

	Matrix p(b), res(b.size(), vector<int>(b.size(), 0));
	for(int i = 0; i < ssize(b); i++) res[i][i] = 1;
	for(; e; e >>= 1) {
		if(e & 1) res = mat_mul(res, p, mod);
		p = mat_mul(p, p, mod);
	}
	return res;
}


// void mat_pow_opt(const Matrix &b, ll e, ll mod) 
// {
// 	Matrix p(b), res(b.size(), vi(b.size(), 0));
// 	int n = ssize(p);
// 	rep(i, 0, )
// }

signed main()
{
	init();
	int mod = 1e9+7;
	int n, m, k; cin >> n >> m >> k;
	vvi mat(n, vi(n, 0));
	rep(i, 0, m)
	{
		int a, b; cin >> a >> b;
		mat[a-1][b-1] += 1;
	}
	cout<<mat_pow(mat, k, mod)[0][n-1]<<endl;
}
