#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// ����AVL���ڵ�ṹ��
typedef struct AVLNode {
    int value;
    int height;
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// ��ȡ�ڵ�߶�
int getHeight(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// ��ȡƽ������
int getBalanceFactor(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

// ���½ڵ�߶�
void updateHeight(AVLNode* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// ����
AVLNode* rotateLeft(AVLNode* node) {
    AVLNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// ����
AVLNode* rotateRight(AVLNode* node) {
    AVLNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// ������
AVLNode* rotateLeftRight(AVLNode* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

// ������
AVLNode* rotateRightLeft(AVLNode* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

// ����ڵ�
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

// ���ҽڵ�
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

// ɾ���ڵ�
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

// �ݹ��������
void inorder(AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

// �ݹ�ǰ�����
void preorder(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->value);
        preorder(root->left);
        preorder(root->right);
    }
}

// �ݹ�������
void postorder(AVLNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->value);
    }
}

// ������
int main() {
    AVLNode* root = NULL;
    int choice, value;
    while (1) {
        printf("\n1. ����ڵ�\n");
        printf("2. ���ҽڵ�\n");
        printf("3. ɾ���ڵ�\n");
        printf("4. �������\n");
        printf("5. ǰ�����\n");
        printf("6. �������\n");
        printf("7. �˳�\n");
        printf("��ѡ�������");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("������Ҫ����Ľڵ�ֵ��");
            scanf("%d", &value);
            root = insert(root, value);
            printf("����ɹ���\n");
            break;
        case 2:
            printf("������Ҫ���ҵĽڵ�ֵ��");
            scanf("%d", &value);
            if (search(root, value) == NULL) {
                printf("�ýڵ㲻���ڣ�\n");
            }
            else {
                printf("�ýڵ���ڣ�\n");
            }
            break;
        case 3:
            printf("������Ҫɾ���Ľڵ�ֵ��");
            scanf("%d", &value);
            root = delete(root, value);
            printf("ɾ���ɹ���\n");
            break;
        case 4:
            printf("���������");
            inorder(root);
            printf("\n");
            break;
        case 5:
            printf("ǰ�������");
            preorder(root);
            printf("\n");
            break;
        case 6:
            printf("���������");
            postorder(root);
            printf("\n");
            break;
        case 7:
            printf("�˳�����\n");
            exit(0);
        default:
            printf("��������ȷ�Ĳ�����ţ�\n");
            break;
        }
    }
    return 0;
}