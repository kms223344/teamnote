void fact(ll n, vl& ret)
{
    if(n == 1) return;
    if(n%2 == 0)
    {
        ret.pb(2);
        fact(n/2, ret);
        return;
    }
    if(is_p(n))
    {
        ret.pb(n);
        return;
    }
    
    ll a, b, c, g = n;
    auto f = [&c, &n](ll x)->ll{return (c+(lll)x*x)%n;};
    do
    {
        if(g == n) a=b=rand()%(n-2)+2, c=rand()%20+1;
        a=f(a); b=f(f(b));
        g = gcd(a-b, n);
    }while(g == 1);
    fact(g, ret); fact(n/g, ret);
}
vl po_rho(ll n)
{
    vl ret;
    fact(n, ret);
    sort(all(ret));
    return ret;
}