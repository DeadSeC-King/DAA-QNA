#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long start, end;
} Balloon;

int compare(const void *a, const void *b) {
    Balloon *x = (Balloon *)a;
    Balloon *y = (Balloon *)b;

    if (x->end < y->end) return -1;
    if (x->end > y->end) return 1;
    return 0;
}

int findMinArrowShots(Balloon points[], int n) {
    qsort(points, n, sizeof(Balloon), compare);

    int arrows = 1;
    long long lastArrow = points[0].end;

    for (int i = 1; i < n; i++) {
        if (points[i].start > lastArrow) {
            arrows++;
            lastArrow = points[i].end;
        }
    }

    return arrows;
}

int main() {
    int n;
    scanf("%d", &n);

    Balloon points[100005];

    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &points[i].start, &points[i].end);
    }

    printf("%d\n", findMinArrowShots(points, n));

    return 0;
}