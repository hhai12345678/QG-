#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 10000

// 插入排序
void insert_sort(int arr[], int n) {
    int i, j, temp;
    for (i = 1; i < n; i++) {
        temp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// 归并排序
void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        int n1 = m - l + 1;
        int n2 = r - m;

        int* L = (int*)malloc(n1 * sizeof(int));
        int* R = (int*)malloc(n2 * sizeof(int));

        int i, j, k;
        for (i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];

        i = 0;
        j = 0;
        k = l;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }

        free(L);
        free(R);
    }
}

// 快速排序
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int j, temp;

    for (j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// 计数排序
void count_sort(int arr[], int n) {
    int i, j;
    int count[MAX_VALUE + 1] = { 0 };
    int* output = (int*)malloc(n * sizeof(int));  // 动态分配空间

    for (i = 0; i < n; i++)
        count[arr[i]]++;

    for (i = 1; i <= MAX_VALUE; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for (i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);  // 释放空间
}

// 基数计数排序
#define RADIX 10

void radix_count_sort(int arr[], int n) {
    int i, j;
    int max_value = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max_value)
            max_value = arr[i];
    }

    int* output = (int*)malloc(n * sizeof(int));
    int count[RADIX] = { 0 };

    for (i = 1; max_value / i > 0; i *= RADIX) {
        for (j = 0; j < RADIX; j++)
            count[j] = 0;

        for (j = 0; j < n; j++)
            count[(arr[j] / i) % RADIX]++;

        for (j = 1; j < RADIX; j++)
            count[j] += count[j - 1];

        for (j = n - 1; j >= 0; j--) {
            output[count[(arr[j] / i) % RADIX] - 1] = arr[j];
            count[(arr[j] / i) % RADIX]--;
        }

        for (j = 0; j < n; j++)
            arr[j] = output[j];
    }

    free(output);
}

int main() {
    srand(time(NULL));
    int n1 = 10000, n2 = 50000, n3 = 200000;
    int i;
    clock_t start, end;
    double cpu_time_used;

    int* arr1 = malloc(n1 * sizeof(int));
    int* arr2 = malloc(n2 * sizeof(int));
    int* arr3 = malloc(n3 * sizeof(int));

    // 生成随机数
    for (i = 0; i < n1; i++)
        arr1[i] = rand() % (MAX_VALUE + 1);

    for (i = 0; i < n2; i++)
        arr2[i] = rand() % (MAX_VALUE + 1);

    for (i = 0; i < n3; i++)
        arr3[i] = rand() % (MAX_VALUE + 1);

    // 插入排序测试
    printf("插入排序测试开始...\n");

    start = clock();
    insert_sort(arr1, n1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n1, cpu_time_used);

    start = clock();
    insert_sort(arr2, n2);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n2, cpu_time_used);

    start = clock();
    insert_sort(arr3, n3);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n3, cpu_time_used);

    printf("插入排序测试结束\n\n");

    // 归并排序测试
    printf("归并排序测试开始...\n");

    start = clock();
    merge_sort(arr1, 0, n1 - 1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n1, cpu_time_used);

    start = clock();
    merge_sort(arr2, 0, n2 - 1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n2, cpu_time_used);

    start = clock();
    merge_sort(arr3, 0, n3 - 1);
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n3, cpu_time_used);
    printf("归并排序测试结束\n\n");

    // 快速排序测试
    printf("快速排序测试开始...\n");

    start = clock();
    quick_sort(arr1, 0, n1 - 1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n1, cpu_time_used);

    start = clock();
    quick_sort(arr2, 0, n2 - 1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n2, cpu_time_used);

    start = clock();
    quick_sort(arr3, 0, n3 - 1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n3, cpu_time_used);

    printf("快速排序测试结束\n\n");

    // 计数排序测试
    printf("计数排序测试开始...\n");

    start = clock();
    count_sort(arr1, n1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n1, cpu_time_used);

    start = clock();
    count_sort(arr2, n2);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n2, cpu_time_used);

    start = clock();
    count_sort(arr3, n3);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n3, cpu_time_used);

    printf("计数排序测试结束\n\n");

    // 基数计数排序测试
    printf("基数计数排序测试开始...\n");

    start = clock();
    radix_count_sort(arr1, n1);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n1, cpu_time_used);

    start = clock();
    radix_count_sort(arr2, n2);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n2, cpu_time_used);

    start = clock();
    radix_count_sort(arr3, n3);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("数组大小：%d，用时：%f秒\n", n3, cpu_time_used);

    printf("基数计数排序测试结束\n\n");
    free(arr1);
    free(arr2);
    free(arr3);
    return 0;
}

