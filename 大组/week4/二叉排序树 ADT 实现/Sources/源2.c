#include <stdio.h>
#include <stdlib.h>

// 定义二叉排序树的结构体
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode, * Tree;

// 创建一个新节点
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 递归查找节点
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

// 非递归查找节点
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

// 插入节点
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

// 删除节点
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

// 递归前序遍历
void preOrderTraversal(Tree root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

// 非递归前序遍历
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

// 递归中序遍历
void inOrderTraversal(Tree root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

// 非递归中序遍历
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

// 递归后序遍历
void postOrderTraversal(Tree root) {
    if (root == NULL) {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
}

// 非递归后序遍历
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

// 层序遍历
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
    printf("递归前序遍历：");
    preOrderTraversal(root);
    printf("\n非递归前序遍历：");
    preOrderTraversalNoRecursion(root);
    printf("\n递归中序遍历：");
    inOrderTraversal(root);
    printf("\n非递归中序遍历：");
    inOrderTraversalNoRecursion(root);
    printf("\n递归后序遍历：");
    postOrderTraversal(root);
    printf("\n非递归后序遍历：");
    postOrderTraversalNoRecursion(root);
    printf("\n层序遍历：");
    levelOrderTraversal(root);
    printf("\n删除结点3后的中序遍历：");
    root = delete(root, 3);
    inOrderTraversal(root);
    printf("\n");
    return 0;
}
