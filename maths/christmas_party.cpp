#include <bits/stdc++.h>
using namespace std;

#define rep(ind, st, end) for(int ind = st; ind < end; ind++)
using vi = vector<int>;
using ll = long long;

int mod = 1e9+7;
int dp[2][int(1e6+1)];
int solve(int first, int n)
{
	if (n <= 1)
		return 0;
	if(n == 2)
		return 1;
	if (dp[first][n])
		return dp[first][n];
	dp[first][n] = ((ll(n-1))*solve(0, n-1)) % mod;
	if(first == 0)
	{
		dp[first][n] += solve(1, n-1);
		dp[first][n] %= mod;
	}
	return dp[first][n];
}

int main()
{
	int n; cin >> n;
	cout<<solve(1, n)<<endl;
}
