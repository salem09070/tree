#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
typedef struct Node {
    int data;               // 데이터 필드
    struct Node* left;      // 왼쪽 자식 노드를 가리키는 포인터
    struct Node* right;     // 오른쪽 자식 노드를 가리키는 포인터
} Node;

Node* root = NULL;          // 트리의 루트 노드를 가리키는 포인터

int visitedNodes = 0;       // 방문한 노드의 수

// 새 노드 생성 함수
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 특정 데이터를 가진 노드 검색 함수
void search(int data) {
    Node* temp = root;
    visitedNodes = 0;

    while (temp != NULL) {
        visitedNodes++;
        if (data == temp->data) {
            printf("방문한 노드수 : %d .\n", visitedNodes);
            return;
        }
        else if (data < temp->data) {
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }
    printf("방문한 노드수 : %d .\n", visitedNodes);
}

// 재귀적으로 노드 삽입 함수
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

// 재귀적으로 노드 삭제 함수
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

// 중위 순회 함수
void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("%d ", node->data);
        visitedNodes++;
        inorderTraversal(node->right);
    }
}

// 반복적으로 노드 삽입 함수
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
            return;  // 중복 데이터
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

// 반복적으로 노드 삭제 함수
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
    printf("방문한 노드수 : %d .\n", visitedNodes);
}

int main() {
    char choice;

    // 초기 트리 구성
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
        printf("s: 검색\n");
        printf("i: 노드 추가\n");
        printf("d: 노드삭제\n");
        printf("t: 중위순회\n");
        printf("I: 노드 추가(반복)\n");
        printf("D: 노드 삭제(반복)\n");
        printf("c: 종료\n");
        printf("메뉴입력: ");
        scanf(" %c", &choice);

        int data;

        switch (choice) {
        case 's':
            printf("검색할 값 입력: ");
            scanf("%d", &data);
            search(data);
            inorderTraversal(root);
            break;

        case 'i':
            printf("삽입할 값 입력: ");
            scanf("%d", &data);
            visitedNodes = 0;
            root = insertRecursive(root, data);
            printf("방문한 노드수 : %d .\n", visitedNodes);
            inorderTraversal(root);
            break;

        case 'd':
            printf("삭제 할 값 입력: ");
            scanf("%d", &data);
            visitedNodes = 0;
            root = deleteRecursive(root, data);
            printf("방문한 노드수 : %d .\n", visitedNodes);
            inorderTraversal(root);
            break;

        case 't':
            visitedNodes = 0;
            inorderTraversal(root);
            printf("\n");
            printf("방문한 노드수 : %d .\n", visitedNodes);
            break;

        case 'I':
            printf("삽입할 값 입력: ");
            scanf("%d", &data);
            visitedNodes = 0;
            insertIterative(data);
            printf("방문한 노드수 : %d .\n", visitedNodes);
            inorderTraversal(root);
            break;

        case 'D':
            printf("삭제할 값 입력: ");
            scanf("%d", &data);
            visitedNodes = 0;
            deleteIterative(data);
            printf("방문한 노드수 : %d .\n", visitedNodes);
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
