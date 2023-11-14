#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF 1000000  // 무한대 (연결이 없는 경우)

typedef struct GraphType {
    int n;  // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES]; // 시작정점으로부터의 최단경로 거리
int path[MAX_VERTICES][MAX_VERTICES];//최단경로 저장 배열

// A 배열을 출력하는 함수
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
                    path[i][j] = path[k][j];//최단경로 추가
                }
    }
}
//Path 출력함수 스텍사용
void printPath(int u, int v) {
    if (path[u][v] == -1) {
        printf("No Path\n"); // u에서 v까지 경로가 없는 경우
        return;
    }
    int stack[MAX_VERTICES], top = -1; // 경로를 저장할 스택과 스택의 최상위 인덱스
    while (v != u) { // 종료 노드에서 시작 노드로 역으로 추적
        stack[++top] = v; // 현재 노드를 스택에 저장
        v = path[u][v]; // 다음 노드로 이동
    }
    stack[++top] = u; // 시작 노드를 스택에 추가
    while (top >= 0)
        printf("%d ", stack[top--]); // 스택을 역순으로 출력하여 경로 표시
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

        start--;//배열 떄문에 1 감소시키기
        end--;//이와 같음


        if (start < 0 || start >= g.n || end < 0 || end >= g.n) {//노드 초과 또는 0이하 입력시 오류메세지 송출
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
