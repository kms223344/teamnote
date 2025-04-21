int n = 20;
vector<int> a(1 << n);

// keeps track of the sum over subsets
// with a certain amount of matching bits in the prefix
vector<vector<int>> dp(1 << n, vector<int>(n));

vector<int> sos(1 << n);
for (int mask = 0; mask < (1 << n); mask++) {
	dp[mask][-1] = a[mask];
	for (int x = 0; x < n; x++) {
		dp[mask][x] = dp[mask][x - 1];
		if (mask & (1 << x)) { dp[mask][x] += dp[mask - (1 << x)][x - 1]; }
	}
	sos[mask] = dp[mask][n - 1];
}

////////////////////////////////////////////
D[i]에 미리 i에 해당하는 값을 넣어둔다
fors(d, 0, 19) fors(i,0,(1<<20)-1)
    if(i & (1<<d)) D[i] += D[i^(1<<d)];
-> D[i] : sum of subset of mask i