const int N = 1e5+7;
char s[N];
int F[N], Z[N], M[N];
int sa[N]; int ord[N], tmp[N], cnt[N];
int lcp[N];
int main() {
    scanf("%s", s+1);
    int n = strlen(s+1);
    
    // KMP - fail function {
        F[1] = 0; int j = 0;
        for(int i=2; i<=n;i++)
        {
            while(j > 0 and s[i] != s[j+1]) j = F[j];
            F[i] = j+=(s[i] == s[j+1]);
        }
    }
    
    //Z - Z array {
        Z[1] = n; int j = 1, r = 0;
        for(int i=2; i<=n; i++)
        {
            Z[i] = i<j+r?min(Z[i-j+1], j+r-i):0;
            while(s[1+Z[i]] == s[i+Z[i]]) Z[i]++;
            if(j+r < i+Z[i]) j = i, r = Z[i];
        }
    }
    
    //Manacher - M array {
        M[1] = 0; int j = 1, r = 0;
        for(int i=2; i<=n; i++)
        {
            M[i] = i<j+r?min(M[2*j-i], j+r-i):0;
            while(1 <= i-M[i]-1 && i+M[i]+1 <= n
                   && s[i-M[i]-1] == s[i+M[i]+1]) M[i]++;
            if(j+r < i+M[i]) j = i, r = M[i];
        }
    }
    
    //Suffix Array - SA {
        int t = 1; ord[n+1] = 0; tmp[0] = 0; sa[0] = 0;
        
        auto cmp = [&t, &n](int i,int j) {
               return ord[i] == ord[j]
                      ?ord[min(i+t, n+1)]<ord[min(j+t, n+1)]
                      :ord[i]<ord[j];
        };
        
        forr(i, n) ord[i] = s[i], sa[i] = i;
        sort(sa+1, sa+1+n, [](int i,int j){return ord[i]<ord[j];});
        
        forr(i, n)  tmp[sa[i]] = tmp[sa[i-1]] + (ord[sa[i-1]]<ord[sa[i]]);
        swap(tmp, ord);
        
        while(t < n) {
            fors(i, 0, n) cnt[i] = 0;
            forr(i, n) cnt[ord[min(i+t, n+1)]]++;
            forr(i, n) cnt[i] += cnt[i-1];
            fore(i, n, 1) tmp[cnt[ord[min(i+t, n+1)]]--] = i;
            
            fors(i, 0, n) cnt[i] = 0;
            forr(i, n) cnt[ord[i]]++;
            forr(i, n) cnt[i] += cnt[i-1];
            fore(i, n, 1) sa[cnt[ord[tmp[i]]]--] = tmp[i];
            
            forr(i, n) tmp[sa[i]] = tmp[sa[i-1]] + cmp(sa[i-1], sa[i]);
            swap(ord, tmp);
            
            t<<=1;
            if(ord[sa[n]] == n) break;
        }
    }
    
    //LCP array {
        int k = 0;
        forr(i, n) if(ord[i] != 1) {
            int j = sa[ord[i]-1];
            while(s[i+k] == s[j+k]) k++;
            lcp[ord[i]] = k;
            
            if(k > 0) k--;
        }
    }
    
    printf("\nF : "); forr(i, n) printf("%d ", F[i]);
    printf("\nZ : "); forr(i, n) printf("%d ", Z[i]);
    printf("\nM : "); forr(i, n) printf("%d ", M[i]);
    printf("\nSA : "); forr(i, n) printf("%d ", sa[i]);
    printf("\nLCP : x "); fors(i, 2, n) printf("%d ", lcp[i]); 
    
    printf("\n"); forr(i, n) printf("%s\n", s+sa[i]);
}