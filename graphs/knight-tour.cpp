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
vpii moves;

void make_moves()
{
	for(auto x:vpii{{1, 2}, {2, 1}})
	{
		rep(i, 0, 2)
		{
			x.F = -x.F;
			rep(j, 0, 2)
			{
				x.S = -x.S;
				moves.pb(x);
			}
		}
	}

}

int ord[8][8];
int nbor[8][8];

bool stupid(int r, int c)
{
	if(ord[r][c] == 63)
		for(auto[dx, dy]: moves)
		{
			int nx = r+dx, ny = c+dy;
			if(nx >= 0 && nx <8 && ny >= 0 && ny <8 && !ord[nx][ny] )
			{
				ord[nx][ny] = 64;
				return true;
			}
		}

	for(auto[dx, dy]: moves)
	{
		int nx = r+dx, ny = c+dy;
		if(nx >= 0 && nx <8 && ny >= 0 && ny <8 && !ord[nx][ny])
		{
			ord[nx][ny] = ord[r][c]+1;
			if(stupid(nx, ny))
				return true;
			ord[nx][ny] = 0;
		}
	}
	return false;
}

int calls = 0;

bool go(int r, int c)
{
	calls++;
	if(calls > 1'000'000)
		return false;
	if(ord[r][c] == 63)
		for(auto[dx, dy]: moves)
		{
			int nx = r+dx, ny = c+dy;
			if(nx >= 0 && nx <8 && ny >= 0 && ny <8 && !ord[nx][ny] )
			{
				ord[nx][ny] = 64;
				return true;
			}
		}
	int mn = 1e9;
	for(auto[dx, dy]: moves)
	{
		int nx = r+dx, ny = c+dy;
		if(nx >= 0 && nx <8 && ny >= 0 && ny <8 && !ord[nx][ny])
			mn = min(--nbor[nx][ny], mn);
	}
	
	if(mn > 1)
		for(auto[dx, dy]: moves)
		{
			int nx = r+dx, ny = c+dy;
			if(nx >= 0 && nx <8 && ny >= 0 && ny <8 && !ord[nx][ny])
			{
				ord[nx][ny] = ord[r][c]+1;
				if(go(nx, ny))
					return true;
				ord[nx][ny] = 0;
			}
		}
	else if(mn == 1){
		for(auto[dx, dy]: moves)
		{
			int nx = r+dx, ny = c+dy;
			if(nx >= 0 && nx <8 && ny >= 0 && ny <8 && !ord[nx][ny] && nbor[nx][ny] == mn)
			{
				ord[nx][ny] = ord[r][c]+1;
				if(go(nx, ny))
					return true;
				ord[nx][ny] = 0;
			}
		}
	}
	for(auto[dx, dy]: moves)
	{
		int nx = r+dx, ny = c+dy;
		if(nx >= 0 && nx <8 && ny >= 0 && ny <8 && !ord[nx][ny])
			++nbor[nx][ny];
	}
	return false;
}

signed main()
{
	init();
	make_moves();
	int r, c; cin >> r >> c;
	r--; c--;

	swap(r, c);
	ord[r][c] = 1;
	rep(i, 0, 8)
		rep(j, 0, 8)
		{
			for(auto[dx, dy]: moves)
			{
				if(i+dx >= 0 && i+dx <8 && j+dy >= 0 && j+dy <8)
					nbor[i][j]++;
			}
		}
	if(go(r, c))
	{
		rep(i, 0, 8)
		{
			rep(j, 0, 8)
			{
				cout<<ord[i][j]<<' ';
			}
			cout<<endl;
		}
	}
	else {
		ord[r][c] = 0;
		ord[c][r] = 1;
		rep(i, 0, 8)
			rep(j, 0, 8)
			{
				nbor[i][j] = 0;
				for(auto[dx, dy]: moves)
				{
					if(i+dx >= 0 && i+dx <8 && j+dy >= 0 && j+dy <8)
						nbor[i][j]++;
				}
			}
		// cout<<"dioporco"<<endl;
		calls = 0;
		if(go(c, r))
		{
			rep(i, 0, 8)
			{
				rep(j, 0, 8)
				{
					cout<<ord[j][i]<<' ';
				}
				cout<<endl;
			}
		}
		else cout<<"diocan"<<endl;
	}
}
