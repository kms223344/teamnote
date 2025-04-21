vi adj[N]; bool cent[N];
int sz[N], par[N];

void getSz(int s){
    sz[s] = 1;
    for(auto i:adj[s]){
        if(cent[i]) continue;
        if(par[s] == i) continue;
        par[i] = s; getSz(i); par[i] = 0;
        
        sz[s] += sz[i];
    }
}
int getCent(int s, int n){
    for(auto i:adj[s])
        if(!cent[i] and sz[i] < sz[s] and sz[i] > n/2)
            return getCent(i, n);
    return s;
}

int cpar[N];
int getCentTree(int s){
    getSz(s);
    int C = getCent(s, sz[s]);    
    cent[C] = true;
    for(auto i:adj[C]){
        if(cent[i]) continue;
        int c = getCentTree(i);
        cpar[c] = C;
    }
    return C;
}

int C = getCentTree(1); cpar[C] = -1;