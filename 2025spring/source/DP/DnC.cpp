//D[t][s...e]를 구해야 하고, j의 탐색 범위는 [l, r]
void f(int t, int s, int e, int l, int r){
    if(s > e) return;
    int m = s + e >> 1;
    int opt = l;
    for(int i=l; i<=r; i++){
        if(D[t-1][opt] + C[opt][m] > D[t-1][i] + C[i][m]) opt = i;
    }
    D[t][m] = D[t-1][opt] + C[opt][m];
    f(t, s, m-1, l, opt);
    f(t, m+1, e, opt, r);
}