#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF 1000000  // ���Ѵ� (������ ���� ���)

typedef struct GraphType {
    int n;  // ������ ����
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES]; // �����������κ����� �ִܰ�� �Ÿ�
int path[MAX_VERTICES][MAX_VERTICES];//�ִܰ�� ���� �迭

// A �迭�� ����ϴ� �Լ�
void printA(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            if (A[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void floyd(GraphType* g) {
    int i, j, k;
    for (i = 0; i < g->n; i++)
        for (j = 0; j < g->n; j++) {
            A[i][j] = g->weight[i][j];
            if (i != j && A[i][j] < INF)
                path[i][j] = i;
            else
                path[i][j] = -1;
        }

    for (k = 0; k < g->n; k++) {
        for (i = 0; i < g->n; i++)
            for (j = 0; j < g->n; j++)
                if (A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    path[i][j] = path[k][j];//�ִܰ�� �߰�
                }
    }
}
//Path ����Լ� ���ػ��
void printPath(int u, int v) {
    if (path[u][v] == -1) {
        printf("No Path\n"); // u���� v���� ��ΰ� ���� ���
        return;
    }
    int stack[MAX_VERTICES], top = -1; // ��θ� ������ ���ð� ������ �ֻ��� �ε���
    while (v != u) { // ���� ��忡�� ���� ���� ������ ����
        stack[++top] = v; // ���� ��带 ���ÿ� ����
        v = path[u][v]; // ���� ���� �̵�
    }
    stack[++top] = u; // ���� ��带 ���ÿ� �߰�
    while (top >= 0)
        printf("%d ", stack[top--]); // ������ �������� ����Ͽ� ��� ǥ��
    printf("\n");
}



int main(void)
{
    GraphType g = { 10,{

 { 0, 3, INF, INF, INF, 11, 12, INF, INF, INF },
 { 3, 0, 5, 4, 1, 7, 8, INF, INF, INF },
 { INF, 5, 0, 2, INF, INF, 6, 5, INF, INF },
 { INF, 4, 2, 0, 13, INF, INF, 14, INF, 16 },
 { INF, 1, INF, 13, 0, 9, INF, INF, 18, 17 },
 { 11, 7, INF, INF, 9, 0, INF, INF, INF, INF },
 { 12, 8, 6, INF, INF, INF, 0, 13, INF, INF },
 { INF, INF, 5, 14, INF, INF, 13, 0, INF, 15 },
 { INF, INF, INF, INF, 18, INF, INF, INF, 0, 10 },
 { INF, INF, INF, 16, 17, INF, INF, INF, 15, 10, 0 }
    } };

    floyd(&g);

    int start, end, x;
    for (x = 0; x < 5; x++) {
        printf("Start Node: ");
        scanf("%d", &start);
        printf("End Node : ");
        scanf("%d", &end);

        start--;//�迭 ������ 1 ���ҽ�Ű��
        end--;//�̿� ����


        if (start < 0 || start >= g.n || end < 0 || end >= g.n) {//��� �ʰ� �Ǵ� 0���� �Է½� �����޼��� ����
            printf("Vertices are out of range\n");
        }
        else {
            printf("Shortest Distance: %d\n", A[start][end]);
            printf("Path: ");
            printPath(start, end);
            printf("\n");
        }
    }


    return 0;
}
