#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 交换函数
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 划分函数
int partition(int arr[], int left, int right) {
    // 选取最右侧的元素为基准元素
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        // 将小于基准元素的数放在左侧
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // 将基准元素放在中间位置
    swap(&arr[i + 1], &arr[right]);

    // 返回基准元素所在位置
    return i + 1;
}

// 查找第k大的数
int findKthLargest(int arr[], int n, int k) {
    int left = 0, right = n - 1;

    while (left <= right) {
        // 划分函数返回基准元素所在位置
        int pivotIndex = partition(arr, left, right);

        // 基准元素为第n-k+1大的数
        if (pivotIndex == n - k) {
            return arr[pivotIndex];
        }
        // 第n-k+1大的数在基准元素的左侧
        else if (pivotIndex > n - k) {
            right = pivotIndex - 1;
        }
        // 第n-k+1大的数在基准元素的右侧
        else {
            left = pivotIndex + 1;
        }
    }

    return -1; // 找不到第k大的数
}

int main() {
    int n, k;
    printf("请输入数组长度n：");
    scanf("%d", &n);
    printf("请输入要查找的第k大的数：");
    scanf("%d", &k);

    // 生成随机数组
    int* arr = (int*)malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("随机数组为：");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 查找第k大的数
    int kthLargest = findKthLargest(arr, n, k);
    if (kthLargest == -1) {
        printf("无法找到第%d大的数\n", k);
    }
    else {
        printf("第%d大的数为%d\n", k, kthLargest);
    }

    // 释放数组内存空间
    free(arr);

    return 0;
}
