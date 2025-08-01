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
vvi gr;
int n;
vvi T;
vector<priority_queue<pii>> ptree;
void buildT(int p, int prev = -1)
{
	for(int x:gr[p])
	{
		if(x != prev)
		{
			T[p].pb(x);
			buildT(x, p);
		}
	}
}

vi leaves;
int cleaf(int p)
{
	if(ssize(T[p]) == 0)
		return leaves[p] = 1;
	leaves[p] = 0;
	for (int x :T[p])
	{
		leaves[p] += cleaf(x);
	}
	return leaves[p];
}

signed main()
{
	init();
	cin >> n;
	gr.resize(n);
	ptree.resize(n);
	leaves.resize(n);
	T.resize(n);
	rep(i, 0, n-1)
	{
		int a, b; cin >> a >> b; a--; b--;
		gr[a].pb(b);
		gr[b].pb(a);
	}
	int r = -1;
	rep(i, 0, n)
	{
		if(gr[i].size() != 1)
		{
			r = i;
			break;
		}
	}
	buildT(r);
	cleaf(r);
	rep(i, 0, n)
	{
		for (int x:T[i])
			ptree[i].push({leaves[x], x});
	}
	vpii res;
	while(leaves[r] >= 2)
	{
		// cout << "root = " << r << endl;
		while(ssize(ptree[r]) > 1)
		{
			int x = ptree[r].top().second; ptree[r].pop();
			int y = ptree[r].top().second; ptree[r].pop();
			leaves[x]--;
			leaves[y]--;
			if(leaves[x])
				ptree[r].push({leaves[x], x});
			if(leaves[y])
				ptree[r].push({leaves[y], y});
			while(ssize(ptree[x]))
			{
				int son = ptree[x].top().second; ptree[x].pop();
				leaves[son]--;
				if(leaves[son])
					ptree[x].push({leaves[son], son});
				x = son;
			}

			while(ssize(ptree[y]))
			{
				int son = ptree[y].top().second; ptree[y].pop();
				leaves[son]--;
				if(leaves[son])
					ptree[y].push({leaves[son], son});
				y = son;
			}
			res.pb({x, y});
			leaves[r] -= 2;
		}
		while(ssize(ptree[r]) == 1)
		{
			r = ptree[r].top().second;
		}
	}
	if(leaves[r] == 1)
	{
		int x = r, prev = r;
		while(ssize(gr[x]) <= 2)
		{
			int i = 0;
			if (gr[x][i] == prev)
				i++;
			prev = x;
			x = gr[x][i];
		}

		int i = 0;
		if (gr[x][i] == prev)
			i++;
		res.pb({gr[x][i], r});
	}
	
	
	cout << ssize(res) << endl;
	for (auto [x, y]:res)
	{
		cout <<x+1 << ' ' << y+1 << endl;
	}

}
