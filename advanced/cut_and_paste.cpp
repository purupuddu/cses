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
#define _ << " " <<
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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vpii = vector<pii>;
using vvi = vector<vector<int >> ;
using vvll = vector<vector<ll >> ;
using vvpii = vector<vector<pii >> ;

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
template<class A, class B>
istream& operator >> (istream &input, pair<A, B>& pp) { input >> pp.first >> pp.second; return input; }
template<class A, class B>
ostream& operator << (ostream &out, const pair<A, B>& pp) { out << "(" << pp.F << ", " << pp.S << ")"; return out; }
#define ans(x) {cout << x << endl; return 0; }

// ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
mt19937 rng{42};

struct Treap {
	using Val = char;

	Val val; // Node value
	ll sum; // Query result on subtree
	bool rev; // Lazy operation to push

	int prio, sz;
	Treap *left, *right;

	Treap(Val x, Treap* l = NULL, Treap *r = NULL) {
		val = x; sz = 1; prio = (int)rng();
		left = l; right = r; rev = false; sum = 0;
	}
	~Treap() {
		if(left) delete left;
		if(right) delete right;
	}
	void recalc() {
		sz = 1;
		sum = val;
		if(left) sz += left->sz, sum += left->sum;
		if(right) sz += right->sz, sum += right->sum;
	}
	void push() {
		if(rev) {
			swap(left, right);
			if(left) left->rev ^= 1;
			if(right) right->rev ^= 1;
		}
		rev = false;
	}
};

// pos: sz of left tree
pair<Treap*, Treap*> split(Treap* u, int pos) {
	if(!u) return {NULL, NULL};
	u->push();
	Treap *t;
	int ls = u->left ? u->left->sz : 0;
	if(ls >= pos) {
		tie(t, u->left) = split(u->left, pos);
		u->recalc();
		return {t, u};
	} else {
		tie(u->right, t) = split(u->right, pos-ls-1);
		u->recalc();
		return {u, t};
	}
}
Treap *merge(Treap* left, Treap* right) {
	if(!left) return right;
	if(!right) return left;
	left->push(); right->push();
	if(left->prio < right->prio) {
		left->right = merge(left->right, right);
		left->recalc();
		return left;
	} else {
		right->left = merge(left, right->left);
		right->recalc();
		return right;
	}
}
Treap *insert(Treap* u, int pos, Treap::Val v) {
	if(u) u->push();
	auto [l, r] = split(u, pos);
	return merge(l, merge(new Treap(v), r));
}
// If val is provided, it stores the deleted value
Treap* erase(Treap* u, int pos, Treap::Val *val = NULL) {
	if(u) u->push();
	auto [l, r] = split(u, pos);
	auto [r1, r2] = split(r, 1);
	if(val) *val = r1->val;
	delete r1;
	return merge(l, r2);
}
Treap::Val find(Treap *u, int pos) {
	if(!u) return -1; // pos out of bounds
	u->push();
	int ls = u->left ? u->left->sz : 0;
	if(ls > pos) return find(u->left, pos);
	if(ls < pos) return find(u->right, pos-ls-1);
	return u->val;
}
// Perform some operation op on range [a, b]
template<typename Op>
Treap *range_operation(Treap *u, int a, int b, Op op) {
	auto [l, mr] = split(u, a);
	auto [m, r] = split(mr, b-a+1);
	op(m);
	return merge(l, merge(m, r));
}
// Execute op on each node, from left to right
template<typename Op>
void visit(Treap *u, Op op) {
	if(!u) return;
	u->push();
	visit(u->left, op);
	op(u);
	visit(u->right, op);
}


signed main()
{
	init();
	{int n; cin >> n; }
	int q; cin >> q;

	string s; cin >> s;
	Treap *t = new Treap(s[0]);
	rep(i, 1, ssize(s))
	{
		t = merge(t, new Treap(s[i]));
	}
	rep(i, 0, q)
	{
		int l, r; cin >> l >> r;
		auto [pre, str] = split(t, l-1);
		auto [cutd, post] = split(str, r-l+1);
		t = merge(merge(pre, post), cutd);
	}
	visit(t, [](Treap *tr){ cout<<tr->val;});
	cout<<endl;
	delete t;
}

