#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];		// 부모 노드

void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}
// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// 루트 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);	// 노드 b의 루트를 찾는다. 
	if (root1 != root2) 	// 합한다. 
		parent[root1] = root2;
}

typedef struct edge {
	int start, end, weight;
}Edge;

typedef struct graphtype {
	int n;
	Edge edges[2 * MAX_VERTICES];
}GraphType;

void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void insert_edge(GraphType* g, int start, int end, int weight)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = weight;
	g->n++;
}

int compare(const void* a, const void* b)
{
	struct edge* x = (struct edge*)a;
	struct edge* y = (struct edge*)b;
	return ((x->weight) - (y->weight));
}

void heapify(Edge heap[], int size, int i) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < size && heap[left].weight < heap[smallest].weight)
		smallest = left;
	if (right < size && heap[right].weight < heap[smallest].weight)
		smallest = right;

	if (smallest != i) {
		Edge temp = heap[i];
		heap[i] = heap[smallest];
		heap[smallest] = temp;
		heapify(heap, size, smallest);
	}
}

void buildHeap(Edge heap[], int size) {
	for (int i = size / 2 - 1; i >= 0; i--) {
		heapify(heap, size, i);
	}
}

Edge extractMin(Edge heap[], int* size) {
	Edge min = heap[0];
	heap[0] = heap[*size - 1];
	(*size)--;
	heapify(heap, *size, 0);
	return min;
}

void kruskal(GraphType* g)
{
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;			// 정점 u와 정점 v의 집합 번호
	struct edge e;

	set_init(g->n);				// 집합 초기화
	qsort(g->edges, g->n, sizeof(struct edge), compare);//정열

	printf("크루스칼 최소 신장 트리 알고리즘 \n");
	int i = 0;
	int c = 1;
	while (edge_accepted < (g->n) - 1)	// 간선의 수 < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		// 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("Edge (%d,%d) Select %d\n", e.start, e.end, i+1);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
		i++;
	}
}

void kruskal_minheap(GraphType* g) {
	int edge_accepted = 0;
	int uset, vset;
	struct edge e;

	set_init(g->n);
	buildHeap(g->edges, g->n);

	printf("크루스칼 최소 신장 트리 알고리즘 (Min Heap 사용)\n");
	int i = 0;
	while (edge_accepted < (g->n) - 1) {
		e = extractMin(g->edges, &g->n);
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("Edge (% d, % d) select %d\n", e.start, e.end, i+1);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}

int main(void)
{
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);
	
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 6, 2, 7);
	insert_edge(g, 6, 5, 9);
	insert_edge(g, 7, 2, 8);
	insert_edge(g, 7, 3, 6);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 3, 2, 5);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 5, 4, 11);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 5, 9, 16);
	insert_edge(g, 8, 4, 14);
	insert_edge(g, 10, 4, 16);
	insert_edge(g, 10, 8, 15);
	insert_edge(g, 10, 9, 10);

	int choice;
	printf("크루스칼 알고리즘 실행 방법 선택:\n");
	printf("1. qsort 사용\n");
	printf("2. Min Heap 사용\n");
	printf("선택: ");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		kruskal(g);
		break;
	case 2:
		kruskal_minheap(g);
		break;
	default:
		printf("잘못된 선택입니다.\n");
	}

	free(g);
	return 0;
}
