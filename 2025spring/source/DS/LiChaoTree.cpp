struct Line
{
    ll a=0, b=(ll)2e18+7;
    ll operator()(ll x){return a*x+b;}
    Line():a(0),b((ll)2e18+7){}
    Line(ll a, ll b):a(a), b(b){}
};

ll middle(ll s, ll e){return (s+e+(ll)2e18)/2-(ll)1e18;}
struct Node {
    Node *l=0, *r=0;
    Line v;
    Node():l(0), r(0), v(Line()){}
};
void insert(Node* node, Line v, ll l, ll r, ll s, ll e) {
    ll mid=middle(s, e);
    if(e < l or r < s) return;
    if(s == e) {
        node->v = (node->v(s) < v(s))?node->v:v;
        return;
    }
    if(!node->l) node->l = new Node();
    if(!node->r) node->r = new Node();

    if(l <= s and e <= r) {
        if(node->v(s) >= v(s) and node->v(e) >= v(e)){node->v = v; return;}
        if(node->v(s) <= v(s) and node->v(e) <= v(e)) return;
        insert(node->l, v, l, r, s, mid);
        insert(node->r, v, l, r, mid+1, e);
    }
    else {
        insert(node->l, v, l, r, s, mid);
        insert(node->r, v, l, r, mid+1, e);
    }
}
ll query(Node* node, ll x, ll s, ll e)
{
    if(!node) return (ll)2e18+7;
    if(x < s or e < x) return (ll)2e18+7;
    if(s == e) return node->v(x);

    ll mid = middle(s, e);
    return min({query(node->l, x, s,mid), query(node->r, x, mid+1, e), node->v(x)});
}
// 전체 구간을 미리 고정해 놓아야 함.
// (const int L = -1e9, R = 1e9);
// Insert : insert(root, Line 객체, l, r, L, R);
// Query : query(root, x, L, R);
int main() {
    Node *root = new Node();
    getint(n); getint(Q);
    forr(i, n) {
        getll(l); getll(r); getll(a); getll(b);
        insert(root, Line(a,b), l,r-1,(ll)-1e9-7, (ll)1e9+7);
    }
    while(Q--) {
        getint(q);
        if(q == 0) {
            getll(l); getll(r); getll(a); getll(b);
            insert(root, Line(a,b), l,r-1,(ll)-1e9-7, (ll)1e9+7);
        }
        if(q == 1) {
            getll(x);
            ll ans = query(root, x,(ll)-1e9-7, (ll)1e9+7);
            if(ans == (ll)2e18+7) printf("INFINITY\n");
            else printf("%lld\n", ans);
        }
    }
}