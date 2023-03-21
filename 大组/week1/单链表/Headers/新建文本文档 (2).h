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