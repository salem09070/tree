#include <stdio.h>
#include <stdlib.h>
// 불린 타입 정의
typedef enum { FALSE, TRUE } bool;

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
    int is_thread;  // 1 if right child is thread, 0 otherwise
} TreeNode;
// 트리 노드 초기화
TreeNode n11 = { 11, NULL, NULL, 0 };
TreeNode n10 = { 10, NULL, NULL, 0 };
TreeNode n8 = { 8, NULL, NULL, 0 };
TreeNode n6 = { 6, NULL, NULL, 0 };
TreeNode n5 = { 5, NULL, NULL, 0 };
TreeNode n4 = { 4, NULL, NULL, 0 };
TreeNode n9 = { 9, &n10, &n11, 0 };
TreeNode n7 = { 7, &n8, &n9, 0 };
TreeNode n3 = { 3, &n4, &n5, 0 };
TreeNode n2 = { 2, &n3, &n6, 0 };
TreeNode n1 = { 1, &n2, &n7, 0 };
TreeNode* root = &n1;


// 스레드를 사용하여 중위 후속자 찾기
TreeNode* find_successor(TreeNode* p) {
    TreeNode* q = p->right;
    if (q == NULL || p->is_thread == TRUE) return q;
    while (q->left != NULL)
        q = q->left;
    return q;
}
// 스레드를 사용한 중위 순회 함수
void thread_inorder(TreeNode* p) {
    printf("1. 중위 순회 결과 \n");
    TreeNode* q;
    q = p;
    while (q->left != NULL)
        q = q->left;
    do {
        printf("%d ", q->data);
        q = find_successor(q);
    } while (q);
}
// 주어진 노드의 부모를 찾는 함수
TreeNode* parent(TreeNode* child) {
    TreeNode* q = child->right;
    TreeNode* ql = q->left;
    if (q == NULL)
        return;
    else if (q->left == child || q->right == child) {
        printf("%d \n", q->data);
        return;
    }
    else if (ql->left == child || ql->right == child) {
        printf("%d \n", ql->data);
        return;
    }
    else {
        printf("error");
        exit(1);
    }
}



int main() {
    // 스레드 설정
    n4.right = &n3;  n4.is_thread = 1;
    n5.right = &n2;  n5.is_thread = 1;
    n6.right = &n1;  n6.is_thread = 1;
    n8.right = &n7;  n8.is_thread = 1;
    n10.right = &n9; n10.is_thread = 1;
    // 중위 순회 결과 출력
    thread_inorder(root);
    printf("\n");
    // 노드 4, 5, 6의 부모를 출력
    printf("2. Node4의 부모 : ");
    parent(&n4);
    printf("3. Node5의 부모 : ");
    parent(&n5);
    printf("4. Node6의 부모 : ");
    parent(&n6);


    return 0;
}
