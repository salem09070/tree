#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// �Լ� ������Ÿ��
Node* createNode(int data);
Node* insertRecursively(Node* root, int data, int* count);
Node* deleteRecursively(Node* root, int data, int* count);
int inorderTraversal(Node* root, int* count);
int searchIteratively(Node* root, int data, int* count);
Node* insertIteratively(Node* root, int data, int* count);
Node* findMinValueNode(Node* root);

int main() {
    Node* root = NULL;
    int visitedCount = 0;

    // �ʱ� Ʈ�� ����
    root = createNode(60);
    root->left = createNode(41);
    root->left->left = createNode(16);
    root->left->right = createNode(53);
    root->left->left->right = createNode(25);
    root->left->right->left = createNode(46);
    root->left->right->left->left = createNode(42);
    root->left->right->right = createNode(55);
    root->right = createNode(74);
    root->right->left = createNode(65);
    root->right->left->left = createNode(63);
    root->right->left->left->left = createNode(62);
    root->right->left->left->right = createNode(64);
    root->right->left->right = createNode(70);

    char choice;
    int data;
    while (1) {
        printf("�޴��� �������ּ��� (s/i/d/t/I/D/q): ");
        scanf(" %c", &choice);

        switch (choice) {
        case 's':
            printf("�˻��� �� �Է�: ");
            scanf("%d", &data);
            if (searchIteratively(root, data, &visitedCount)) {
                printf("�˻� ����: %d \n", data);
            }
            else {
                printf("%d Ʈ���� �����ϴ�.\n", data);
            }
            printf("\n�湮�� ��� ��: %d\n", visitedCount);
            visitedCount = 0; // ī��Ʈ �ʱ�ȭ
            break;
        case 'i':
            printf("������ �� �Է�: ");
            scanf("%d", &data);
            root = insertRecursively(root, data, &visitedCount);
            printf("�湮�� ��� ��: %d\n", visitedCount);
            visitedCount = 0; // ī��Ʈ �ʱ�ȭ
            break;
        case 'd':
            printf("������ �� �Է�: ");
            scanf("%d", &data);
            root = deleteRecursively(root, data, &visitedCount);
            printf("�湮�� ��� ��: %d\n", visitedCount);
            visitedCount = 0; // ī��Ʈ �ʱ�ȭ
            break;
        case 't':
            inorderTraversal(root, &visitedCount);
            printf("\n�湮�� ��� ��: %d\n", visitedCount);
            visitedCount = 0; // ī��Ʈ �ʱ�ȭ
            break;
        case 'I':
            printf("��� �߰�(�ݺ�): ");
            scanf("%d", &data);
            root = insertIteratively(root, data, &visitedCount);
            printf("\n�湮�� ��� ��: %d\n", visitedCount);
            visitedCount = 0; // ī��Ʈ �ʱ�ȭ
            break;
        case 'D':
            printf("��� ����(�ݺ�): ");
            scanf("%d", &data);
            // �ݺ����� ���� ����� �����Ǿ� �־�, ������� ���� �Լ��� ����ϰڽ��ϴ�.
            root = deleteRecursively(root, data, &visitedCount);
            printf("�湮�� ��� ��: %d\n", visitedCount);
            visitedCount = 0; // ī��Ʈ �ʱ�ȭ
            break;
        case 'q':
            return 0;
        default:
            printf("�ùٸ��� ���� �����Դϴ�.\n");
        }
        printf("\n������ȸ ���: ");
        inorderTraversal(root);
        printf("\n");
    }
    return 0;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertRecursively(Node* root, int data, int* count) {
    (*count)++;
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insertRecursively(root->left, data, count);
    }
    else if (data > root->data) {
        root->right = insertRecursively(root->right, data, count);
    }
    return root;
}

Node* deleteRecursively(Node* root, int data, int* count) {
    (*count)++;
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = deleteRecursively(root->left, data, count);
    }
    else if (data > root->data) {
        root->right = deleteRecursively(root->right, data, count);
    }
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = findMinValueNode(root->right);
        root->data = temp->data;
        root->right = deleteRecursively(root->right, temp->data, count);
    }
    return root;
}

int inorderTraversal(Node* root, int* count) {
    if (root != NULL) {
        inorderTraversal(root->left, count);
        (*count)++;
        printf("%d ", root->data);
        inorderTraversal(root->right, count);
    }
    return 0;
}

int searchIteratively(Node* root, int data, int* count) {
    while (root != NULL) {
        (*count)++;
        if (data < root->data) {
            root = root->left;
        }
        else if (data > root->data) {
            root = root->right;
        }
        else {
            return 1;  // ��� �߰�
        }
    }
    return 0;  // ��带 ã�� ����
}

Node* insertIteratively(Node* root, int data, int* count) {
    Node* newNode = createNode(data);
    if (root == NULL) {
        return newNode;
    }
    Node* current = root;
    Node* parent = NULL;
    while (current != NULL) {
        (*count)++;
        parent = current;
        if (data < current->data) {
            current = current->left;
        }
        else if (data > current->data) {
            current = current->right;
        }
        else {
            return root;  // �ߺ� ���� ������� �ʽ��ϴ�.
        }
    }
    if (data < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    return root;
}

Node* findMinValueNode(Node* root) {
    Node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
