#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 插入排序
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

// 归并排序
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // 创建临时数组
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // 将数据复制到临时数组 L[] 和 R[] 中
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // 归并临时数组到原数组 arr[]
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

    // 复制 L[] 中剩余的元素（如果有的话）到 arr[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // 复制 R[] 中剩余的元素（如果有的话）到 arr[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // 释放动态内存
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // 分割数组
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // 合并分割的数组
        merge(arr, l, m, r);
    }
}


// 快速排序
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        // 分割数组
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// 计数排序
void countSort(int arr[], int n, int max) {
    int* output = (int*)malloc(sizeof(int) * n); // 输出数组
    int* count = (int*)malloc(sizeof(int) * (max + 1));
    memset(count, 0, sizeof(int) * (max + 1));

    // 存储每个元素的出现次数
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // 修改count[i]，使它包含小于等于i的元素数量
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // 从后往前遍历数组，构造输出数组
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // 将输出数组复制到原数组
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
    free(count);
}


// 获取arr[]中最大元素
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
// 基数计数排序
void radixCountSort(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };
    // 统计每个数字出现的次数
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // 修改 count[i]，使它表示的是 i 在输出数组中的下标位置
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 输出结果到 output 数组中
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 将 output 数组复制到原数组
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    free(output); // 释放分配的内存
}

void radixSort(int arr[], int n) {
    // 获取数组中的最大元素
    int max = getMax(arr, n);
    // 对每一位进行计数排序
    for (int exp = 1; max / exp > 0; exp *= 10)
        radixCountSort(arr, n, exp);
}

int main() {
    int num_datasets = 5; // 数据集数量
    int dataset_sizes[] = { 10, 50, 100, 500, 1000 }; // 每个数据集的大小
    // 初始化随机数生成器
    srand(time(0));

    // 对于每个数据集，生成随机数据并进行排序
    for (int i = 0; i < num_datasets; i++) {
        int n = dataset_sizes[i];
       int* arr = (int*)malloc(n * sizeof(int));

        clock_t start, end;
        double cpu_time_used;

        // 生成随机数据
        for (int j = 0; j < n; j++)
            arr[j] = rand() % n;

        // 测试插入排序
        start = clock();
        for (int k = 0; k < 100000; k++)
            insertionSort(arr, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("插入排序，数据集大小：%d，排序时间：%f秒\n", n, cpu_time_used);

        // 测试归并排序
        start = clock();
        for (int k = 0; k < 100000; k++)
            mergeSort(arr, 0, n - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("归并排序，数据集大小：%d，排序时间：%f秒\n", n, cpu_time_used);
        // 测试快速排序
        start = clock();
        for (int k = 0; k < 100000; k++)
            quickSort(arr, 0, n - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("快速排序，数据集大小：%d，排序时间：%f秒\n", n, cpu_time_used);

        // 测试计数排序
        start = clock();
        for (int k = 0; k < 100000; k++)
            countSort(arr, n, 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("计数排序，数据集大小：%d，排序时间：%f秒\n", n, cpu_time_used);

        // 测试基数计数排序
        start = clock();
        for (int k = 0; k < 100000; k++)
            radixSort(arr, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("基数计数排序，数据集大小：%d，排序时间：%f秒\n", n, cpu_time_used);
        free(arr);

    }

    return 0;
}
