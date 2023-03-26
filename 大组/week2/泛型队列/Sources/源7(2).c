/*#include<stdio.h>
int main()
{
	int a, b, c,n;
	scanf_s("%d", &n);
	for (a = 0; a<=n;a++)//控制上面部分
	{
		for (b = n-1; b >=a; b--)//输出空格的数量
			printf(" ");
		for (c = 1; c <= 2 * a-1; c++)//输出*的数量
			printf("*");
		printf("\n");
	}
	for (a = n - 1; a >= 1; a--)//控制下面部分
	{
		for (b = a; b <= n - 1; b++)
			printf(" ");
		for (c = 1; c <= 2 * a - 1; c++)
			printf("*");
		printf("\n");
	}
	return 0;
}*/
#include <stdio.h>
#include <stdlib.h>

//定义链式存储结构体
typedef struct Node {
    void* data;
    struct Node* next;
}Node, * Queue;

//初始化队列
void InitQueue(Queue* Q) {
    *Q = NULL;
}

//判断队列是否为空
int QueueEmpty(Queue Q) {
    if (Q == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

//入队
void EnQueue(Queue* Q, void* x) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->next = NULL;
    if (*Q == NULL) {
        *Q = p;
    }
    else {
        Node* rear = *Q;
        while (rear->next != NULL) {
            rear = rear->next;
        }
        rear->next = p;
    }
}

//出队
void* DeQueue(Queue* Q) {
    if (QueueEmpty(*Q)) {
        printf("队列为空，无法出队！\n");
        return NULL;
    }
    else {
        Node* p = *Q;
        void* x = p->data;
        *Q = (*Q)->next;
        free(p);
        return x;
    }
}

//获取队头元素
void* GetHead(Queue Q) {
    if (QueueEmpty(Q)) {
        printf("队列为空，无法获取队头元素！\n");
        return NULL;
    }
    else {
        return Q->data;
    }
}

int main() {
    Queue Q;
    InitQueue(&Q);
    int a = 1;
    char b = 'a';
    float c = 1.23;
    EnQueue(&Q, &a);
    EnQueue(&Q, &b);
    EnQueue(&Q, &c);
    printf("队头元素为：%d\n", *(int*)GetHead(Q));
    printf("出队元素为：%d\n", *(int*)DeQueue(&Q));
    printf("出队元素为：%c\n", *(char*)DeQueue(&Q));
    printf("出队元素为：%f\n", *(float*)DeQueue(&Q));
    printf("队列是否为空：%d\n", QueueEmpty(Q));
    return 0;
}
