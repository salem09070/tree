#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEXS 100
int visited[MAX_VERTEXS]; // 노드의 방문여부를 저장 할 배열

// 에러출력함수
void error(char* message) {
    fprintf(stderr, "\n%s\n", message);
}

// 스택 정의 (DFS에서 사용)
typedef struct {
    int data[MAX_VERTEXS];
    int top;
} StackType;

void init_stack(StackType* s) {
    s->top = -1;
}

int is_emptys(StackType* s) {
    return s->top == -1;
}

int is_fulls(StackType* s) {
    return s->top == MAX_VERTEXS - 1;
}

void push(StackType* s, int item) {
    if (is_fulls(s)) {
        error("Stack Full");
        return;
    }
    else {
        s->data[++(s->top)] = item;
    }
}

int pop(StackType* s) {
    if (is_emptys(s)) {
        error("Stack Empty");
        return -1;
    }
    else return(s->data[(s->top)--]);
}

// 큐 정의 (BFS에서 사용)
typedef struct {
    int data[MAX_VERTEXS];
    int front, rear;
} QueueType;

void init_queue(QueueType* qptr) {
    qptr->front = qptr->rear = 0;
}

int is_emptyq(QueueType* qptr) {
    return (qptr->front == qptr->rear);
}

int is_fullq(QueueType* qptr) {
    return (qptr->front == (qptr->rear + 1) % MAX_VERTEXS);
}

void enqueue(QueueType* qptr, int value) {
    if (is_fullq(qptr)) {
        error("Queue is Full");
        return;
    }
    else {
        qptr->rear = (qptr->rear + 1) % MAX_VERTEXS;
        qptr->data[qptr->rear] = value;
    }
}

int dequeue(QueueType* qptr) {
    if (is_emptyq(qptr)) {
        error("Queue is Empty");
        return -1;
    }
    else {
        qptr->front = (qptr->front + 1) % MAX_VERTEXS;
        return qptr->data[qptr->front];
    }
}

typedef struct GraphType_MAT {
    int n; // 정점의 개수
    int adj_mat[MAX_VERTEXS][MAX_VERTEXS]; // 인접행렬
} graphType_mat;

void initGMat(graphType_mat* g) {
    int i, j;
    g->n = 0;
    for (i = 0; i < MAX_VERTEXS; i++) {
        for (j = 0; j < MAX_VERTEXS; j++) {
            g->adj_mat[i][j] = 0;
        }
    }
}

void insert_vertex_mat(graphType_mat* g, int v) {
    if (((g->n) + 1) > MAX_VERTEXS) {
        error("Over vertexs's number");
        return;
    }
    g->n++;
}

void insert_edge_mat(graphType_mat* g, int u, int v) {
    if (u >= g->n || v >= g->n) {
        error("Default vertex's number");
        return;
    }
    g->adj_mat[u][v] = 1;
    g->adj_mat[v][u] = 1; // 무방향 그래프의 경우
}

void dfs_mat(graphType_mat* g, int v, int key) {
    StackType s;
    init_stack(&s);
    push(&s, v);
    for (int i = 0; i < g->n; i++) visited[i] = 0;

    while (!is_emptys(&s)) {
        v = pop(&s);
        if (!visited[v]) {
            visited[v] = 1;
            printf("%d ", v);

            if (v == key) {
                printf("\nFound key node! Visited nodes: %d\n", v);
                break;
            }

            for (int w = 0; w < g->n; w++) {
                if (g->adj_mat[v][w] && !visited[w]) {
                    push(&s, w);
                }
            }
        }
    }
}

void bfs_mat(graphType_mat* g, int v, int key) {
    QueueType q;
    init_queue(&q);
    enqueue(&q, v);
    for (int i = 0; i < g->n; i++) visited[i] = 0;

    while (!is_emptyq(&q)) {
        v = dequeue(&q);
        if (!visited[v]) {
            visited[v] = 1;
            printf("%d ", v);

            if (v == key) {
                printf("\nFound key node! Visited nodes: %d\n", v);
                break;
            }

            for (int w = 0; w < g->n; w++) {
                if (g->adj_mat[v][w] && !visited[w]) {
                    enqueue(&q, w);
                }
            }
        }
    }
}

graphType_mat* makeGraphMat() {
    graphType_mat* g = (graphType_mat*)malloc(sizeof(graphType_mat));
    initGMat(g);

    // 정점 추가
    for (int i = 0; i < 11; i++) {
        insert_vertex_mat(g, i);
    }

    // 각 정점에 대한 인접 정점 추가
    int edges[11][7] = {
        {2, 5, 6, 9, -1},  // 0
        {4, 5, 7, 10, -1}, // 1
        {0, 3, 4, -1},     // 2
        {2, 4, 5, -1},     // 3
        {1, 2, 3, 5, 6, 7, -1}, // 4
        {0, 1, 3, 4, -1}, // 5
        {0, 4, 7, 8, -1}, // 6
        {1, 4, 10, -1},   // 7
        {6, 9, 10, -1},    // 8
        {0, 8, -1},        // 9
        {1, 7, 8, -1}      // 10
    };

    for (int i = 0; i < 11; i++) {
        for (int j = 0; edges[i][j] != -1; j++) {
            insert_edge_mat(g, i, edges[i][j]);
        }
    }

    return g;
}

int main() {
    graphType_mat* g = makeGraphMat();  // 인접 행렬 그래프 생성
    int menu;
    while (1) {
        printf("==========\n");
        printf("1. DFS\n");
        printf("2. BFS\n");
        printf("3. Exit\n");
        printf("==========\n");
        printf("Enter the menu: ");
        scanf("%d", &menu);

        int startNode, key;
        switch (menu) {
        case 1:
            printf("Enter the start Node's number and key of search: ");
            scanf("%d %d", &startNode, &key);
            dfs_mat(g, startNode, key);
            break;
        case 2:
            printf("Enter the start Node's number and key of search: ");
            scanf("%d %d", &startNode, &key);
            bfs_mat(g, startNode, key);
            break;
        case 3:
            free(g);  // 메모리 해제
            exit(1);
            break;
        default:
            printf("Invalid input. Try again: ");
            break;
        }
    }

    return 0;
}
