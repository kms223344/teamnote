ll primary_root(ll p) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<ll> distrib(1, p-1);
    
    //distrib(gen);
    vl g = po_rho(p-1);
    
    while(true) {
        ll c = distrib(gen);
        
        bool ok = true; ll u = p-1;
        ll b = 1;
        for(auto i:g) {
            if(i != b) u = p-1;
            ll x = pow(c, u/i, p);
            if(x == 1) ok = false;
            u /= i; b = i;
        }
        
        if(ok) return c;
    }
}