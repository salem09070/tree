#include <stdio.h>
#include <stdlib.h>

// ��ũ Ʈ�� ��� ����ü ����
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// ���� ��� ����ü ����
struct StackNode {
    struct TreeNode* node;
    struct StackNode* next;
};

// ���ο� ��带 �����ϴ� �Լ�(��ũ)
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ���� �ʱ�ȭ �Լ�
struct StackNode* createStack() {
    return NULL;
}

// ���ÿ� ��� �߰� �Լ�
void push(struct StackNode** stack, struct TreeNode* node) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->node = node;
    newNode->next = *stack;
    *stack = newNode;
}

// ���ÿ��� ��� ������ �Լ�
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

// ���� ��ȸ �Լ�
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack = createStack();
    struct TreeNode* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            // ��� ���
            printf(" %d", current->data);
            // ������ ����Ʈ���� ���ÿ� �߰�
            push(&stack, current->right);
            // ���� �ڽ����� �̵�
            current = current->left; 
        }
        // ���ÿ��� ��带 ������ ������ ����Ʈ���� �̵�
        current = pop(&stack); 
    }
    // ���� �޸� ����
    free(stack); 
}

// ���� ��ȸ �Լ�
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack = createStack();
    struct TreeNode* current = root;

    while (current != NULL || stack != NULL) {
        while (current != NULL) {
            // ���� ��带 ���ÿ� �߰�
            push(&stack, current); 
            // ���� �ڽ����� �̵�
            current = current->left; 
        }
        // ���ÿ��� ��带 ������ ���
        current = pop(&stack); 
        printf(" %d", current->data);
        // ������ �ڽ����� �̵�
        current = current->right; 
    }
    //�޸� ����
    free(stack); 
}

// ���� ��ȸ �Լ�
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct StackNode* stack1 = createStack();
    struct StackNode* stack2 = createStack();
    struct TreeNode* current = root;

    push(&stack1, current);

    while (stack1 != NULL) {
        // ����1���� ��带 ������ ����2�� �߰�
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
        // ����2���� ��带 ������ ���
        current = pop(&stack2); 
        printf(" %d", current->data);
    }

    //�޸� ����
    free(stack1); 
    free(stack2); 
}

int main() {
    // Ʈ�� ����
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

    printf("1.���� ��ȸ:\n");
    preorderTraversal(root);
    printf("\n");

    printf("2.���� ��ȸ:\n");
    inorderTraversal(root);
    printf("\n");

    printf("3.���� ��ȸ:\n");
    postorderTraversal(root);
    printf("\n");

    return 0;
}
