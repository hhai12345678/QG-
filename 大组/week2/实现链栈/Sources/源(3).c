
#include<stdio.h>
#include<stdlib.h>

typedef struct node {//��ջ�Ľṹ���� 
    int data;//������ 
    struct node* next;//ָ���� 
}node;
node* start(node* l) {//��ջ�ĳ�ʼ�� ���ص���ָ�� 
    l = (node*)malloc(sizeof(node));//Ϊ��ջ�����ڴ�ռ� 
    l->next = NULL;//��ʼ��Ϊ��ջ 
    return l;
}
void create(node* l) {//����һ���µ���ջ 
    node* p;//�½�ָ��p  
    int i = 1;
    int j;
    while (i != 0) {
        scanf_s("%d", &j);
        if (j != -1) {
            p = (node*)malloc(sizeof(node)); //��p����ռ�
            p->data = j;
            p->next = l->next;
            l->next = p;//ͷ�巨 
        }
        else {
            i = 0;//����-1ʱ���� 
        }
    }
}
void push(node* l, int e) {//��ջ�Ľ�ջ���� 
    node* p;//�½�ָ��p
    p = (node*)malloc(sizeof(node)); //��p����ռ�
    p->data = e;
    p->next = l->next;//ͷ�巨��ջ 
    l->next = p;
    printf("Ԫ��%d��ջ��\n", p->data);
}
void pop(node* l) {//��ջ�ĳ�ջ���� 
    node* p;//�½�ָ��p
    p = l->next;
    if (p == NULL) {
        printf("����ջΪ�գ��޷���ջ��\n");
    }
    else {
        int e;
        e = p->data;
        printf("Ԫ��%d��ջ��\n",e);
        l->next = p->next;//ɾ�����p 
        free(p);
    }
}
void print(node* l) {
    node* p;
    p = l->next;
    if (p == NULL) {
        printf("����ջΪ�գ��޷���ӡ��\n");
    }
    else {
        printf("�����������Ϊ��");
        while (l->next != NULL) {
            printf("%d ", l->next->data);
            l = l->next;
        }
        printf("\n");
    }
}
int main() {
    node* p=0;
    p = start(p);
    printf("��ջ��ʼ���ɹ���\n");
    printf("����������ջ��ֵ��\n");
    create(p);
    print(p);
    push(p, 1);
    print(p);
    pop(p);
    print(p);
}
