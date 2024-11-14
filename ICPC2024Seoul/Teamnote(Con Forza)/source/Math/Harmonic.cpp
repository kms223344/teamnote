ll f(int n)
{
    ll ans = 0;
    for(int i = 1; i <= n; i = n/(n/i)+ 1)
        ans += (ll)(n/(n/i)-i+1)*(n/i);
    return ans;
}