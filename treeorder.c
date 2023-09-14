#include <stdio.h>
#include <stdlib.h>

// 링크 트리 노드 구조체 정의
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 스택 노드 구조체 정의
struct StackNode {
    struct TreeNode* node;
    struct StackNode* next;
};

// 새로운 노드를 생성하는 함수(링크)
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 스택 초기화 함수
struct StackNode* createStack() {
    return NULL;
}

// 스택에 노드 추가 함수
void push(struct StackNode** stack, struct TreeNode* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->node = node;
    newNode->next = *stack;
    *stack = newNode;
}

// 스택에서 노드 꺼내는 함수
struct TreeNode* pop(struct StackNode** stack) {
    if (*stack == NULL) {
        return NULL;
    }
    struct StackNode* top = *stack;
    struct TreeNode* node = top->node;
    *stack = top->next;
    free(top);
    return node;
}

// 전위 순회 함수
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack = createStack();
    struct TreeNode* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            // 노드 출력
            printf(" %d", current->data);
            // 오른쪽 서브트리를 스택에 추가
            push(&stack, current->right);
            // 왼쪽 자식으로 이동
            current = current->left; 
        }
        // 스택에서 노드를 꺼내서 오른쪽 서브트리로 이동
        current = pop(&stack); 
    }
    // 스택 메모리 해제
    free(stack); 
}

// 중위 순회 함수
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack = createStack();
    struct TreeNode* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            // 현재 노드를 스택에 추가
            push(&stack, current); 
            // 왼쪽 자식으로 이동
            current = current->left; 
        }
        // 스택에서 노드를 꺼내서 출력
        current = pop(&stack); 
        printf(" %d", current->data);
        // 오른쪽 자식으로 이동
        current = current->right; 
    }
    //메모리 해제
    free(stack); 
}

// 후위 순회 함수
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack1 = createStack();
    struct StackNode* stack2 = createStack();
    struct TreeNode* current = root;

    push(&stack1, current);

    while (stack1 != NULL) {
        // 스택1에서 노드를 꺼내서 스택2에 추가
        current = pop(&stack1);
        push(&stack2, current);

        if (current->left != NULL) {
            push(&stack1, current->left);
        }
        if (current->right != NULL) {
            push(&stack1, current->right);
        }
    }

    while (stack2 != NULL) {
        // 스택2에서 노드를 꺼내서 출력
        current = pop(&stack2); 
        printf(" %d", current->data);
    }

    //메모리 해제
    free(stack1); 
    free(stack2); 
}

int main() {
    // 트리 생성
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

    printf("<Traversal with Stack>\n");

    printf("1.전위 순회:\n");
    preorderTraversal(root);
    printf("\n");

    printf("2.중위 순회:\n");
    inorderTraversal(root);
    printf("\n");

    printf("3.후위 순회:\n");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
