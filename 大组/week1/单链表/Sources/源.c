#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef int ElemType;
typedef struct LNode
{
    ElemType data;//������
    struct LNode* next;//ָ����
} LNode, * LinkedList;
typedef enum Status {
    error,
    success
} Status;

//����������
Status InitList(LinkedList* L);//��ʼ������������һ���յ����Ա�
void DestroyList(LinkedList* L);
Status InsertList(LNode* p, ElemType data);
Status DeleteList(LNode* p, ElemType e);
void TraverseList(LinkedList L);
Status SearchList(LinkedList L, ElemType e);
Status ReverseList(LinkedList* L);
Status IsLoopList(LinkedList L);
LNode* FindMidNode(LinkedList L);
LNode* ReverseEvenList(LinkedList* L);
void show(void);
int judge_int(void);

Status InitList(LinkedList* L) //������ĳ�ʼ��
{
    LinkedList list;

    list = (LinkedList)malloc(sizeof(LNode));
    if (list == NULL)
    {
        printf("�ڴ����ʧ��\n");
        return error;
    }
    list->next = NULL;
    *L = list;

    return success;//���ɵ�һ���ڵ㣬����ɹ�����ֵ1
}

void DestroyList(LinkedList* L) {//ɾ������
    LinkedList temp;

    while (*L != NULL)
    {
        temp = *L;
        *L = (*L)->next;
        free(temp);
    }
}

Status InsertList(LNode* p, ElemType data) //��������
{
    LinkedList current = p;
    LinkedList newNode = (LinkedList)malloc(sizeof(LNode));

    if (newNode == NULL)
    {
        printf("�ڴ����ʧ��\n");
        return error;//�ж������Ƿ�Ϊ��
    }
    newNode->data = data;
    newNode->next = NULL;
    while (current->next != NULL)
    {
        current = current->next;//��ϵͳ������һ���ս��
    }
    current->next = newNode;//������Ԫ�ظ�ֵ��current->next
    return success;
}

Status DeleteList(LNode* p, ElemType e)//ɾ������
{
    LinkedList posNode = p->next;
    LinkedList posNodeFront = p;
    if (posNode == NULL)
    {
        printf("����Ϊ�գ��޷�ɾ��\n");
    }
    else
    {
        while (posNode->data != e)
        {
            posNodeFront = posNode;
            posNode = posNode->next;
            if (posNode == NULL)
            {
                printf("û�и�����\n");//�ж���������
                return error;
            }
        }
        posNodeFront->next = posNode->next;//������ǰ�̽���ָ���ƹ�ָ���̽��
        free(posNode);
        return success;
    }
}

void TraverseList(LinkedList L) //����
{
    LinkedList temp;

    temp = L->next;
    while (temp != NULL)
    {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

Status SearchList(LinkedList L, ElemType e) //��������
{
    while (L != NULL)
    {
        if (L->data == e)
        {
            return success;//���ҳɹ������ؽ�������
        }
        L = L->next;//������ǣ�����L��ָ������ƶ�������ָ����һ�����
    }
    return error;//��������ĩβLΪ�գ���˵��������
}




/*�ݹ�ʵ��
void ReverseList(LinkedList L) {
    LinkedList current, next, pre;
    current = L->next;
    pre = NULL;
    while(current != NULL)
    {
        next = current->next;
        current->next = pre;
        pre = current;�Ӻ���ǰ��ת
        current = next;
    }
    L->next = pre;
}
*/

Status ReverseList(LinkedList* L) //��ת����,����ʵ��
{
    LNode* newHead;		//����ÿ�η�ת��ĵ�һ���ڵ� 
    LNode* p1;			//ÿ�ζ�ָ��ǰһ���ڵ�	
    LNode* p2;			// ����δ��תǰ����һ���ڵ� 
    p1 = (*L)->next;//��ָ���¼��һ������λ�ã��ٷ�ת��ǰ����ָ��
    p2 = p1->next;
    p1->next = NULL;
    newHead = p1;
    while (p2 != NULL) {
        p1 = p2;
        p2 = p1->next;

        p1->next = newHead;
        newHead = p1;
    }
    (*L)->next = newHead;
}
LNode* ReverseEvenList(LinkedList* L)//������������ż�ڵ�
{
    LinkedList p, q, f;
    f = (LinkedList)malloc(sizeof(LNode));
    p = f;
    p->next = (*L);
    q = (*L);
    while (q != NULL && q->next != NULL)
    {
        p->next = q->next;
        q->next = p->next->next;
        p->next->next = q;
        p = q;
        q = q->next;//��ż����
    }
    (*L) = f->next;
    f->next = NULL;
    free(f);

    return *L;
}


LNode* FindMidNode(LinkedList L) //�����м���
{
    LinkedList slow = L, fast = L;//���ÿ���ָ��
    while (fast != NULL && slow != NULL)
    {
        fast = fast->next->next; //��ָ��ÿ������������ָ��ÿ����һ��
        slow = slow->next;
    }
    return slow;//����ָ���ߵ�β����ָ�������ߵ��м�ڵ�
}

Status IsLoopList(LinkedList L) //�ж������Ƿ�ɻ�
{
    LinkedList fast = L, slow = L;////���ÿ���ָ��
    while (fast->next != NULL && slow->next != NULL)
    {
        slow = slow->next;
        if ((fast = fast->next->next) == NULL)
            return error;
        if (fast == slow)//��ָ��slow��fast��������б�������ָ��slowÿ����һ������ָ��fastÿ�����������������ɻ���������󶼻�������
            return success;
    }
    return error;
}

void show(void)
{
    printf("\n\n\n\n������ADT\n\n");
    printf("1.����������\n");
    printf("2.��������\n");
    printf("3.������\n");
    printf("4.ɾ�����\n");
    printf("5.��������\n");
    printf("6.��������\n");
    printf("7.��ת����\n");
    printf("8.�ж������Ƿ�ɻ�\n");
    printf("9.������������ż�ڵ�\n");
    printf("10.�����м���\n");
    printf("11.�˳�\n");
    printf("\n�������Ӧ������(1-11)��");
}

int judge_int(void)  //��ֹ�û��������������ַ�
{
    int len, num = 0, arg = 1;
    char word[10];
    int m, j = 1, k;
    while (j)
    {
        scanf_s("%s", word,9);
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
    LinkedList head = NULL;

    do
    {
        show();
        choice = judge_int();
        system("cls");
        switch (choice)
        {
        case 1://����������
        {
            if (InitList(&head))
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
            DestroyList(&head);
            printf("�����������\n");
            break;
        }
        case 3://��������
        {
            if (head == NULL)
            {
                printf("����Ϊ�գ� ���ȴ�������\n");
            }
            else
            {
                printf("���������ݣ�");
                scanf_s("%d", &num);
                if (InsertList(head, num))
                {
                    printf("���ݲ���ɹ�\n");
                }
                else
                {
                    printf("���ݲ���ʧ��\n");
                }
            }
            break;
        }
        case 4://ɾ������
        {
            printf("����ɾ���ĸ����ݣ�");
            scanf_s("%d", &num);
            if (DeleteList(head, num))
            {
                printf("����ɾ���ɹ�\n");
            }
            else
            {
                printf("����ɾ��ʧ��\n");
            }
            break;
        }
        case 5://��������
        {
            if (head == NULL || head->next == NULL)
            {
                printf("�������ڻ���ֻ����һ���յ�ͷ���\n");
            }
            else
            {
                TraverseList(head);
            }
            break;
        }
        case 6://��������
        {
            printf("��������Ҫ���ҵ����ݣ�");
            scanf_s("%d", &num);
            if (SearchList(head, num))
            {
                printf("��������\n");
            }
            else
            {
                printf("����������\n");
            }
            break;
        }
        case 7://��ת����
        {
            if (head == NULL || head->next == NULL)
            {
                printf("����Ϊ�ջ�������ֻ�����������\n");
                printf("����תʧ��\n");
            }
            else
            {
                if (ReverseList(&head))
                {
                    printf("����ת�ɹ�\n");
                }
                else
                {
                    printf("����תʧ��\n");
                }

            }
            break;
        }
        case 8://�ж������Ƿ�ɻ�
        {
            if (head == NULL || head->next == NULL)
            {
                printf("����Ϊ��\n");
            }
            else
            {
                if (IsLoopList(head))
                {
                    printf("����ɻ�\n");
                }
                else
                {
                    printf("����û�гɻ�\n");
                }
            }
            break;
        }
        case 9://������������ż�ڵ�
        { 
            if (head == NULL || head->next == NULL)
        {
                printf("����Ϊ��\n");
        }
        else
        {
            if (ReverseEvenList(&head))
            {
                printf("�����ɹ�\n");
            }
            else
            {
                printf("����ʧ��\n");
            }

        }
            break;
        }
        case 10://�����м���
        {
            if (head == NULL || head->next == NULL)
            {
                printf("���ǿ�����\n");
            }
            else
            {
                printf("�����м䴢���ֵΪ%d\n", (FindMidNode(head))->data);
            }
            break;
        }
        case 11://��������
        {
            DestroyList(&head);
            break;
        }
        default:
        {
            printf("�������������֣�(1-11)\n");
            break;
        }
        }
    } while (choice != 11);

    return 0;
}
