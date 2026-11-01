#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double value, weight, ratio;
} Item;

int compare(const void *a, const void *b) {
    Item *x = (Item *)a;
    Item *y = (Item *)b;

    if (x->ratio < y->ratio) return 1;
    if (x->ratio > y->ratio) return -1;
    return 0;
}

int main() {
    int n;
    double W, maxValue = 0;

    scanf("%d %lf", &n, &W);

    Item items[100005];

    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &items[i].value, &items[i].weight);
        items[i].ratio = items[i].value / items[i].weight;
    }

    qsort(items, n, sizeof(Item), compare);

    for (int i = 0; i < n; i++) {
        if (W >= items[i].weight) {
            maxValue += items[i].value;
            W -= items[i].weight;
        } else {
            maxValue += items[i].ratio * W;
            break;
        }
    }

    printf("%.1lf\n", maxValue);

    return 0;
}