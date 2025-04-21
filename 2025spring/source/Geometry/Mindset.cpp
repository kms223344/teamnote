using pii=pair<int,int>;
pii operator+(pii A, pii B){return {A.fi+B.fi, A.se+B.se};}
pii operator-(pii A, pii B){return {A.fi-B.fi, A.se-B.se};}
ll operator*(pii A, pii B){return (ll)A.fi*B.fi+(ll)A.se*B.se;} // inner product
ll operator/(pii A, pii B){return (ll)A.fi*B.se-(ll)A.se*B.fi;} // outer product

// 각도 정렬 (O = pii(0, 0))
sort(P+1, P+1+n, [](pii A, pii B) {
    if(B == O) return false;
    if(A == O) return true;
    return (A<O)!=(B<O)?A>B:A/B<0;
});

// 선분 교차
// Segment : fi에서 시작하는 se 벡터
// fi + k * se, 0 <= k <= 1

using Segment = pair<pii, pii>;
int isJoin(const Segment& A, const Segment& B) {
    if(B.se/A.se != 0) {
        ll p = (A.fi-B.fi)/A.se;
        ll q = B.se/A.se;
        
        if(q<0) q = -q, p = -p;
        if(p < 0 or p > q) return false;
        
        p = (B.fi-A.fi)/B.se;
        q = A.se/B.se;
        
        if(q<0) q = -q, p = -p;
        if(p < 0 or p > q) return false;
        
        return true;
    }
    else {
        if((A.fi-B.fi)/A.se != 0) return false;
        
        ll p = A.fi*A.se, q = (A.fi+A.se)*A.se;
        ll r = B.fi*A.se, s = (B.fi+B.se)*A.se;
        
        if(p>q) swap(p, q); if(r>s) swap(r, s);
        
        if(max(p, r) > min(q, s)) return false;
        
        return true;
    }
}
