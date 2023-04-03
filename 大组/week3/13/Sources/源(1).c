#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ��������
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

// �鲢����
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // ������ʱ����
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    // �����ݸ��Ƶ���ʱ���� L[] �� R[] ��
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // �鲢��ʱ���鵽ԭ���� arr[]
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

    // ���� L[] ��ʣ���Ԫ�أ�����еĻ����� arr[]
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // ���� R[] ��ʣ���Ԫ�أ�����еĻ����� arr[]
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // �ͷŶ�̬�ڴ�
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // �ָ�����
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // �ϲ��ָ������
        merge(arr, l, m, r);
    }
}


// ��������
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
        // �ָ�����
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// ��������
void countSort(int arr[], int n, int max) {
    int* output = (int*)malloc(sizeof(int) * n); // �������
    int* count = (int*)malloc(sizeof(int) * (max + 1));
    memset(count, 0, sizeof(int) * (max + 1));

    // �洢ÿ��Ԫ�صĳ��ִ���
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    // �޸�count[i]��ʹ������С�ڵ���i��Ԫ������
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // �Ӻ���ǰ�������飬�����������
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // ��������鸴�Ƶ�ԭ����
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
    free(count);
}


// ��ȡarr[]�����Ԫ��
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}
// ������������
void radixCountSort(int arr[], int n, int exp) {
    int* output = (int*)malloc(n * sizeof(int));
    int count[10] = { 0 };
    // ͳ��ÿ�����ֳ��ֵĴ���
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // �޸� count[i]��ʹ����ʾ���� i ����������е��±�λ��
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // �������� output ������
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // �� output ���鸴�Ƶ�ԭ����
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
    free(output); // �ͷŷ�����ڴ�
}

void radixSort(int arr[], int n) {
    // ��ȡ�����е����Ԫ��
    int max = getMax(arr, n);
    // ��ÿһλ���м�������
    for (int exp = 1; max / exp > 0; exp *= 10)
        radixCountSort(arr, n, exp);
}

int main() {
    int num_datasets = 5; // ���ݼ�����
    int dataset_sizes[] = { 10, 50, 100, 500, 1000 }; // ÿ�����ݼ��Ĵ�С
    // ��ʼ�������������
    srand(time(0));

    // ����ÿ�����ݼ�������������ݲ���������
    for (int i = 0; i < num_datasets; i++) {
        int n = dataset_sizes[i];
       int* arr = (int*)malloc(n * sizeof(int));

        clock_t start, end;
        double cpu_time_used;

        // �����������
        for (int j = 0; j < n; j++)
            arr[j] = rand() % n;

        // ���Բ�������
        start = clock();
        for (int k = 0; k < 100000; k++)
            insertionSort(arr, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("�����������ݼ���С��%d������ʱ�䣺%f��\n", n, cpu_time_used);

        // ���Թ鲢����
        start = clock();
        for (int k = 0; k < 100000; k++)
            mergeSort(arr, 0, n - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("�鲢�������ݼ���С��%d������ʱ�䣺%f��\n", n, cpu_time_used);
        // ���Կ�������
        start = clock();
        for (int k = 0; k < 100000; k++)
            quickSort(arr, 0, n - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("�����������ݼ���С��%d������ʱ�䣺%f��\n", n, cpu_time_used);

        // ���Լ�������
        start = clock();
        for (int k = 0; k < 100000; k++)
            countSort(arr, n, 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("�����������ݼ���С��%d������ʱ�䣺%f��\n", n, cpu_time_used);

        // ���Ի�����������
        start = clock();
        for (int k = 0; k < 100000; k++)
            radixSort(arr, n);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("���������������ݼ���С��%d������ʱ�䣺%f��\n", n, cpu_time_used);
        free(arr);

    }

    return 0;
}
