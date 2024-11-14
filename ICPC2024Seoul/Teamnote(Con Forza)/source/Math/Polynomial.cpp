namespace GMS
{
    template<ll T, ll mod, ll w>
    struct Qring : public vl
    {
        using poly = Qring<T, mod, w>;
        Qring()                 : vl(1, 0){}
        Qring(ll c)             : vl(1, c){}
        Qring(ll c, int n)      : vl(n, c){}
        Qring(const vl& cp)     : vl(cp){}
        
        ll& operator[](ll idx)
        {
            if((unsigned)idx < size()) return vl::operator[](idx);
            this->resize(idx+1); return vl::operator[](idx);
        }
        ll operator[](ll idx) const
        {
            if((unsigned)idx < size()) return vl::operator[](idx);
            return 0LL;
        }
        
        void adjust()
        {
            while(size() > T) pop_back();
            while(size() > 1 and back() == 0) pop_back();
        }
        void adjust(int n){resize(n, 0);}
        
        ll operator()(ll x)
        {
            x %= mod;
            ll ret = 0;
            for(auto it=rbegin(); it!=rend(); it++)
                ret = (ret*x+*it)%mod;
            
            return ret;
        }
        
        friend poly operator%(const poly& A, int B) // remainder by x^B
        {
            poly ret(A);
            ret.resize(B, 0);
            return ret;
        }
        friend poly operator%(poly&& A, int B) // remainder by x^B
        {
            A.resize(B, 0);
            return A;
        }
        
        friend poly operator+(const poly& A, const poly& B)
        {
            int n = max(A.size(), B.size());
            poly ret(0, n);
            fors(i, 0, n-1) ret[i] = (A[i]+B[i])%mod;
            ret.adjust();
            return ret;
        }
        friend poly operator+(poly&& A, const poly& B)
        {
            int n = B.size();
            fors(i, 0, n-1) A[i] = (A[i]+B[i])%mod;
            A.adjust();
            return A;
        }
        
        friend poly operator-(const poly& A)
        {
            int n = A.size();
            poly ret(0, n);
            fors(i, 0, n-1) ret[i] = A[i]?mod-A[i]:0;
            return ret;
        }
        friend poly operator-(poly&& A)
        {
            int n = A.size();
            fors(i, 0, n-1) A[i] = A[i]?mod-A[i]:0;
            return A;
        }
        
        friend poly operator-(const poly& A, const poly& B)
        {
            int n = max(A.size(), B.size());
            poly ret(0, n);
            fors(i, 0, n-1) ret[i] = (mod+A[i]-B[i])%mod;
            ret.adjust();
            return ret;
        }
        friend poly operator-(poly&& A, const poly& B)
        {
            int n = B.size();
            fors(i, 0, n-1) A[i] = (mod+A[i]-B[i])%mod;
            A.adjust();
            return A;
        }
        
        friend poly operator*(ll x, const poly& B)
        {
            poly ret(B); x %= mod;
            for(auto &i : ret) i = (i*x)%mod;
            ret.adjust();
            return ret;
        }
        
        friend poly operator*(const poly& A, const poly& B)
        {
            poly ret(conv<mod, w>(A, B));
            // ACL : poly ret(atcoder::convolution<mod>(A, B));
            ret.adjust();
            return ret;
        }
        //friend poly operator/(const poly& A, const poly& B){return A*inv(B);}

        friend poly inv(const poly& A){return inv(A, T);}
        friend poly inv(const poly& A, int t)
        {
            assert(A[0] != 0);
            poly g = pow<mod>(A[0], mod-2);
            
            int st=1;
            while(st <= t)
            {
                st <<=1;
                g = (-A%st*g%st+2)*g%st;
            }
            g.adjust(t);
            return g;
        }
        
        friend poly diff(const poly& A)
        {
            int n = A.size();
            poly ret(0, n-1);
            forr(i, n-1) ret[i-1] = i*A[i]%mod;
            return ret;
        }
        friend poly inte(const poly& A)
        {
            static ll inv[T] = {0, };
            int n = A.size();
            poly ret(0, n+1);
            forr(i, n+1) if(inv[i] == 0) inv[i] = pow<mod>(i, mod-2);
            forr(i, n+1) ret[i] = inv[i]*A[i-1]%mod;
            return ret;
        }
        
        friend poly log(const poly& A){return log(A, T);}
        friend poly log(const poly& A, int t)
        {
            assert(A[0] == 1);
            poly ret = inte(diff(A) * inv(A, t)%t);
            ret.adjust(t);
            return ret;
        }
        
        friend poly exp(const poly& A){return exp(A, T);}
        friend poly exp(const poly& A, int t)
        {
            assert(A[0] == 0);
            
            poly g = 1;
            int st = 1;
            while(st < t)
            {
                st <<= 1;
                g = (A%st-log(g, st)+1)*g%st;
            }
            g.adjust(t);
            return g;
        }
        
        friend poly pow(const poly& A, ll b, ll t)
        {
            poly ret(A); ret.adjust();
            if(ret.size() == 1)
            {
                ret[0] = pow<mod>(ret[0], b);
                ret.adjust(t);
                return ret;
            }
            
            ll idx = 0; while(ret[idx] == 0) idx++;
            if((__int128_t) idx * b >= t) return poly(0, t);
            
            ll c = ret[idx]; ll ic = pow<mod>(ret[idx], mod-2); poly g;
            int n = ret.size();
            fors(i, idx, n-1) g[i-idx] = ret[i]*ic%mod;
            g.resize(t-idx*b);
            
            g = exp(b * log(g, t-idx*b), t-idx*b);
            c = pow<mod>(c, b);
            
            ret = poly(0, t);
            fors(i, idx*b, t-1) ret[i] = g[i-idx*b] * c % mod;
            
            return ret;
        }
        
        //Only just Polynomial, not Qring
        void rev()
        {
            int n=size();
            poly& F = *this;
            for(int i=0; i<n/2; i++) std::swap(F[i], F[n-i-1]);
        }
        friend poly div_quot(poly F, poly G)
        {
            F.adjust(); G.adjust();
            ll df = F.size(), dg = G.size();
            if(df < dg) return poly(0);
            
            F.rev(); G.rev();
            
            F.resize(df-dg+1);
            F = F * inv(G, df-dg+1);
            F.resize(df-dg+1);
            
            F.rev();
            return F;
        }
        friend poly div_rem(poly F, poly G)
                     {return F-G*div_quot(F, G);}
        
        friend poly shift(const poly& F, ll c)
        {
            ll n = F.size(); c %= mod;
            
            poly A(0, n); ll fac = 1;
            fors(i, 0, n-1) A[i] = F[i]*fac%mod, fac = fac*(i+1)%mod;
            A.rev();
            
            poly C(1, n);
            fors(i, 1, n-1) C[i] = C[i-1]*c%mod;
            
            ll facc = fac = pow<mod>(fac, mod-2)*n%mod;
            fore(i, n-1, 0) C[i] = C[i]*fac%mod, fac = fac*i%mod;
            
            poly B = C*A; B.resize(n);
            B.rev();
            
            fore(i, n-1, 0) B[i] = B[i]*facc%mod, facc = facc*i%mod;
            
            return B;
        }
        friend void calcG(vector<poly>& G, int i, int l, int r, const vl& p)
        {
            if(l == r)
            {
                ll g = p[l]?mod-p[l]:0;
                G[i] = vl({g, 1});
                return;
            }
            int mid = (l+r)/2;
            calcG(G, i*2, l, mid, p);
            calcG(G, i*2+1, mid+1, r, p);
            
            G[i] = G[i*2]*G[i*2+1];
        }
        friend void eval(const vector<poly>& G, int i, int l, int r, poly&& F, vl& ret)
        {
            if(l == r)
            {
                ret[l] = F[0];
                return;
            }
            
            int mid=(l+r)/2;
            eval(G, i*2, l, mid, div_rem(F, G[i*2]), ret);
            eval(G, i*2+1, mid+1, r, div_rem(F, G[i*2+1]), ret);
        }
        friend vl multipoint_eval(const poly& A, const vl& B)
        {
            int m = B.size();
            vector<poly> G(4*m);
            calcG(G, 1, 0, m-1, B);
            
            vl ret(m, 0);
            eval(G, 1, 0, m-1, div_rem(A, G[1]), ret);
            
            return ret;
        }
    };
}  // namespace GMS

const ll mod = 998244353, w = 3, T = 1<<20;
using poly = GMS::Qring<T, mod, w>;