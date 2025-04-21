using cpx = complex<double>;
using vcpx = vector<cpx>;
void fft(vcpx &a, bool inv = false) {
    int n = a.size(), j = 0; assert((n&-n) == n);
    for(int i=1; i<n; i++) {
        int bit = (n >> 1);
        while(j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if(i < j) swap(a[i], a[j]);
    }
    
    vcpx roots(n/2);
    prec c = 2 * pi * (inv ? -1 : 1);
    for(int i=0; i<n/2; i++)
        roots[i] = cpx(cosl(c * i / n), sinl(c * i / n));
        
    for(int i=2; i<=n; i<<=1) {
        int step = n / i;
        for(int j=0; j<n; j+=i) {
            for(int k=0; k<i/2; k++) {
                cpx u = a[j+k], v = a[j+k+i/2]*roots[step*k];
                a[j+k] = u+v;
                a[j+k+i/2] = u-v;
            }
        }
    }
    
    if(inv) for(int i=0; i<n; i++) a[i] /= n;
}

ll mod = 1e9+7;
vl conv(const vl& AA,const vl& BB) {
    const ll G = 1<<15;
    int n = AA.size()+BB.size()-1;
    int m = 1; while(m < n) m<<=1;
    
    int a = AA.size(), b = BB.size();
    
    vcpx A(m), B(m), C(m), D(m);
    fors(i, 0, a-1) A[i] = cpx(AA[i]/G, AA[i]%G);
    fors(i, 0, b-1) B[i] = cpx(BB[i]/G, BB[i]%G);
    
    fft(A); fft(B);
    
    fors(i, 0, m-1) {
        int j = i?m-i:0;
        cpx A1 = (A[i]+conj(A[j]))*cpx(0.5, 0);
        cpx A2 = (A[i]-conj(A[j]))*cpx(0, -0.5);
        
        cpx B1 = (B[i]+conj(B[j]))*cpx(0.5, 0);
        cpx B2 = (B[i]-conj(B[j]))*cpx(0, -0.5);
        
        C[i] = A1*B1 + A2*B2*cpx(0, 1);
        D[i] = A2*B1 + A1*B2*cpx(0, 1);
    }
    
    fft(C, true); fft(D, true);
    
    
    vl ret(m); ll G1 = G%mod, G2 = (lll)G*G%mod;
    fors(i, 0, m-1) {
        ll p = ll(C[i].real()+0.5);
        ll q = ll(D[i].real()+0.5) + ll(D[i].imag()+0.5);
        ll r = ll(C[i].imag()+0.5);
        
        p %= mod; q %= mod; r %= mod;
        ret[i] = (((lll)p*G2)%mod+((lll)q*G1)%mod+r%mod)%mod;
    }
    ret.resize(n);
    return ret;
}