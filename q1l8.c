#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start, finish;
} Activity;

int compare(const void *a, const void *b) {
    Activity *x = (Activity *)a;
    Activity *y = (Activity *)b;

    return x->finish - y->finish;
}

void activitySelection(Activity arr[], int n, int index,
                       int lastFinish, Activity selected[],
                       int *count) {

    if (index == n)
        return;

    if (arr[index].start >= lastFinish) {
        selected[*count] = arr[index];
        (*count)++;

        activitySelection(arr, n, index + 1,
                          arr[index].finish, selected, count);
    } else {
        activitySelection(arr, n, index + 1,
                          lastFinish, selected, count);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    Activity arr[1000], selected[1000];

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].start, &arr[i].finish);
    }

    qsort(arr, n, sizeof(Activity), compare);

    int count = 0;

    activitySelection(arr, n, 0, 0, selected, &count);

    printf("%d\n", count);

    for (int i = 0; i < count; i++) {
        printf("(%d,%d)", selected[i].start, selected[i].finish);

        if (i < count - 1)
            printf("  ");
    }

    printf("\n");

    return 0;
}