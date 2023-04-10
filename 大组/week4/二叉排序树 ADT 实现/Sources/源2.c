#include <stdio.h>
#include <stdlib.h>

// ��������������Ľṹ��
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode, * Tree;

// ����һ���½ڵ�
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// �ݹ���ҽڵ�
TreeNode* search(Tree root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (root->data > data) {
        return search(root->left, data);
    }
    else {
        return search(root->right, data);
    }
}

// �ǵݹ���ҽڵ�
TreeNode* searchNoRecursion(Tree root, int data) {
    while (root != NULL && root->data != data) {
        if (root->data > data) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return root;
}

// ����ڵ�
Tree insert(Tree root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (root->data > data) {
        root->left = insert(root->left, data);
    }
    else if (root->data < data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// ɾ���ڵ�
Tree delete(Tree root, int data) {
    if (root == NULL) {
        return root;
    }
    if (root->data > data) {
        root->left = delete(root->left, data);
    }
    else if (root->data < data) {
        root->right = delete(root->right, data);
    }
    else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        else {
            TreeNode* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->data = temp->data;
            root->right = delete(root->right, temp->data);
        }
    }
    return root;
}

// �ݹ�ǰ�����
void preOrderTraversal(Tree root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

// �ǵݹ�ǰ�����
void preOrderTraversalNoRecursion(Tree root) {
    if (root == NULL) {
        return;
    }
    TreeNode* stack[100];
    int top = -1;
    stack[++top] = root;
    while (top != -1) {
        TreeNode* p = stack[top--];
        printf("%d ", p->data);
        if (p->right != NULL) {
            stack[++top] = p->right;
        }
        if (p->left != NULL) {
            stack[++top] = p->left;
        }
    }
}

// �ݹ��������
void inOrderTraversal(Tree root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

// �ǵݹ��������
void inOrderTraversalNoRecursion(Tree root) {
    if (root == NULL) {
        return;
    }
    TreeNode* stack[100];
    int top = -1;
    TreeNode* p = root;
    while (top != -1 || p != NULL) {
        while (p != NULL) {
            stack[++top] = p;
            p = p->left;
        }
        if (top != -1) {
            p = stack[top--];
            printf("%d ", p->data);
            p = p->right;
        }
    }
}

// �ݹ�������
void postOrderTraversal(Tree root) {
    if (root == NULL) {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
}

// �ǵݹ�������
void postOrderTraversalNoRecursion(Tree root) {
    if (root == NULL) {
        return;
    }
    TreeNode* stack[100];
    int top = -1;
    TreeNode* p = root;
    TreeNode* lastVisit = NULL;
    while (p != NULL) {
        stack[++top] = p;
        p = p->left;
    }
    while (top != -1) {
        p = stack[top--];
        if (p->right == NULL || p->right == lastVisit) {
            printf("%d ", p->data);
            lastVisit = p;
        }
        else {
            stack[++top] = p;
            p = p->right;
            while (p != NULL) {
                stack[++top] = p;
                p = p->left;
            }
        }
    }
}

// �������
void levelOrderTraversal(Tree root) {
    if (root == NULL) {
        return;
    }
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front != rear) {
        TreeNode* p = queue[front++];
        printf("%d ", p->data);
        if (p->left != NULL) {
            queue[rear++] = p->left;
        }
        if (p->right != NULL) {
            queue[rear++] = p->right;
        }
    }
}

int main() {
    Tree root = NULL;
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 1);
    insert(root, 4);
    insert(root, 7);
    insert(root, 6);
    insert(root, 8);
    printf("�ݹ�ǰ�������");
    preOrderTraversal(root);
    printf("\n�ǵݹ�ǰ�������");
    preOrderTraversalNoRecursion(root);
    printf("\n�ݹ����������");
    inOrderTraversal(root);
    printf("\n�ǵݹ����������");
    inOrderTraversalNoRecursion(root);
    printf("\n�ݹ���������");
    postOrderTraversal(root);
    printf("\n�ǵݹ���������");
    postOrderTraversalNoRecursion(root);
    printf("\n���������");
    levelOrderTraversal(root);
    printf("\nɾ�����3������������");
    root = delete(root, 3);
    inOrderTraversal(root);
    printf("\n");
    return 0;
}
