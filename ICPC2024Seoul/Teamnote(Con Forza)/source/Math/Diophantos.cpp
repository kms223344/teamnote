pll diophantos(ll a, ll b)
{
    assert(a>0 and b>=0);
    if(b == 0) return {1, 0};
    auto [y, x] = diophantos(b, a%b); y = y-(a/b)*x;
    if(x < 0 or x >= b)
    {
        ll t = x/b;
        if(x%b < 0) t--;

        x -= b*t; y += a*t;
    }
    return {x, y};
}