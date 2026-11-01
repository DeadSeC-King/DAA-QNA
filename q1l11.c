#include <stdio.h>
#include <string.h>

#define MAX 1005

int main() {
    char A[MAX], B[MAX];
    int dp[MAX][MAX];

    scanf("%s", A);
    scanf("%s", B);

    int m = strlen(A);
    int n = strlen(B);

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {

            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            }
            else if (A[i - 1] == B[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else {
                dp[i][j] = dp[i - 1][j] > dp[i][j - 1]
                           ? dp[i - 1][j]
                           : dp[i][j - 1];
            }
        }
    }

    printf("%d\n", dp[m][n]);

    return 0;
}