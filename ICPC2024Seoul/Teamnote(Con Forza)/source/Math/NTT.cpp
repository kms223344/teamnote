namespace GMS
{
    template<ll mod>
    ll pow(ll a, ll b)
    {
        static_assert(mod <= (ll)2e9, "mod should be less than 2e9");
        a %= mod;
        ll ret = 1;
        while(b != 0)
        {
            if(b&1) ret = ret*a%mod;
            a = a*a%mod; b>>=1;
        }

        return ret;
    }
    template<ll mod, ll w>
		void ntt(vector<ll> &a, bool inv = false)
    {
        static_assert(mod <= (ll)2e9, "mod should be less than 2e9");
        int n = a.size(), j = 0;
        
        assert((n & -n) == n);
        assert((mod-1)%n == 0);

        for(int i=1; i<n; i++)
        {
            int bit = (n >> 1);
            while(j >= bit){
                j -= bit;
                bit >>= 1;
            }
            j += bit;
            if(i < j) swap(a[i], a[j]);
        }
        
        static vector<ll> root[30], iroot[30];
        for(int st=1; (1<<st) <= n; st++)
        {
            if(root[st].empty())
            {
                ll t = pow<mod>(w, (mod-1)/(1<<st));
                
                root[st].pb(1);
                for(int i=1; i<(1<<(st-1)); i++)
                    root[st].pb(root[st].back()*t%mod);
            }
            if(iroot[st].empty())
            {
                ll t = pow<mod>(w, (mod-1)/(1<<st));
                t = pow<mod>(t, mod-2);
                
                iroot[st].pb(1);
                for(int i=1; i<(1<<(st-1)); i++)
                    iroot[st].pb(iroot[st].back()*t%mod);
            }
        }
        
        vector<ll>* r = (inv?root:iroot);
        
        for(int st = 1; (1<<st) <= n; st++)
        {
            int i = 1<<st; //int step = n / i;
            for(int j=0; j<n; j+=i)
            {
                for(int k=0; k<i/2; k++)
                {
                    ll u = a[j+k], v = a[j+k+i/2] * r[st][k]%mod;
                    a[j+k] = (u+v)%mod;
                    a[j+k+i/2] = (mod+u-v)%mod;
                }
            }
        }
        if(inv)
        {
            ll in = pow<mod>(n, mod-2);
            for(int i=0; i<n; i++) a[i] = a[i]*in%mod;
        }
    }
    
    template<ll mod, ll w>
    vl conv(vl A, vl B)
    {
        int n = A.size(), m = B.size();
        int t = 1; while(t < n+m-1) t*=2;
        A.resize(t); B.resize(t);

        ntt<mod, w>(A); ntt<mod, w>(B);

        fors(i, 0, t-1) A[i] = A[i]*B[i]%mod;
        
        ntt<mod, w>(A, true);
        A.resize(n+m-1);
        
        return A;
    }
} // namespace GMS