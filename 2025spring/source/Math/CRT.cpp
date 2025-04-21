pll crt(pll p, pll q) {
    if(p.fi > q.fi) swap(p, q);
    auto [a, A] = p;
    auto [b, B] = q;

    ll g = gcd(A, B);
    if((b-a)%g != 0) return {-1, -1};
    
    ll i = A, j = B, k = b-a;
    i/=g; j/=g; k/=g;
    auto [x, y] = diophantos(i, j);
    return {(ll)((a+(lll)A*k*x)%(A*B/g)), A*B/g};
}