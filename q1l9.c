#include <stdio.h>

#define MAX 1000
#define INF 1000000000000000LL

typedef long long ll;

int main() {
    int n, m, s;
    ll graph[MAX][MAX];
    ll dist[MAX];
    int visited[MAX] = {0};

    scanf("%d %d", &n, &m);
    scanf("%d", &s);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = INF;
        }
        graph[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);

        if (w < graph[u][v])
            graph[u][v] = w;
    }

    for (int i = 0; i < n; i++)
        dist[i] = INF;

    dist[s] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j] &&
                (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1 || dist[u] == INF)
            break;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF)
            printf("INF");
        else
            printf("%lld", dist[i]);

        if (i < n - 1)
            printf(" ");
    }

    printf("\n");

    return 0;
}