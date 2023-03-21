
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <cstddef>

typedef int ElemType;
typedef struct DuLNode {
    ElemType data;
    struct DuLNode* prior, * next;
} DuLNode, * DuLinkedList;
typedef enum Status {
    error,
    success,
} Status;

//����������
Status InitList_DuL(DuLinkedList* L);
void DestroyList_DuL(DuLinkedList* L);
Status InsertBeforeList_DuL(DuLNode* p, DuLNode* q);
Status InsertAfterList_DuL(DuLNode* p, DuLNode* q);
Status DeleteList_DuL(DuLNode* p, ElemType* e);
void TraverseList_DuL(DuLinkedList L);
void show(void);
int judge_int(void);

Status InitList_DuL(DuLinkedList* L) {
    DuLinkedList List;
    List = (DuLinkedList)malloc(sizeof(DuLNode));
    if (List == NULL)
    {
        printf("�ڴ����ʧ��\n");
        return error;
    }
    List->next = NULL;
    List->prior = NULL;
    *L = List;
    return success;
}

void DestroyList_DuL(DuLinkedList* L) {
    DuLinkedList temp;

    while (*L != NULL)
    {
        temp = *L;
        *L = (*L)->next;
        free(temp);
    }
}

Status InsertBeforeList_DuL(DuLNode* p, DuLNode* q) {
    if (p->next == NULL)//������Ϊ��ʱ��ֱ������p��q
    {
        p->next = q;
        q->prior = p;
    }
    else
    {
        DuLinkedList temp;
        temp = p->next;
        p->next = q;
        q->next = temp;
        temp->prior = q;
        q->prior = p;
        return success;
    }
}

Status InsertAfterList_DuL(DuLNode* p, DuLNode* q) {
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = q;
    q->prior = p;
}

Status DeleteList_DuL(DuLNode* p, ElemType* e) {
    if (p->next == NULL)
    {
        printf("����Ϊ�գ��޷�ɾ��\n");
        return error;
    }
    else
    {
        DuLinkedList posNode = p->next, posNodeFront = p;
        //�ҵ�ɾ������λ��
        while (posNode->data != *e)
        {
            posNodeFront = posNode;
            posNode = posNode->next;
            if (posNode == NULL)
            {
                printf("�Ҳ���������\n");
                return error;
            }
        }
        if (posNode->next != NULL)
        {
            posNodeFront->next = posNode->next;
            posNode->next->prior = posNodeFront;
        }
        else
        {
            posNodeFront->next = NULL;
        }
        free(posNode);
        return success;
    }
}

void TraverseList_DuL(DuLinkedList L) {
    if (L == NULL)
    {
        printf("����δ���������ȴ�������\n");
    }
    else if (L->next == NULL)
    {
        printf("��ǰ����Ϊ��\n");
    }
    else
    {
        DuLinkedList temp = L->next;
        while (temp != NULL)
        {
            printf("%d\t", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void show(void)
{
    printf("\n\n\n\n˫����ADT\n\n");
    printf("1.����������\n");
    printf("2.��������\n");
    printf("3.ͷ�巨��������\n");
    printf("4.β�巨��������\n");
    printf("5.ɾ������\n");
    printf("6.��������\n");
    printf("7.�˳�\n");
    printf("\n�������Ӧ������(1-7)��");
}

int judge_int(void)  //��ֹ�û��������������ַ�
{
    int len, num = 0, arg = 1;
    char word[10];
    int m, j = 1, k;
    while (j)
    {
        scanf("%s", word);
        len = strlen(word);
        for (m = 0; m < len; m++)
        {
            if (word[m] < '0' || word[m]>'9')  //�����Ƿ��������������ַ�
            {
                printf("������������");
                break;
            }
            else
            {
                if (m == len - 1)
                    j = 0;
            }
        }
    }
    j = len - 1;
    for (m = 0; m < len; m++)  // ���ַ�����ת��Ϊ����
    {
        for (k = 0; k < j; k++)
            arg *= 10;
        num += (word[m] - '0') * arg;
        arg = 1;
        j--;
    }
    return num;
}

int main(void)
{
    int choice, num = 0;
    DuLinkedList head;
    head = NULL;

    do
    {
        show();
        choice = judge_int();
        system("cls");
        switch (choice)
        {
        case 1://����������
        {
            if (InitList_DuL(&head))
            {
                printf("���������ɹ�\n");
            }
            else
            {
                printf("��������ʧ��\n");
            }
            break;
        }
        case 2://��������
        {
            DestroyList_DuL(&head);
            printf("�������ٳɹ�\n");
            break;
        }
        case 3://ͷ�巨��������
        {
            if (head == NULL)
            {
                printf("����δ���������ȴ�������\n");
            }
            else
            {
                DuLinkedList newNode;
                if (InitList_DuL(&newNode))
                {
                    printf("���������ݣ�");
                    scanf("%d", &newNode->data);
                    if (InsertBeforeList_DuL(head, newNode))
                    {
                        printf("���ݲ���ɹ�\n");
                    }
                    else
                    {
                        printf("���ݲ���ʧ��\n");
                    }
                }
                else
                {
                    printf("���ݲ���ʧ��\n");
                }
            }
            break;
        }
        case 4://β�巨��������
        {
            if (head == NULL)
            {
                printf("����δ���������ȴ�������\n");
            }
            else
            {
                DuLinkedList newNode;
                if (InitList_DuL(&newNode))
                {
                    printf("���������ݣ�");
                    scanf("%d", &newNode->data);
                    if (InsertAfterList_DuL(head, newNode))
                    {
                        printf("���ݲ���ɹ�\n");
                    }
                    else
                    {
                        printf("���ݲ���ʧ��\n");
                    }
                }
                else
                {
                    printf("���ݲ���ʧ��\n");
                }
            }
            break;
        }
        case 5://ɾ������
        {
            if (head == NULL)
            {
                printf("����δ���������ȴ�������\n");
            }
            else
            {
                printf("����ɾ���ĸ����ݣ�");
                scanf("%d", &num);
                if (DeleteList_DuL(head, &num))
                {
                    printf("����ɾ���ɹ�\n");
                }
                else
                {
                    printf("����ɾ��ʧ��\n");
                }
            }
            break;
        }
        case 6://��������
        {
            TraverseList_DuL(head);
            break;
        }
        case 7://�˳����� 
        {
            DestroyList_DuL(&head);
            break;
        }
        default:
        {
            printf("��������������!(1-7)\n");
            break;
        }
        }
    } while (choice != 7);

    return 0;
}
