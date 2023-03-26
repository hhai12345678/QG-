
#include<stdio.h>
#include<stdlib.h>

typedef struct node {//链栈的结构定义 
    int data;//数据域 
    struct node* next;//指针域 
}node;
node* start(node* l) {//链栈的初始化 返回的是指针 
    l = (node*)malloc(sizeof(node));//为链栈分配内存空间 
    l->next = NULL;//初始化为空栈 
    return l;
}
void create(node* l) {//创建一个新的链栈 
    node* p;//新建指针p  
    int i = 1;
    int j;
    while (i != 0) {
        scanf_s("%d", &j);
        if (j != -1) {
            p = (node*)malloc(sizeof(node)); //给p分配空间
            p->data = j;
            p->next = l->next;
            l->next = p;//头插法 
        }
        else {
            i = 0;//输入-1时结束 
        }
    }
}
void push(node* l, int e) {//链栈的进栈操作 
    node* p;//新建指针p
    p = (node*)malloc(sizeof(node)); //给p分配空间
    p->data = e;
    p->next = l->next;//头插法入栈 
    l->next = p;
    printf("元素%d进栈！\n", p->data);
}
void pop(node* l) {//链栈的出栈操作 
    node* p;//新建指针p
    p = l->next;
    if (p == NULL) {
        printf("该链栈为空，无法出栈！\n");
    }
    else {
        int e;
        e = p->data;
        printf("元素%d出栈！\n",e);
        l->next = p->next;//删除结点p 
        free(p);
    }
}
void print(node* l) {
    node* p;
    p = l->next;
    if (p == NULL) {
        printf("该链栈为空，无法打印！\n");
    }
    else {
        printf("该链表的内容为：");
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
    printf("链栈初始化成功！\n");
    printf("请输入新链栈的值：\n");
    create(p);
    print(p);
    push(p, 1);
    print(p);
    pop(p);
    print(p);
}
