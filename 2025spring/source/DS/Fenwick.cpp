ll tree[N];
void update(int i,ll x) {
    while(i < N) tree[i] += x, i += i&-i;
}
int query(int i) {
    ll s = 0;
    while(i) s += tree[i], i -= i&-i;
    return s;
}