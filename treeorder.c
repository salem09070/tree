#include <stdio.h>
#include <stdlib.h>

//링크 트리 노드 구조체 정의
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 새로운 노드를 생성하는 함수(링크)
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 전위 순회 (Preorder Traversal) 함수 (링크)
void preorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// 중위 순회 (Inorder Traversal) 함수 (링크)
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// 후위 순회 (Postorder Traversal) 함수 (링크)
void postorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// 배열로 표현한 트리 전위 순회 함수
void ArraypreorderTraversal(struct TreeNode* arr, int index, int size) {
    if (index < size && arr[index].data != 0) {
        printf("%d ", arr[index].data);
        ArraypreorderTraversal(arr, 2 * index + 1, size); // 왼쪽 자식 노드
        ArraypreorderTraversal(arr, 2 * index + 2, size); // 오른쪽 자식 노드
    }
}

// 배열로 표현한 트리 중위 순회 함수
void ArrayinorderTraversal(struct TreeNode* arr, int index, int size) {
    if (index < size && arr[index].data != 0) {
        ArrayinorderTraversal(arr, 2 * index + 1, size); // 왼쪽 자식 노드
        printf("%d ", arr[index].data);
        ArrayinorderTraversal(arr, 2 * index + 2, size); // 오른쪽 자식 노드
    }
}

// 배열로 표현한 트리 후위 순회 함수
void ArraypostorderTraversal(struct TreeNode* arr, int index, int size) {
    if (index < size && arr[index].data != 0) {
        ArraypostorderTraversal(arr, 2 * index + 1, size); // 왼쪽 자식 노드
        ArraypostorderTraversal(arr, 2 * index + 2, size); // 오른쪽 자식 노드
        printf("%d ", arr[index].data);
    }
}

int main() {
    // 링크로 표현한 트리 생성
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
    printf("전위 순회");
    preorderTraversal(root);
    printf("\n\n");

    printf("중위 순회");
    inorderTraversal(root);
    printf("\n\n");

    printf("후위 순회");
    postorderTraversal(root);
    printf("\n\n");

    // 배열로 표현한 트리
    struct TreeNode arr[] = {
        {1},
        {2}, {7},
        {3}, {6}, {8}, {9},
        {4}, {5}, {0}, {0}, {0}, {0}, {10}, {11}
    };

    int size = sizeof(arr) / sizeof(arr[0]);

    printf("<Array Tree>\n");
    printf("전위 순회");
    ArraypreorderTraversal(arr, 0, size);
    printf("\n\n");

    printf("중위 순회");
    ArrayinorderTraversal(arr, 0, size);
    printf("\n\n");

    printf("후위 순회");
    ArraypostorderTraversal(arr, 0, size);
    printf("\n\n");

    return 0;
}
