#include <stdio.h>
#include <limits.h>

#define MAX 100

int main() {
    int n;
    int p[MAX];
    long long dp[MAX][MAX];

    scanf("%d", &n);

    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]);
    }

    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = LLONG_MAX;

            for (int k = i; k < j; k++) {
                long long cost = dp[i][k] + dp[k + 1][j]
                               + (long long)p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }

    printf("%lld\n", dp[1][n]);

    return 0;
}