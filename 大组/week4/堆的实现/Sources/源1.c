#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// ����ѽṹ��
typedef struct {
    int* data; // �洢��Ԫ�ص�����
    int size;  // �ѵĵ�ǰ��С
    int capacity; // �ѵ�����
} Heap;

// ������
Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (int*)malloc(sizeof(int) * (capacity + 1)); // �����±��1��ʼ
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// ����Ԫ��
void insert(Heap* heap, int value) {
    if (heap->size >= heap->capacity) {
        printf("������������ʧ�ܣ�\n");
        return;
    }
    heap->size++;
    heap->data[heap->size] = value; // ����Ԫ�ز��뵽�ѵ����
    int i = heap->size;
    while (i > 1 && heap->data[i] > heap->data[i / 2]) { // ���˲�������֤�ѵ���������
        int temp = heap->data[i];
        heap->data[i] = heap->data[i / 2];
        heap->data[i / 2] = temp;
        i = i / 2;
    }
    printf("����ɹ���\n");
}

// ɾ���Ѷ�Ԫ��
void removeMax(Heap* heap) {
    if (heap->size == 0) {
        printf("��Ϊ�գ�ɾ��ʧ�ܣ�\n");
        return;
    }
    heap->data[1] = heap->data[heap->size]; // �������һ��Ԫ���Ƶ��Ѷ�
    heap->size--;
    int i = 1;
    while (i * 2 <= heap->size) { // ���˲�������֤�ѵ���������
        int j = i * 2;
        if (j + 1 <= heap->size && heap->data[j + 1] > heap->data[j]) {
            j++;
        }
        if (heap->data[i] < heap->data[j]) {
            int temp = heap->data[i];
            heap->data[i] = heap->data[j];
            heap->data[j] = temp;
            i = j;
        }
        else {
            break;
        }
    }
    printf("ɾ���ɹ���\n");
}

// ��ӡ��Ԫ��
void printHeap(Heap* heap) {
    printf("�ѵ�Ԫ��Ϊ��");
    for (int i = 1; i <= heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// ���ٶ�
void destroyHeap(Heap* heap) {
    free(heap->data);
    free(heap);
    printf("�������٣�\n");
}

// ����ʽ���Զ�
void interactive() {
    printf("������ѵ�������");
    int capacity;
    scanf("%d", &capacity);
    Heap* heap = createHeap(capacity);
    int option;
    while (1) {
        printf("\n��ѡ�������\n");
        printf("1. ����Ԫ��\n");
        printf("2. ɾ���Ѷ�Ԫ��\n");
        printf("3. ��ӡ��Ԫ��\n");
        printf("4. ���ٶ�\n");
        printf("5. �˳�����\n");
        scanf("%d", &option);
        switch (option) {
        case 1: {
            printf("������Ҫ�����Ԫ�أ�");
            int value;
            scanf("%d", &value);
            insert(heap, value);
            break;
        }
        case 2: {
            removeMax(heap);
            break;
        }
        case 3: {
            printHeap(heap);
            break;
        }
        case 4: {
            destroyHeap(heap);
            return;
        }
        case 5: {
            printf("�������˳���\n");
            return;
        }
        default: {
            printf("��������ȷ��ѡ�\n");
            break;
        }
        }
    }
}

// ������
int main() {
    interactive();
    return 0;
}