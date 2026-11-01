#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL
#define MAXN 300
#define LOG 31

typedef long long ll;

ll power[LOG][MAXN][MAXN];

ll temp[MAXN][MAXN];

void multiply(ll A[MAXN][MAXN], ll B[MAXN][MAXN],
              ll C[MAXN][MAXN], int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
}

void multiplyVector(ll *v, ll A[MAXN][MAXN], int n) {
    ll result[MAXN] = {0};

    for (int i = 0; i < n; i++) {
        if (v[i] == 0) continue;

        for (int j = 0; j < n; j++) {
            result[j] = (result[j] + v[i] * A[i][j]) % MOD;
        }
    }

    for (int i = 0; i < n; i++)
        v[i] = result[i];
}

int main() {
    int n, m, q;

    scanf("%d %d %d", &n, &m, &q);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            power[0][i][j] = 0;
        }
    }

    // Build adjacency matrix (undirected graph)
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        u--;
        v--;

        power[0][u][v]++;
        power[0][u][v] %= MOD;

        power[0][v][u]++;
        power[0][v][u] %= MOD;
    }

    // Precompute powers of adjacency matrix
    for (int p = 1; p < LOG; p++) {
        multiply(power[p - 1], power[p - 1],
                 power[p], n);
    }

    // Process queries
    while (q--) {
        int s, t;
        ll k;

        scanf("%d %d %lld", &s, &t, &k);

        s--;
        t--;

        if (k == 0) {
            printf("%d\n", s == t ? 1 : 0);
            continue;
        }

        ll v[MAXN] = {0};
        v[s] = 1;

        int bit = 0;

        while (k > 0) {
            if (k & 1) {
                multiplyVector(v, power[bit], n);
            }

            k >>= 1;
            bit++;
        }

        printf("%lld\n", v[t]);
    }

    return 0;
}