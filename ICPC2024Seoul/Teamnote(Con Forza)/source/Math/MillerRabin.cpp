ll pow(ll a, ll b, ll mod)
{
    ll ret = 1;
    for(int st=0; (1LL<<st) <= b; st++)
    {
        if((1LL<<st) & b) ret=(lll)ret*a%mod;
        a=(lll)a*a%mod;
    }
    return ret;
}
bool miller(ll n, ll a)
{
    if(n == a) return true;
    ll x = n-1;
    if(pow(a, x, n) != 1) return false;
    while(x%2==0)
    {
        x/=2;
        ll t = pow(a, x, n);
        if(t!=1 and t!=n-1) return false;
        if(t==n-1) return true;
    }
    return true;
}
bool is_p(ll n)
{
    if(n<=2) return n==2;
    vi D = {2, 3, 5, 7, 11, 13, 17, 23, 29, 31, 37};
    for(auto i:D) if(!miller(n, i)) return false;
    return true;
}