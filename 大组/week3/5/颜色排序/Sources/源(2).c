#include <stdio.h>

void sort(int arr[], int n) {
    int p0 = 0, p2 = n - 1, i = 0;
    while (i <= p2) {
        if (arr[i] == 0) {
            arr[i] = arr[p0];
            arr[p0] = 0;
            p0++;
            i++;
        }
        else if (arr[i] == 2) {
            arr[i] = arr[p2];
            arr[p2] = 2;
            p2--;
        }
        else {
            i++;
        }
    }
}

int main() {
    int arr[] = { 1, 0, 2, 1, 2, 0, 1, 0, 2, 1 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("ÅÅÐòÇ°£º\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    sort(arr, n);
    printf("ÅÅÐòºó£º\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
