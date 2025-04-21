auto isunder = [](pii upper[], int u, pii x, bool inv = false){ // inv==true : isover
    int r = inv?-1:1;
    int idx = lower_bound(upper+1, upper+1+u, x, 
       [&r](pii a, pii b){return r*a.fi<r*b.fi;}) - upper;
    if(idx > u) return false;
    if(idx == 1) {
        if(r*x.fi < r*upper[1].fi) return false;
        else {
            int h = upper[1].se;
            if(upper[2].fi == upper[1].fi) h = upper[2].se;
            
            return r*x.se <= r*h;
        }
    }
    return ccw(upper[idx-1], upper[idx], x) <= 0;
};