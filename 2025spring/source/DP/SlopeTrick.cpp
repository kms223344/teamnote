const int N = 1e6+7;
int arr[N];
priority_queue<int> pq;
ll ans = 0;
int main()
{
    getint(n);
    forr(i, n) scanf("%d", arr+i);
    
    pq.push(arr[1]); int t=0; ll val = 0;
    fors(i, 2, n)
    {
        t++;
        int r = t + pq.top();
        if(r <= arr[i]) pq.push(arr[i]-t);
        else
        {
            pq.push(arr[i]-t); pq.push(arr[i]-t); pq.pop();
            ans += r-arr[i];
        }
    }
    
    printf("%lld", ans);
}


int arr[N];
priority_queue<int> pq;
int ans2[N];
int main()
{
    getint(n);
    forr(i, n) scanf("%d", arr+i);
    
    pq.push(arr[1]); ll ans = 0;
    ans2[1] = arr[1];
    fors(i, 2, n)
    {
        int r = (i-1) + pq.top();
        if(r <= arr[i]) pq.push(arr[i]-(i-1));
        else
        {
            pq.push(arr[i]-(i-1)); pq.push(arr[i]-(i-1)); pq.pop();
            ans += r-arr[i];
        }
        
        ans2[i] = pq.top() + (i-1);
    }
    
    fore(i, n-1, 1) ans2[i] = min(ans2[i], ans2[i+1]-1);
    forr(i, n) printf("%d\n", ans2[i]);
}