#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��������
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// ���ֺ���
int partition(int arr[], int left, int right) {
    // ѡȡ���Ҳ��Ԫ��Ϊ��׼Ԫ��
    int pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        // ��С�ڻ�׼Ԫ�ص����������
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // ����׼Ԫ�ط����м�λ��
    swap(&arr[i + 1], &arr[right]);

    // ���ػ�׼Ԫ������λ��
    return i + 1;
}

// ���ҵ�k�����
int findKthLargest(int arr[], int n, int k) {
    int left = 0, right = n - 1;

    while (left <= right) {
        // ���ֺ������ػ�׼Ԫ������λ��
        int pivotIndex = partition(arr, left, right);

        // ��׼Ԫ��Ϊ��n-k+1�����
        if (pivotIndex == n - k) {
            return arr[pivotIndex];
        }
        // ��n-k+1������ڻ�׼Ԫ�ص����
        else if (pivotIndex > n - k) {
            right = pivotIndex - 1;
        }
        // ��n-k+1������ڻ�׼Ԫ�ص��Ҳ�
        else {
            left = pivotIndex + 1;
        }
    }

    return -1; // �Ҳ�����k�����
}

int main() {
    int n, k;
    printf("���������鳤��n��");
    scanf("%d", &n);
    printf("������Ҫ���ҵĵ�k�������");
    scanf("%d", &k);

    // �����������
    int* arr = (int*)malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("�������Ϊ��");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // ���ҵ�k�����
    int kthLargest = findKthLargest(arr, n, k);
    if (kthLargest == -1) {
        printf("�޷��ҵ���%d�����\n", k);
    }
    else {
        printf("��%d�����Ϊ%d\n", k, kthLargest);
    }

    // �ͷ������ڴ�ռ�
    free(arr);

    return 0;
}
