#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// 定义堆结构体
typedef struct {
    int* data; // 存储堆元素的数组
    int size;  // 堆的当前大小
    int capacity; // 堆的容量
} Heap;

// 创建堆
Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (int*)malloc(sizeof(int) * (capacity + 1)); // 数组下标从1开始
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// 插入元素
void insert(Heap* heap, int value) {
    if (heap->size >= heap->capacity) {
        printf("堆已满，插入失败！\n");
        return;
    }
    heap->size++;
    heap->data[heap->size] = value; // 将新元素插入到堆的最后
    int i = heap->size;
    while (i > 1 && heap->data[i] > heap->data[i / 2]) { // 上滤操作，保证堆的最大堆性质
        int temp = heap->data[i];
        heap->data[i] = heap->data[i / 2];
        heap->data[i / 2] = temp;
        i = i / 2;
    }
    printf("插入成功！\n");
}

// 删除堆顶元素
void removeMax(Heap* heap) {
    if (heap->size == 0) {
        printf("堆为空，删除失败！\n");
        return;
    }
    heap->data[1] = heap->data[heap->size]; // 将堆最后一个元素移到堆顶
    heap->size--;
    int i = 1;
    while (i * 2 <= heap->size) { // 下滤操作，保证堆的最大堆性质
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
    printf("删除成功！\n");
}

// 打印堆元素
void printHeap(Heap* heap) {
    printf("堆的元素为：");
    for (int i = 1; i <= heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// 销毁堆
void destroyHeap(Heap* heap) {
    free(heap->data);
    free(heap);
    printf("堆已销毁！\n");
}

// 交互式测试堆
void interactive() {
    printf("请输入堆的容量：");
    int capacity;
    scanf("%d", &capacity);
    Heap* heap = createHeap(capacity);
    int option;
    while (1) {
        printf("\n请选择操作：\n");
        printf("1. 插入元素\n");
        printf("2. 删除堆顶元素\n");
        printf("3. 打印堆元素\n");
        printf("4. 销毁堆\n");
        printf("5. 退出程序\n");
        scanf("%d", &option);
        switch (option) {
        case 1: {
            printf("请输入要插入的元素：");
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
            printf("程序已退出！\n");
            return;
        }
        default: {
            printf("请输入正确的选项！\n");
            break;
        }
        }
    }
}

// 主函数
int main() {
    interactive();
    return 0;
}