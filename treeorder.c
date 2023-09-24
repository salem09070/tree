#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int nodeCount = 0;  // 전역 변수로 노드 카운트를 추적

double evaluate(Node* root) {
    if (!root) return 0;

    nodeCount++;  // 노드 방문

    if (root->data >= '0' && root->data <= '9') return root->data - '0';

    double leftValue = evaluate(root->left);
    double rightValue = evaluate(root->right);

    printf("%.2f %c %.2f = ", leftValue, root->data, rightValue);

    switch (root->data) {
    case '+':
        printf("%.2f\n", leftValue + rightValue);
        return leftValue + rightValue;
    case '-':
        printf("%.2f\n", leftValue - rightValue);
        return leftValue - rightValue;
    case '*':
        printf("%.2f\n", leftValue * rightValue);
        return leftValue * rightValue;
    case '/':
        printf("%.2f\n", leftValue / rightValue);
        return leftValue / rightValue;
    }

    return 0;
}

int main() {
    Node* root = newNode('+');
    root->left = newNode('-');
    root->right = newNode('9');
    root->left->left = newNode('+');
    root->left->right = newNode('/');
    root->left->left->left = newNode('+');
    root->left->left->right = newNode('*');
    root->left->left->left->left = newNode('2');
    root->left->left->left->right = newNode('3');
    root->left->left->right->left = newNode('4');
    root->left->left->right->right = newNode('5');
    root->left->right->left = newNode('6');
    root->left->right->right = newNode('7');

    printf("수식의 값은 : %.2f 입니다.\n\n", evaluate(root));
    printf("총 노드의 수는: %d 개 입니다.\n", nodeCount);

    return 0;
}