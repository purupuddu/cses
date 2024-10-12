#include<bits/stdc++.h>
using namespace std; 

void init() {
	#ifndef TIE
		cin.tie(0)->sync_with_stdio(false); 
	#endif
}

#define all(c) begin(c), end(c)
#define rep(ind, st, end) for(int ind = st; ind<end; ind++)
#define revp(ind, end, st) for(int ind = st; ind-->end; )
#define modfor(ind, st, mod) for(int ind = st, _fl=false; ind!=st || !_fl; ind = (i+1)%mod, _fl=true)
#define ssize(c) static_cast<int>(c.size())
#define lg2(x) (__builtin_clz(1) - __builtin_clz(x))
#define pb push_back
#define F first
#define S second
#define endl '\n'
#define vv vector<vector

#define ans(x) {cout << x << endl; return 0; }

using ll = long long; 
using pii = pair<int, int>; 
using pll = pair<ll, ll>; 
using vi = vector<int>; 
using vll = vector<ll>; 
using vpii = vector<pii>; 
using vvi = vector<vector<int >> ; 
using vvll = vector<vector<ll >> ; 
using vvpii = vector<vector<pii >> ; 

struct SegmentTree {
	using Node = int; 
	Node unit = Node(0); // s.t. for every x merge(x, unit) = x
	Node merge(Node a, Node b) { return a + b; }

	int n; 
	vector<Node> st; 

	SegmentTree(const vector<int>& data) {
		n = 1; 
		while(n < ssize(data)) n *= 2; 
		st.assign(2*n, unit); 
		for(int i = 0; i < ssize(data); i++) st[i+n] = Node{data[i]}; 
		for(int i = n-1; i > 0; i--) st[i] = merge(st[2*i], st[2*i+1]); 
	}
	void update(int p, int v) {
		st[p += n] = Node{v}; 
		for(p /= 2; p > 0; p /= 2) st[p] = merge(st[2*p], st[2*p+1]); 
	}
	Node query(int x, int y) { // [x, y]
		Node left = unit, right = unit; 
		for(x += n, y += n + 1; x < y; x /= 2, y /= 2) {
			if(x&1) left = merge(left, st[x++]); 
			if(y&1) right = merge(st[--y], right); 
		}
		return merge(left, right); 
	}

	bool cmp(Node nd, int k) {
		return nd >= k;  // condition we want on result of lower_bound(k)
	}
	int lower_bound(int k)
	{
		if(!cmp(st[1], k))
			return -1; 
		int p = 1; 
		Node part = unit; 
		while(p < n)
		{
			p <<= 1; 
			if(!cmp(merge(part, st[p]), k)) {
				part = merge(part, st[p++]); 
			}
		}
		return p - n; 
	}

}; 

int main()
{
	init(); 
	int n; cin >> n;
	vi v(n); 
	rep(i, 0, n)
		cin >> v[i]; 
	SegmentTree st(vi(n, 1)); 

	rep(i, 0, n)
	{
		int ind; cin >> ind;
		ind = st.lower_bound(ind);
		cout << v[ind] << ' ';
		st.update(ind, 0);
	}

}
