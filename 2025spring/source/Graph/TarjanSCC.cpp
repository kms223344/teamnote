vi adj[N];
int in[N], c = 0;
stack<int> p;
bool fin[N]; int scn[N], nscc = 0;
int dfs(int s) {
    in[s] = ++c;
    p.push(s);

    int m = c;
    for(auto i : adj[s]) {
        if(in[i] == 0) m = min(m, dfs(i));
        else if(!fin[i]) m = min(m, in[i]);
    }

    if(m == in[s]) {
        nscc++;
        while(p.top() != s)
        {
            int i = p.top(); p.pop();
            scn[i] = nscc; fin[i] = true;
        }
        p.pop();
        scn[s] = nscc; fin[s] = true;
    }
    return m;
}

forr(i, n) if(!fin[i]) dfs(i);