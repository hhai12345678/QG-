/*#include<stdio.h>
int main()
{
	int a, b, c,n;
	scanf_s("%d", &n);
	for (a = 0; a<=n;a++)//�������沿��
	{
		for (b = n-1; b >=a; b--)//����ո������
			printf(" ");
		for (c = 1; c <= 2 * a-1; c++)//���*������
			printf("*");
		printf("\n");
	}
	for (a = n - 1; a >= 1; a--)//�������沿��
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

//������ʽ�洢�ṹ��
typedef struct Node {
    void* data;
    struct Node* next;
}Node, * Queue;

//��ʼ������
void InitQueue(Queue* Q) {
    *Q = NULL;
}

//�ж϶����Ƿ�Ϊ��
int QueueEmpty(Queue Q) {
    if (Q == NULL) {
        return 1;
    }
    else {
        return 0;
    }
}

//���
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

//����
void* DeQueue(Queue* Q) {
    if (QueueEmpty(*Q)) {
        printf("����Ϊ�գ��޷����ӣ�\n");
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

//��ȡ��ͷԪ��
void* GetHead(Queue Q) {
    if (QueueEmpty(Q)) {
        printf("����Ϊ�գ��޷���ȡ��ͷԪ�أ�\n");
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
    printf("��ͷԪ��Ϊ��%d\n", *(int*)GetHead(Q));
    printf("����Ԫ��Ϊ��%d\n", *(int*)DeQueue(&Q));
    printf("����Ԫ��Ϊ��%c\n", *(char*)DeQueue(&Q));
    printf("����Ԫ��Ϊ��%f\n", *(float*)DeQueue(&Q));
    printf("�����Ƿ�Ϊ�գ�%d\n", QueueEmpty(Q));
    return 0;
}
