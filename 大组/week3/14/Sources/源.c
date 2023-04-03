#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"


// �����������
void generateRandomArray(int arr[], int n, int range) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % range + 1;
    }
}

// �����鱣�浽�ļ���
void saveArrayToFile(int arr[], int n, char* filename) {
    FILE* fp;
    fp = fopen(filename, "w");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", arr[i]);
    }
    fclose(fp);
}

// ���ļ��ж�ȡ����
void readArrayFromFile(int arr[], int n, char* filename) {
    FILE* fp;
    fp = fopen(filename, "r");
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);
}

// �������
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// ������������ֵ
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// ��������
void InsertSort(int arr[], int n) {
    int i, j, tmp;
    for (i = 1; i < n; i++) {
        tmp = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > tmp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = tmp;
    }
}

// �鲢����
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    for (i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    i = 0;
    j = 0;
    k = left;
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

void MergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void Swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int j;
    for (j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

void CountSort(int arr[], int n) {
    int i, j, max;
    int* count;
    max = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    count = (int*)malloc(sizeof(int) * (max + 1));
    for (i = 0; i <= max; i++) {
        count[i] = 0;
    }
    for (i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    i = 0;
    j = 0;
    while (i <= max) {
        if (count[i] > 0) {
            arr[j] = i;
            count[i]--;
            j++;
        }
        else {
            i++;
        }
    }
    free(count);
}
// ������������
void RadixCountSort(int arr[], int n) {
    int i, max = arr[0], exp = 1;
    int* output = (int*)malloc(n * sizeof(int)); // ��̬�ڴ����
    int count[10] = { 0 };
    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    while (max / exp > 0) {
        for (i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }
        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for (i = 0; i < n; i++) {
            arr[i] = output[i];
        }
        exp *= 10;
    }
    free(output); // �ͷŶ�̬�ڴ�
}



int main() {
    int n, range;
    printf("������Ҫ���ɵ��������ĳ��ȣ�");
    scanf("%d", &n);
    printf("������������ķ�Χ��");
    scanf("%d", &range);

    int* arr = (int*)malloc(n * sizeof(int));
    generateRandomArray(arr, n, range);
    printf("�������Ϊ��\n");
    printArray(arr, n);

    saveArrayToFile(arr, n, "data.txt");
    printf("�����ѱ��浽�ļ� data.txt �С�\n");

    printf("���ڴ��ļ��ж�ȡ���ݲ���������...\n");
    readArrayFromFile(arr, n, "data.txt");

    printf("����������Ϊ��\n");
    InsertSort(arr, n);
    printArray(arr, n);

    printf("�鲢������Ϊ��\n");
    MergeSort(arr, 0, n - 1);
    printArray(arr, n);

    printf("����������Ϊ��\n");
    QuickSort(arr, 0, n - 1);
    printArray(arr, n);

    printf("����������Ϊ��\n");
    CountSort(arr, n);
    printArray(arr, n);

    printf("��������������Ϊ��\n");
    RadixCountSort(arr, n);
    printArray(arr, n);

    free(arr);

    return 0;
}

