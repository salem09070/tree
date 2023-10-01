#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
typedef struct Node {
    int data;               // ������ �ʵ�
    struct Node* left;      // ���� �ڽ� ��带 ����Ű�� ������
    struct Node* right;     // ������ �ڽ� ��带 ����Ű�� ������
} Node;

Node* root = NULL;          // Ʈ���� ��Ʈ ��带 ����Ű�� ������

int visitedNodes = 0;       // �湮�� ����� ��

// �� ��� ���� �Լ�
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Ư�� �����͸� ���� ��� �˻� �Լ�
void search(int data) {
    Node* temp = root;
    visitedNodes = 0;

    while (temp != NULL) {
        visitedNodes++;
        if (data == temp->data) {
            printf("�湮�� ���� : %d .\n", visitedNodes);
            return;
        }
        else if (data < temp->data) {
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }
    printf("�湮�� ���� : %d .\n", visitedNodes);
}

// ��������� ��� ���� �Լ�
Node* insertRecursive(Node* node, int data) {
    visitedNodes++;

    if (node == NULL) {
        return createNode(data);
    }

    if (data < node->data) {
        node->left = insertRecursive(node->left, data);
    }
    else if (data > node->data) {
        node->right = insertRecursive(node->right, data);
    }
    return node;
}

// ��������� ��� ���� �Լ�
Node* deleteRecursive(Node* node, int data) {
    visitedNodes++;

    if (node == NULL) return node;

    if (data < node->data) {
        node->left = deleteRecursive(node->left, data);
    }
    else if (data > node->data) {
        node->right = deleteRecursive(node->right, data);
    }
    else {
        if (node->left == NULL) {
            Node* temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            Node* temp = node->left;
            free(node);
            return temp;
        }

        Node* temp = node->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        node->data = temp->data;
        node->right = deleteRecursive(node->right, temp->data);
    }
    return node;
}

// ���� ��ȸ �Լ�
void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        visitedNodes++;
        inorderTraversal(node->right);
    }
}

// �ݺ������� ��� ���� �Լ�
void insertIterative(int data) {
    Node* newNode = createNode(data);
    Node* current = root;
    Node* parent = NULL;

    visitedNodes = 0;

    while (current != NULL) {
        visitedNodes++;
        parent = current;

        if (data < current->data) {
            current = current->left;
        }
        else if (data > current->data) {
            current = current->right;
        }
        else {
            return;  // �ߺ� ������
        }
    }

    if (parent == NULL) {
        root = newNode;
    }
    else if (data < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
}

// �ݺ������� ��� ���� �Լ�
void deleteIterative(int data) {
    if (root == NULL) return;

    Node* current = root;
    Node* parent = NULL;

    visitedNodes = 0;

    while (current != NULL && current->data != data) {
        visitedNodes++;
        parent = current;
        if (data < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Data not found.\n");
        return;
    }

    if (current->left == NULL || current->right == NULL) {
        Node* temp;
        if (current->left == NULL) {
            temp = current->right;
        }
        else {
            temp = current->left;
        }

        if (parent == NULL) {
            root = temp;
        }
        else if (parent->left == current) {
            parent->left = temp;
        }
        else {
            parent->right = temp;
        }
    }
    else {
        Node* temp = current->right;
        Node* tempParent = current;
        while (temp->left != NULL) {
            tempParent = temp;
            temp = temp->left;
        }
        current->data = temp->data;
        if (tempParent->left == temp) {
            tempParent->left = temp->right;
        }
        else {
            tempParent->right = temp->right;
        }
    }
    free(current);
    printf("�湮�� ���� : %d .\n", visitedNodes);
}

int main() {
    char choice;

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

    do {
        printf("\nMenu:\n");
        printf("s: �˻�\n");
        printf("i: ��� �߰�\n");
        printf("d: ������\n");
        printf("t: ������ȸ\n");
        printf("I: ��� �߰�(�ݺ�)\n");
        printf("D: ��� ����(�ݺ�)\n");
        printf("c: ����\n");
        printf("�޴��Է�: ");
        scanf(" %c", &choice);

        int data;

        switch (choice) {
        case 's':
            printf("�˻��� �� �Է�: ");
            scanf("%d", &data);
            search(data);
            inorderTraversal(root);
            break;

        case 'i':
            printf("������ �� �Է�: ");
            scanf("%d", &data);
            visitedNodes = 0;
            root = insertRecursive(root, data);
            printf("�湮�� ���� : %d .\n", visitedNodes);
            inorderTraversal(root);
            break;

        case 'd':
            printf("���� �� �� �Է�: ");
            scanf("%d", &data);
            visitedNodes = 0;
            root = deleteRecursive(root, data);
            printf("�湮�� ���� : %d .\n", visitedNodes);
            inorderTraversal(root);
            break;

        case 't':
            visitedNodes = 0;
            inorderTraversal(root);
            printf("\n");
            printf("�湮�� ���� : %d .\n", visitedNodes);
            break;

        case 'I':
            printf("������ �� �Է�: ");
            scanf("%d", &data);
            visitedNodes = 0;
            insertIterative(data);
            printf("�湮�� ���� : %d .\n", visitedNodes);
            inorderTraversal(root);
            break;

        case 'D':
            printf("������ �� �Է�: ");
            scanf("%d", &data);
            visitedNodes = 0;
            deleteIterative(data);
            printf("�湮�� ���� : %d .\n", visitedNodes);
            inorderTraversal(root);
            break;

        case 'c':
            break;

        default:
            printf("Invalid choice\n");
        }
    } while (choice != 'c');

    return 0;
}
