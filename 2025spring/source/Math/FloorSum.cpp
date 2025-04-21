ll floor_sum(ll a, ll b, ll c, ll n)
{
    if(a == 0) return b/c*n;
    if(a>=c or b>=c) return n*(n-1)/2 * (a/c) + n * (b/c) + floor_sum(a%c, b%c, c, n);
    ll m = (a*(n-1)+b)/c;
    return m*n - floor_sum(c, c-b+a-1, a, m);
}