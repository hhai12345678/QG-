#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef int ElemType;
typedef struct LNode
{
    ElemType data;//数据域
    struct LNode* next;//指针域
} LNode, * LinkedList;
typedef enum Status {
    error,
    success
} Status;

//函数的声明
Status InitList(LinkedList* L);//初始化操作，建立一个空的线性表
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

Status InitList(LinkedList* L) //单链表的初始化
{
    LinkedList list;

    list = (LinkedList)malloc(sizeof(LNode));
    if (list == NULL)
    {
        printf("内存分配失败\n");
        return error;
    }
    list->next = NULL;
    *L = list;

    return success;//生成第一个节点，如果成功返回值1
}

void DestroyList(LinkedList* L) {//删除链表
    LinkedList temp;

    while (*L != NULL)
    {
        temp = *L;
        *L = (*L)->next;
        free(temp);
    }
}

Status InsertList(LNode* p, ElemType data) //插入数据
{
    LinkedList current = p;
    LinkedList newNode = (LinkedList)malloc(sizeof(LNode));

    if (newNode == NULL)
    {
        printf("内存分配失败\n");
        return error;//判断链表是否为空
    }
    newNode->data = data;
    newNode->next = NULL;
    while (current->next != NULL)
    {
        current = current->next;//在系统中生成一个空结点
    }
    current->next = newNode;//将数据元素赋值给current->next
    return success;
}

Status DeleteList(LNode* p, ElemType e)//删除数据
{
    LinkedList posNode = p->next;
    LinkedList posNodeFront = p;
    if (posNode == NULL)
    {
        printf("链表为空，无法删除\n");
    }
    else
    {
        while (posNode->data != e)
        {
            posNodeFront = posNode;
            posNode = posNode->next;
            if (posNode == NULL)
            {
                printf("没有该数据\n");//判断有无数据
                return error;
            }
        }
        posNodeFront->next = posNode->next;//将他的前继结点的指针绕过指向后继结点
        free(posNode);
        return success;
    }
}

void TraverseList(LinkedList L) //遍历
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

Status SearchList(LinkedList L, ElemType e) //查找数据
{
    while (L != NULL)
    {
        if (L->data == e)
        {
            return success;//查找成功，返回结点的数据
        }
        L = L->next;//如果不是，就让L的指针向后移动，不断指向下一个结点
    }
    return error;//若到链表末尾L为空，则说明不存在
}




/*递归实现
void ReverseList(LinkedList L) {
    LinkedList current, next, pre;
    current = L->next;
    pre = NULL;
    while(current != NULL)
    {
        next = current->next;
        current->next = pre;
        pre = current;从后向前反转
        current = next;
    }
    L->next = pre;
}
*/

Status ReverseList(LinkedList* L) //反转链表,迭代实现
{
    LNode* newHead;		//储存每次反转后的第一个节点 
    LNode* p1;			//每次都指向前一个节点	
    LNode* p2;			// 储存未反转前的下一个节点 
    p1 = (*L)->next;//用指针记录下一个结点的位置，再反转当前结点的指向
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
LNode* ReverseEvenList(LinkedList* L)//交换单链表奇偶节点
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
        q = q->next;//奇偶交互
    }
    (*L) = f->next;
    f->next = NULL;
    free(f);

    return *L;
}


LNode* FindMidNode(LinkedList L) //查找中间结点
{
    LinkedList slow = L, fast = L;//设置快慢指针
    while (fast != NULL && slow != NULL)
    {
        fast = fast->next->next; //快指针每次走两步，慢指针每次走一步
        slow = slow->next;
    }
    return slow;//待快指针走到尾，慢指针正好走到中间节点
}

Status IsLoopList(LinkedList L) //判断链表是否成环
{
    LinkedList fast = L, slow = L;////设置快慢指针
    while (fast->next != NULL && slow->next != NULL)
    {
        slow = slow->next;
        if ((fast = fast->next->next) == NULL)
            return error;
        if (fast == slow)//用指针slow和fast对链表进行遍历，慢指针slow每次走一步，快指针fast每次走两步，如果链表成环，它们最后都会相遇。
            return success;
    }
    return error;
}

void show(void)
{
    printf("\n\n\n\n单链表ADT\n\n");
    printf("1.创建空链表\n");
    printf("2.销毁链表\n");
    printf("3.插入结点\n");
    printf("4.删除结点\n");
    printf("5.遍历链表\n");
    printf("6.查找数据\n");
    printf("7.反转链表\n");
    printf("8.判断链表是否成环\n");
    printf("9.交换单链表奇偶节点\n");
    printf("10.查找中间结点\n");
    printf("11.退出\n");
    printf("\n请输入对应的数字(1-11)：");
}

int judge_int(void)  //防止用户乱输入其他的字符
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
            if (word[m] < '0' || word[m]>'9')  //检验是否有乱输入其他字符
            {
                printf("请输入整数：");
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
    for (m = 0; m < len; m++)  // 将字符重新转换为数字
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
        case 1://创建空链表
        {
            if (InitList(&head))
            {
                printf("空链表创建成功\n");
            }
            else
            {
                printf("空链表创建失败\n");
            }
            break;
        }
        case 2://销毁链表
        {
            DestroyList(&head);
            printf("链表销毁完成\n");
            break;
        }
        case 3://插入数据
        {
            if (head == NULL)
            {
                printf("链表为空， 请先创建链表\n");
            }
            else
            {
                printf("请输入数据：");
                scanf_s("%d", &num);
                if (InsertList(head, num))
                {
                    printf("数据插入成功\n");
                }
                else
                {
                    printf("数据插入失败\n");
                }
            }
            break;
        }
        case 4://删除数据
        {
            printf("你想删除哪个数据：");
            scanf_s("%d", &num);
            if (DeleteList(head, num))
            {
                printf("数据删除成功\n");
            }
            else
            {
                printf("数据删除失败\n");
            }
            break;
        }
        case 5://遍历链表
        {
            if (head == NULL || head->next == NULL)
            {
                printf("链表不存在或者只存在一个空的头结点\n");
            }
            else
            {
                TraverseList(head);
            }
            break;
        }
        case 6://查找数据
        {
            printf("请输入你要查找的数据：");
            scanf_s("%d", &num);
            if (SearchList(head, num))
            {
                printf("该数存在\n");
            }
            else
            {
                printf("该数不存在\n");
            }
            break;
        }
        case 7://反转链表
        {
            if (head == NULL || head->next == NULL)
            {
                printf("链表为空或者链表只含有两个结点\n");
                printf("链表反转失败\n");
            }
            else
            {
                if (ReverseList(&head))
                {
                    printf("链表反转成功\n");
                }
                else
                {
                    printf("链表反转失败\n");
                }

            }
            break;
        }
        case 8://判断链表是否成环
        {
            if (head == NULL || head->next == NULL)
            {
                printf("链表为空\n");
            }
            else
            {
                if (IsLoopList(head))
                {
                    printf("链表成环\n");
                }
                else
                {
                    printf("链表没有成环\n");
                }
            }
            break;
        }
        case 9://交换单链表奇偶节点
        { 
            if (head == NULL || head->next == NULL)
        {
                printf("链表为空\n");
        }
        else
        {
            if (ReverseEvenList(&head))
            {
                printf("交换成功\n");
            }
            else
            {
                printf("交换失败\n");
            }

        }
            break;
        }
        case 10://查找中间结点
        {
            if (head == NULL || head->next == NULL)
            {
                printf("这是空链表\n");
            }
            else
            {
                printf("链表中间储存的值为%d\n", (FindMidNode(head))->data);
            }
            break;
        }
        case 11://销毁链表
        {
            DestroyList(&head);
            break;
        }
        default:
        {
            printf("请重新输入数字！(1-11)\n");
            break;
        }
        }
    } while (choice != 11);

    return 0;
}
