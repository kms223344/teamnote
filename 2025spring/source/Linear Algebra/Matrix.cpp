class Matrix {
private:
    // c: col 개수, r: row 개수
    ll c, r, mod;
	vector<vector<ll>> arr;
    ll power(ll x, ll y, ll p) {
        if (y == 0) return 1;
        ll v = power(x, y/2, p) % p;
        v = (v * v) % p;
        return (y%2 == 0)? v : (x * v) % p;
    }
    ll modInverse(ll a, ll p) { return power(a, p-2, p); }

public:
    Matrix(int _n, int _m, ll p) : c(_n), r(_m), mod(p) {
        arr.resize(c, vector<ll>(r, 0));
    }
    
    void setI() {
        assert(c == r);
        for(int i=0; i<c; i++) arr[i][i] = 1;
    }

    ll *operator[](ll i) { return &arr[i][0]; }

    void swaprow(ll i, ll j) {
		if (i == j) return;
		for (int k = 0; k < c; k++)
			swap(arr[i][k], arr[j][k]);
    }

    pair<bool, Matrix> Inverse() {
        assert(c == r);
        Matrix victim = *this;
        Matrix retm(c, c, mod);
        retm.setI();

        for (int k = 0; k < c; k++) {
            int t = k - 1;
            while (t + 1 < c && !victim[++t][k]);
            if (t == c - 1 && !victim[t][k])
                return {false, Matrix(0, 0, 0)};
            victim.swaprow(k, t), retm.swaprow(k, t);
            ll d = victim[k][k];

            for (int j = 0; j < c; j++) {
                victim[k][j] = (victim[k][j] * modInverse(d, mod))%mod;
                retm[k][j] = (retm[k][j] * modInverse(d, mod))%mod;
            }

            for (int i = 0; i<c; i++)
                if (i != k) {
                    ll m = victim[i][k];
                    for (int j = 0; j < c; j++) {
                        if (j >= k) victim[i][j] = (victim[i][j] - victim[k][j] * m + mod*mod)%mod;
                        retm[i][j] = (retm[i][j] - retm[k][j] * m + mod*mod)%mod;
                    }
                }
        }
        return {true, retm};
    }

    vector<double> GaussElimination() {
        assert(c == r - 1);
        vector<double> retv(c, 0.0);

        for(ll i=0; i<c; i++) for(ll j=1+i; j<c; j++) {
            double tmp = arr[j][i];
            for(ll k=i; k<r; k++)
                arr[j][k] = arr[j][k] - (tmp / arr[i][i]) * arr[i][k];
        }

        ll p = c, q = 0;
        for (ll p = c - 1; p >= 0; p--) {
            retv[p] = arr[p][c] / arr[p][p];
            for (q = p - 1; q >= 0; q--)
                arr[q][c] = arr[q][c] - arr[q][p] * retv[p];
        }
        return retv;
    }
};