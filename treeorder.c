#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode* next;
} GraphNode;

typedef struct GraphType {
    int n;   // ������ ����
    GraphNode* adjList[MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; // ���� �������κ����� �ִ� ��� �Ÿ�
int found[MAX_VERTICES]; // �湮�� ���� ǥ��

void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        g->adjList[i] = NULL;
    }
}

void insert_edge(GraphType* g, int u, int v, int weight) {
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->weight = weight;
    node->next = g->adjList[u];
    g->adjList[u] = node;
}

int choose(int distance[], int n, int found[]) {
    int min = INF;
    int minpos = -1;
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void shortest_path(GraphType* g, int start) {
    for (int i = 0; i < g->n; i++) {//�ʱ�ȭ
        distance[i] = INF;
        found[i] = FALSE;
    }

    distance[start] = 0;

    for (int i = 0; i < g->n - 1; i++) {
        printf("Distance: \n");
        for (int j = 0; j < g->n; j++)
            if (distance[j] == INF)
                printf(" * ");
            else
                printf("%d ", distance[j]);
        printf("\n");

        printf("Found: ");
        for (int j = 0; j < g->n; j++)
            printf("%d ", found[j]);
        printf("\n");

        int u = choose(distance, g->n, found);
        found[u] = TRUE;

        for (GraphNode* node = g->adjList[u]; node != NULL; node = node->next) {
            int v = node->vertex;
            if (!found[v] && distance[u] + node->weight < distance[v]) {
                distance[v] = distance[u] + node->weight;
            }
        }
    }
}

void free_graph(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* node = g->adjList[i];
        while (node != NULL) {
            GraphNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
}

int main(void) {
    GraphType g;
    init_graph(&g, 10); 

    int adj_matrix[10][10] = {
        {0, 3, INF, INF, INF, 11, 12, INF, INF, INF},
        {3, 0, 5, 4, 1, 7, 8, INF, INF, INF},
        {INF, 5, 0, 2, INF, INF, 6, 5, INF, INF},
        {INF, 4, 2, 0, 13, INF, INF, 14, INF, 16},
        {INF, 1, INF, 13, 0, 9, INF, INF, 18, 17},
        {11, 7, INF, INF, 9, 0, INF, INF, INF, INF},
        {12, 8, 6, INF, INF, INF, 0, 13, INF, INF},
        {INF, INF, 5, 14, INF, INF, 13, 0, INF, 15},
        {INF, INF, INF, INF, INF, INF, INF, INF, 0, 10},
        {INF, INF, INF, INF, 17, INF, INF, 15, 10, 0}
    };

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (adj_matrix[i][j] != INF) {
                insert_edge(&g, i, j, adj_matrix[i][j]);
            }
        }
    }
    shortest_path(&g, 0);

    free_graph(&g);

    return 0;
}
