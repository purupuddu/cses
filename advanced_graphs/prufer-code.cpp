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

// key property of sequence S: x in S iff x not a leaf. 
// Store leaves in pq. Let x smallest leaf. It's attached to the first entry of S
// Then after removing the first entry of S, S becomes the code of tree - x -> keep solving until S empty
// length of S is n-2 => the only missing edge is the one linking the two nodes left in pq (the two leaves of the tree)
signed main()
{
	init();
	int n; cin >> n;
	vi ft(n, -1);
	vi v(n-2); cin >> v;
	vi fr(n, 0);
	for (int &x:v)
	{
		x--;
		fr[x]++;
	}
	priority_queue<int> pq;
	rep(i, 0, n)
	{
		if(fr[i] == 0)
			pq.push(-i);
	}
	for (int x:v)
	{
		int u = -pq.top(); pq.pop();
		ft[u] = x;
		fr[x]--;
		if (fr[x] == 0)
			pq.push(-x);
	}
	int a = -pq.top(); pq.pop();
	ft[a] = -pq.top();
	rep(i, 0, n)
	{
		if(ft[i] != -1)
		{
			cout<<i+1<<' '<<ft[i]+1<<endl;
		}
	}
}
