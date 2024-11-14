struct Edge
{
    int to, cap, now;
    ll cost;
    Edge* rev;
    Edge(int to,int cap, ll cost)
        :to(to), cap(cap), now(0), cost(cost){}
    int left(){return cap - now;}
    ll flow(int f)
        {now += f; rev->now -= f; return cost * f;}
    void reset(){now = 0;}
};
vector<Edge*> adj[N];
Edge* hist[N]; ll dist[N]; bool inQueue[N], chk[N];
bool spfa(int s, int t)
{
    memset(dist, 0, sizeof(dist));
    memset(chk, 0, sizeof(chk)); chk[s] = true;

    queue<int> q;
    memset(inQueue, 0, sizeof(inQueue));
    q.push(s); inQueue[s] = true;

    while(!q.empty())
    {
        int now = q.front();
        q.pop(); inQueue[now] = false;

        for(auto e : adj[now])
        {
            int next = e->to;
            if(e->left() > 0 and
                  (chk[next] == false
                         or dist[next] > dist[now] + e->cost))
            {
                chk[next] = true;
                dist[next] = dist[now] + e->cost;
                hist[next] = e;
                if(!inQueue[next])
                    q.push(next), inQueue[next] = true;
            }
        }
    }
    return chk[t];
}
// cost가 들어가면 항상 단방향만 가능하다. (양방향 : 2번 connect)
void connect(int from, int to, int cap, ll cost)
{
    Edge *fw, *bw;
    fw = new Edge(to, cap, cost);
    bw = new Edge(from, 0, -cost);
    fw->rev = bw; bw->rev = fw;
    adj[from].push_back(fw);
    adj[to].push_back(bw);
}
//maximum matching & minimum cost
pair<ll, ll> flow(int S,int T)
{
    ll ans = 0; ll cost = 0;
    while(spfa(S, T))
    {
        int m = 2e9;

        int now = T;
        while(S != now)
        {
            m = min(m, hist[now]->left());
            now = hist[now]->rev->to;
        }
        now = T;
        while(S != now)
        {
            cost += hist[now]->flow(m);
            now = hist[now]->rev->to;
        }
        ans += m;
    }
    return {ans, cost};
}