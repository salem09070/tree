#include <stdio.h>
#include <stdlib.h>
// �Ҹ� Ÿ�� ����
typedef enum { FALSE, TRUE } bool;

//��ũ Ʈ�� ��� ����ü ����
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// ���ο� ��带 �����ϴ� �Լ�(��ũ)
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ���� ��ȸ (Preorder Traversal) �Լ� (��ũ)
void preorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// ���� ��ȸ (Inorder Traversal) �Լ� (��ũ)
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// ���� ��ȸ (Postorder Traversal) �Լ� (��ũ)
void postorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// �迭�� ǥ���� Ʈ�� ���� ��ȸ �Լ�
void ArraypreorderTraversal(struct TreeNode* arr, int index, int size) {
    if (index < size && arr[index].data != 0) {
        printf("%d ", arr[index].data);
        ArraypreorderTraversal(arr, 2 * index + 1, size); // ���� �ڽ� ���
        ArraypreorderTraversal(arr, 2 * index + 2, size); // ������ �ڽ� ���
    }
}

// �迭�� ǥ���� Ʈ�� ���� ��ȸ �Լ�
void ArrayinorderTraversal(struct TreeNode* arr, int index, int size) {
    if (index < size && arr[index].data != 0) {
        ArrayinorderTraversal(arr, 2 * index + 1, size); // ���� �ڽ� ���
        printf("%d ", arr[index].data);
        ArrayinorderTraversal(arr, 2 * index + 2, size); // ������ �ڽ� ���
    }
}

// �迭�� ǥ���� Ʈ�� ���� ��ȸ �Լ�
void ArraypostorderTraversal(struct TreeNode* arr, int index, int size) {
    if (index < size && arr[index].data != 0) {
        ArraypostorderTraversal(arr, 2 * index + 1, size); // ���� �ڽ� ���
        ArraypostorderTraversal(arr, 2 * index + 2, size); // ������ �ڽ� ���
        printf("%d ", arr[index].data);
    }
}

int main() {
    // ��ũ�� ǥ���� Ʈ�� ����
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(7);
    root->left->left = createNode(3);
    root->left->right = createNode(6);
    root->right->left = createNode(8);
    root->right->right = createNode(9);
    root->left->left->left = createNode(4);
    root->left->left->right = createNode(5);
    root->right->right->left = createNode(10);
    root->right->right->right = createNode(11);

    printf("<Linked Tree>\n");
    printf("���� ��ȸ");
    preorderTraversal(root);
    printf("\n\n");

    printf("���� ��ȸ");
    inorderTraversal(root);
    printf("\n\n");

    printf("���� ��ȸ");
    postorderTraversal(root);
    printf("\n\n");

    // �迭�� ǥ���� Ʈ��
    struct TreeNode arr[] = {
        {1},
        {2}, {7},
        {3}, {6}, {8}, {9},
        {4}, {5}, {0}, {0}, {0}, {0}, {10}, {11}
    };

    int size = sizeof(arr) / sizeof(arr[0]);

    printf("<Array Tree>\n");
    printf("���� ��ȸ");
    ArraypreorderTraversal(arr, 0, size);
    printf("\n\n");

    printf("���� ��ȸ");
    ArrayinorderTraversal(arr, 0, size);
    printf("\n\n");

    printf("���� ��ȸ");
    ArraypostorderTraversal(arr, 0, size);
    printf("\n\n");

    return 0;
}
