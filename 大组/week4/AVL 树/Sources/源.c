#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// 定义AVL树节点结构体
typedef struct AVLNode {
    int value;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// 获取节点高度
int getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// 获取平衡因子
int getBalanceFactor(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// 更新节点高度
void updateHeight(AVLNode* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// 左旋
AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// 右旋
AVLNode* rotateRight(AVLNode* node) {
    AVLNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// 左右旋
AVLNode* rotateLeftRight(AVLNode* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// 右左旋
AVLNode* rotateRightLeft(AVLNode* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// 插入节点
AVLNode* insert(AVLNode* root, int value) {
    if (root == NULL) {
        AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
        node->value = value;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
        updateHeight(root);
        if (getBalanceFactor(root) == 2) {
            if (getBalanceFactor(root->left) == 1) {
                root = rotateRight(root);
            }
            else {
                root = rotateLeftRight(root);
            }
        }
    }
    else {
        root->right = insert(root->right, value);
        updateHeight(root);
        if (getBalanceFactor(root) == -2) {
            if (getBalanceFactor(root->right) == -1) {
                root = rotateLeft(root);
            }
            else {
                root = rotateRightLeft(root);
            }
        }
    }
    return root;
}

// 查找节点
AVLNode* search(AVLNode* root, int value) {
    if (root == NULL) {
        return NULL;
    }
    if (root->value == value) {
        return root;
    }
    else if (value < root->value) {
        return search(root->left, value);
    }
    else {
        return search(root->right, value);
    }
}

// 删除节点
AVLNode* delete(AVLNode* root, int value) {
    if (root == NULL) {
        return NULL;
    }
    if (value < root->value) {
        root->left = delete(root->left, value);
        updateHeight(root);
        if (getBalanceFactor(root) == -2) {
            if (getBalanceFactor(root->right) == -1) {
                root = rotateLeft(root);
            }
            else {
                root = rotateRightLeft(root);
            }
        }
    }
    else if (value > root->value) {
        root->right = delete(root->right, value);
        updateHeight(root);
        if (getBalanceFactor(root) == 2) {
            if (getBalanceFactor(root->left) == 1) {
                root = rotateRight(root);
            }
            else {
                root = rotateLeftRight(root);
            }
        }
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            AVLNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            AVLNode* temp = root->left;
            free(root);
            return temp;
        }
        else {
            AVLNode* temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->value = temp->value;
            root->right = delete(root->right, temp->value);
            updateHeight(root);
            if (getBalanceFactor(root) == 2) {
                if (getBalanceFactor(root->left) == 1) {
                    root = rotateRight(root);
                }
                else {
                    root = rotateLeftRight(root);
                }
            }
        }
    }
    return root;
}

// 递归中序遍历
void inorder(AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

// 递归前序遍历
void preorder(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

// 递归后序遍历
void postorder(AVLNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
}

// 主函数
int main() {
    AVLNode* root = NULL;
    int choice, value;
    while (1) {
        printf("\n1. 插入节点\n");
        printf("2. 查找节点\n");
        printf("3. 删除节点\n");
        printf("4. 中序遍历\n");
        printf("5. 前序遍历\n");
        printf("6. 后序遍历\n");
        printf("7. 退出\n");
        printf("请选择操作：");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("请输入要插入的节点值：");
            scanf("%d", &value);
            root = insert(root, value);
            printf("插入成功！\n");
            break;
        case 2:
            printf("请输入要查找的节点值：");
            scanf("%d", &value);
            if (search(root, value) == NULL) {
                printf("该节点不存在！\n");
            }
            else {
                printf("该节点存在！\n");
            }
            break;
        case 3:
            printf("请输入要删除的节点值：");
            scanf("%d", &value);
            root = delete(root, value);
            printf("删除成功！\n");
            break;
        case 4:
            printf("中序遍历：");
            inorder(root);
            printf("\n");
            break;
        case 5:
            printf("前序遍历：");
            preorder(root);
            printf("\n");
            break;
        case 6:
            printf("后序遍历：");
            postorder(root);
            printf("\n");
            break;
        case 7:
            printf("退出程序！\n");
            exit(0);
        default:
            printf("请输入正确的操作序号！\n");
            break;
        }
    }
    return 0;
}