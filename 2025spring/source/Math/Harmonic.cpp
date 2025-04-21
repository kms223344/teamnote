ll harmonic(ll n) {
    ll ans = 0;
    for(ll i = 1; i <= n; i = n/(n/i)+ 1) {
        //for j \in [i, n/(n/i)] : n/j == n/i
        
        ans += n/i * (n/(n/i) - i + 1);
        
        // \sum_{i=1}^n {f(n/i)}
        // ans += f(n/i) * (n/(n/i) - i + 1)
    }
    return ans;
}