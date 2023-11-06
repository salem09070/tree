#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];		// �θ� ���

void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}
// curr�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// ��Ʈ 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// �ΰ��� ���Ұ� ���� ������ ��ģ��.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// ��� a�� ��Ʈ�� ã�´�. 
	int root2 = set_find(b);	// ��� b�� ��Ʈ�� ã�´�. 
	if (root1 != root2) 	// ���Ѵ�. 
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
	int edge_accepted = 0;	// ������� ���õ� ������ ��	
	int uset, vset;			// ���� u�� ���� v�� ���� ��ȣ
	struct edge e;

	set_init(g->n);				// ���� �ʱ�ȭ
	qsort(g->edges, g->n, sizeof(struct edge), compare);//����

	printf("ũ�罺Į �ּ� ���� Ʈ�� �˰��� \n");
	int i = 0;
	int c = 1;
	while (edge_accepted < (g->n) - 1)	// ������ �� < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// ���� u�� ���� ��ȣ 
		vset = set_find(e.end);		// ���� v�� ���� ��ȣ
		if (uset != vset) {			// ���� ���� ������ �ٸ���
			printf("Edge (%d,%d) Select %d\n", e.start, e.end, i+1);
			edge_accepted++;
			set_union(uset, vset);	// �ΰ��� ������ ��ģ��.
		}
		i++;
	}
}

void kruskal_minheap(GraphType* g) {
	int edge_accepted = 0;
	int uset, vset;
	struct edge e;

	set_init(g->n);
	int heap_size = g->n;  // ������ �� ũ�� ����
	buildHeap(g->edges, heap_size);

	printf("ũ�罺Į �ּ� ���� Ʈ�� �˰��� (Min Heap ���)\n");
	int i = 0;

	while (edge_accepted < (g->n) - 1) {
		e = extractMin(g->edges, &heap_size);  // �� ũ�� ���� ���
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("Edge (%d, %d) %d����\n", e.start, e.end,i+1);
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
	printf("ũ�罺Į �˰��� ���� ��� ����:\n");
	printf("1. qsort ���\n");
	printf("2. Min Heap ���\n");
	printf("����: ");
	scanf("%d", &choice);

	switch (choice) {
	case 1:
		kruskal(g);
		break;
	case 2:
		kruskal_minheap(g);
		break;
	default:
		printf("�߸��� �����Դϴ�.\n");
	}

	free(g);
	return 0;
}
