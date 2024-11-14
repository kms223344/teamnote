struct dsu_pb
{
    const int N;
    vi par; stack<pair<pii, pii> > s;
     
    dsu_pb(int N):N(N), par(N)
    {
        fors(i, 0, N-1) par[i] = -1;
    }
    int root(int i)
    {
        if(par[i] < 0) return i;
        return root(par[i]);
    }
    bool join(int i, int j)
    {
        i = root(i); j = root(j);
        s.push({{i, par[i]}, {j, par[j]}});
        
        if(i == j) return false;
        
        if(-par[i] < -par[j]) swap(i, j);
        
        par[i] += par[j]; par[j] = i;
        return true;
    }

protected:
    void unjoin()
    {
        assert(!s.empty());
        auto [i, j] = s.top(); s.pop();
        
        par[i.fi] = i.se;
        par[j.fi] = j.se;
    }
};

struct dsu_pf : public dsu_pb
{    
    vector<pair<bool, pii> > st;          // fi==0 -> B type, fi==1 -> A type
    vector<pair<bool, pii> > tmp[2];
    
    int A=0, B=0;
    
    dsu_pf(int N):dsu_pb(N){}
    
    bool join(int i, int j)
    {
        st.pb({0, {i, j}}); B++;
        return dsu_pb::join(i, j);
    }
    void pop_front()
    {
        assert(!st.empty());
        if(A == 0)
        {
            forr(i, B) unjoin();
            
            A = B; B = 0;
            reverse(all(st));
            for(auto &[b, p]:st) b = 1, dsu_pb::join(p.fi, p.se);
        }
        else if(st.back().fi == false)
        {
            tmp[st.back().fi].pb(st.back()); st.pop_back();
            unjoin(); 
            
            while(tmp[0].size() != tmp[1].size() and (unsigned) A != tmp[1].size())
            {
                tmp[st.back().fi].pb(st.back());
                st.pop_back();
                unjoin();
            }
            
            for(auto i:{0, 1}) reverse(all(tmp[i]));
            for(auto i:{0, 1}) for(auto v:tmp[i]) 
                st.pb(v), dsu_pb::join(v.se.fi, v.se.se);
            
            tmp[0].clear(); tmp[1].clear();
        }
        
        A--; st.pop_back();
        unjoin();
    }
};