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


vector<string> mat;


vpii moves = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m; 

void dists(queue<pii> & q, vvi &dists) 
{
	vvi vis(n, vi(m, 0));
	while(!q.empty())
	{
		auto [x, y] = q.front(); q.pop();
		if(vis[x][y])
			continue;
		vis[x][y] = 1;
		for(auto [dx, dy] : moves)
		{
			int nx = dx+x, ny = dy+y;
			if(nx < 0 || ny < 0 || nx >= n || ny >= m || mat[nx][ny] == '#' || dists[nx][ny] <= dists[x][y])
				continue;
			dists[nx][ny] = dists[x][y]+1;
			q.push({nx, ny});
		}
	}
}

vvi dm;
vvi d;
vvi vis;
string res = "";
bool escape(int x, int y)
{
	if(dm[x][y] <= d[x][y] || vis[x][y])
		return false;
	if(x == 0 || x == n-1 || y == 0 || y == m-1)
		return true;
	vis[x][y] = true;

	rep(i, 0, 4)
	{
		auto[dx, dy] = moves[i];
		if(escape(x+dx, y+dy))
		{
			res += ("DURL"[i]);
			return true;
		}
	}
	return  false;
}
signed main()
{
	init();
	cin >> n >> m;
	mat.resize(n); cin >> mat;
	dm.assign(n, vi(m, 1e9));
	d.assign(n, vi(m, 1e9));
	vis.assign(n, vi(m, 0));
	queue<pii> q;
	int x, y; 
	rep(i, 0, n)
		rep(j, 0, m)
		{
			if(mat[i][j] == 'A')
				x = i, y = j;
			if(mat[i][j] == 'M')
			{
				dm[i][j] = 0;
				q.push({i, j});
			}
		}
	dists(q, dm);
	q.push({x, y});
	d[x][y] = 0;
	dists(q, d);
	if(!escape(x, y))
		ans("NO")
	cout<<"YES\n";
	reverse(all(res));
	cout<<ssize(res)<<endl<<res<<endl;
}
