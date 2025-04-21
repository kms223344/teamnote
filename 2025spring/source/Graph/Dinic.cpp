struct Edge {
    int to, cap, now;
    Edge* rev;
    Edge(int to,int cap):to(to), cap(cap), now(0){}
    int left(){return cap - now;}
    void flow(int f){now += f; rev->now -= f;}
    void reset(){now = 0;}
};
vector<Edge*> adj[N];

int lv[N]; bool chk[N];
bool bfs(int S, int T) {
    queue<int> q;
    q.push(S); lv[S] = 0; chk[S] = true;
    while(!q.empty()) {
        int s = q.front(); q.pop();
        for(auto i : adj[s]) {
            if(i->left() and !chk[i->to]) {
                lv[i->to] = lv[s]+1; chk[i->to] = true;
                q.push(i->to);
            }
        }
    }
    return chk[T];
}

Edge* hist[N]; int last[N];
bool dfs(int s, int T) {
    if(s == T) return true;

    for(int &j=last[s]; j < adj[s].size(); j++) {
        int i = adj[s][j]->to;
        if(adj[s][j]->left() == 0 or lv[i] != lv[s]+1) continue;
        hist[i] = adj[s][j];

        if(dfs(i, T)) return true;
    }
    return false;
}

ll flow(int S,int T) {
    ll ans = 0;
    while(bfs(S, T)) {
        while(dfs(S, T)) {
            int m = 2e9;
            int now = T;
            while(S != now) {
                m = min(m, hist[now]->left());
                now = hist[now]->rev->to;
            }
            now = T;
            while(S != now)
                hist[now]->flow(m), now = hist[now]->rev->to;
            ans += m;
        } 
        memset(last, 0, sizeof last);
        memset(chk, 0, sizeof chk);
    }
    return ans;
}
// isDir : isDirected => 양방향 간선이면 false
void connect(int from, int to, int cap, bool isDir = true) {
    Edge *fw, *bw;
    fw = new Edge(to, cap);
    bw = new Edge(from, !isDir ? cap : 0);
    fw->rev = bw; bw->rev = fw;
    adj[from].push_back(fw);
    adj[to].push_back(bw);
}