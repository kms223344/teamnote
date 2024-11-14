using pii=pair<int,int>;
pii operator+(pii A, pii B){return {A.fi+B.fi, A.se+B.se};}
pii operator-(pii A, pii B){return {A.fi-B.fi, A.se-B.se};}
ll operator*(pii A, pii B){return (ll)A.fi*B.fi+(ll)A.se*B.se;} // inner product
ll operator/(pii A, pii B){return (ll)A.fi*B.se-(ll)A.se*B.fi;} // outer product

// 각도 정렬 (O = pii(0, 0))
sort(P+1, P+1+n, [](pii A, pii B){return (A<O)!=(B<O)?l<r:l/r>0;});

// 선분 : pair<pii A, pii B> -> 2D-vector B from A
// 선분 교차 판정
bool isintersect(const pii &a, const pii &b, const pii &u, const pii &v){
  if( b/v != 0 ) return sign((u-a)/b) * sign((u+v-a)/b) <= 0 && sign((a-u)/v) * sign((a+b-u)/v) <= 0;
  else return (a-u)/v == 0 && (0 <= v*(a-u) && v*(a-u) <= v*v || 0 <= b*(u-a) && b*(u-a) <= b*b);
}