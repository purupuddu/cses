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
struct SuffixArray {
	vi sa, rank, lcp;
	SuffixArray(const string& s) {
		int n = ssize(s) + 1, cl = 256;
		vi c(n), cn(n), pn(n), cnt(max(n,cl));
		iota(pn.begin(), pn.end(), 0);
		sa = rank = c;
		for(int i = 0; i < n-1; i++) c[i] = s[i];

		for(int k = 0; k <= n; k = k ? 2*k : 1) {
			if(k) for(int i = 0; i < n; i++) pn[i] = (sa[i]-k+n)%n;
			for(int i = 0; i < cl; i++) cnt[i] = 0;
			for(int i = 0; i < n; i++) cnt[c[pn[i]]]++;
			for(int i = 1; i < cl; i++) cnt[i] += cnt[i-1];
			for(int i = n-1; i >= 0; i--) sa[--cnt[c[pn[i]]]] = pn[i];

			cn[sa[0]] = 0; cl = 1;
			for(int i = 1; i < n; i++) {
				if(c[sa[i]] != c[sa[i-1]] || c[(sa[i]+k)%n] != c[(sa[i-1]+k)%n])
					cl++;
				cn[sa[i]] = cl - 1;
			}
			if(cl == n) break;
			c.swap(cn);
		}
		lcp.assign(n-1, 0);
		for(int i = 0; i < n; i++) rank[sa[i]] = i;
		for(int i = 0, k = 0; i < n-1; i++, k = max(0, k-1)) {
			int j = sa[rank[i]-1];
			while(s[i+k] == s[j+k]) k++;
			lcp[rank[i]-1] = k;
		}
	}
};

signed main()
{
	init();
	string s; cin >> s;
	s += '~';
	int n = ssize(s);
	SuffixArray sa(s);
	int q; cin >> q;
	int start = n;
	rep(i, 0, q)
	{
		string pat; cin >> pat;
		int l = 0, r = n;
		while(l < r)
		{
			int mid = (l + r) / 2;
			int start_pos = sa.sa[mid];
			int cmp = strncmp(pat.c_str(), s.c_str()+start_pos, pat.size());
			if(cmp <= 0)
			{
				r = mid;
			}
			else l = mid+1;
		}
		start = l;
		l = 0, r = n;
		pat[ssize(pat) - 1]++;
		while(l < r)
		{
			int mid = (l + r) / 2;
			int start_pos = sa.sa[mid];
			int cmp = strncmp(pat.c_str(), s.c_str()+start_pos, pat.size());
			if(cmp <= 0)
			{
				r = mid;
			}
			else l = mid+1;
		}
		int end = l;
		cout << end - start << endl;
	}

}
