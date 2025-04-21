BOJ 트리와 쿼리 1
1 i c: i번 간선의 비용을 c로 바꾼다.
2 u v: u에서 v로 가는 단순 경로에 존재하는 비용 중에서 가장 큰 것을 출력한다.

const int N = 1e5+7;

vi adj[N]; int par[N]; int sz[N]; int d[N];
void dfs1(int s) {
    sz[s] = 1;
    for(int i=0;i<adj[s].size();i++)
        if(adj[s][i] == par[s])
            {adj[s].erase(adj[s].begin() + i); break;}
    for(auto &i : adj[s]) {
        par[i] = s; d[i] = d[s] + 1;
        dfs1(i);
        sz[s] += sz[i];
        if(sz[i] > sz[adj[s][0]]) swap(adj[s][0], i);
    }
}
int in[N], c; int top[N];
void dfs2(int s) {
    in[s] = ++c;
    for(auto i : adj[s]) {
        if(i == adj[s][0])
            top[i] = top[s];
        else top[i] = i;

        dfs2(i);
    }
}

Node *root; // Segment Tree
int query(int a,int b) {
    int ans = 0;
    while(top[a] != top[b]) {
        if(d[top[a]] > d[top[b]]) swap(a, b);
        ans = max(ans, query(root, in[top[b]], in[b]));
        b = par[top[b]];
    }

    if(d[a] > d[b]) swap(a, b);
    ans = max(ans, query(root, in[a]+1, in[b]));

    return ans;
}
map<pii, int> m;
int arr[N]; pii edge[N];
int main() {
    getint(n);
    forr(i, n-1) {
        intab; adj[a].pb(b); adj[b].pb(a);
        getint(c);
        m[{a,b}] = m[{b, a}] = c;
        edge[i] = {a,b};
    }

    dfs1(1); dfs2(1);
    forr(i, n) arr[in[i]] = m[{par[i], i}];
    root = new Node(1, n); init(root, arr);

    getint(Q);
    while(Q--) {
        getint(q);
        if(q == 1) {
            getint(i); getint(c);
            auto [a, b] = edge[i];
            if(par[b] == a) a = b;

            update(root, in[a], c, true);
        }
        if(q == 2) {
            intab;
            printf("%d\n", query(a, b));
        }
    }
}
