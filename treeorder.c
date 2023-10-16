#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ELEMENT 200

int cnt = 0; // �̵� Ƚ���� ������ ���� ����

// ��� ����ü ����
typedef struct Element
{
	int key;
} element;

// �� ����ü ����
typedef struct heapType
{
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// �� ���� �Լ�
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}

// �� �ʱ�ȭ �Լ�
void init(HeapType* h)
{
	h->heap_size = 0;
}

// ���� ������� Ȯ���ϴ� �Լ�
int is_empty(HeapType* h)
{
	return (h->heap_size == 0);
}

// ���� �� á���� Ȯ���ϴ� �Լ�
int is_full(HeapType* h)
{
	return(h->heap_size == (MAX_ELEMENT - 1));
}

// �� ���� ��� �Լ�
int print_heap(HeapType* h) {
	for (int i = 1; i < h->heap_size + 1; i++)
	{
		printf("%d ", h->heap[i].key);
	}
}

// �⺻ ���� �Լ�
void basic_insert_heap(HeapType* h, element item)
{
	int i = ++(h->heap_size);
	while ((i != 1) && (item.key > h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;
}

// ���� ��� �߰� �Լ�
void insert_heap(HeapType* h, element item) {
	if (is_full(&h))
	{
		printf("heap�� �� á���ϴ�.");
		return;
	}
	int i = ++(h->heap_size);
	cnt = 0;

	while ((i > 1) && item.key > h->heap[i / 2].key) {
		cnt++;
		h->heap[i] = item;
		print_heap(h);
		printf("\n");
		h->heap[i] = h->heap[i / 2];
		i = i / 2;
	}
	h->heap[i] = item;

}

// ������ ��� ���� �Լ�
element delete_heap(HeapType* h)
{
	cnt = 0;
	int parent, child;
	element item, temp;
	if (is_empty(h))
	{
		printf("heap�� ������ϴ�.");
		return;
	}
	item = h->heap[1]; // ù ���� item ����
	temp = h->heap[(h->heap_size)--]; // temp�� ������ ���� ����
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		cnt++;
		print_heap(h);
		printf("\n");
		if ((child < h->heap_size) && (h->heap[child].key) < h->heap[child + 1].key) child++;
		if (temp.key >= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}


// �������� �� ��� �Լ�
int print_level_heap(HeapType* h) {
	int k = 1;
	for (int i = 1; i < h->heap_size + 1; i++)
	{
		if (k > h->heap_size) break;
		printf("[%d] ", i);
		for (int j = 0; j < pow(2, i - 1); j++)
		{
			if (k > h->heap_size) break;
			printf("%d ", h->heap[k++].key);
		}
		printf("\n");
	}
}

// ���� �Լ�
int main()
{
	element e1 = { 90 }, e2 = { 89 }, e3 = { 70 }, e4 = { 36 }, e5 = { 75 }, e6 = { 63 },
		e7 = { 65 }, e8 = { 21 }, e9 = { 18 }, e10 = { 15 }, e11 = { 100 };
	HeapType* heap;

	heap = create();
	init(heap);

	basic_insert_heap(heap, e1);
	basic_insert_heap(heap, e2);
	basic_insert_heap(heap, e3);
	basic_insert_heap(heap, e4);
	basic_insert_heap(heap, e5);
	basic_insert_heap(heap, e6);
	basic_insert_heap(heap, e7);
	basic_insert_heap(heap, e8);
	basic_insert_heap(heap, e9);
	basic_insert_heap(heap, e10);

	printf("i : ��� �߰�\n");
	printf("d : ��� ����\n");
	printf("p : ������ ���\n");
	printf("c : ���� \n");

	char choice = ' ';
	element item;

	while (choice != 'q')
	{
		printf("\n�޴� �Է�: ");
		scanf(" %c", &choice);

		switch (choice)
		{
		case 'i':
			printf("�߰��� �� �Է�: ");
			scanf("%d", &item.key);
			insert_heap(heap, item);
			print_heap(heap);
			printf("\n��尡 �̵��� Ƚ�� %d\n", cnt);
			break;
		case 'd':
			delete_heap(heap);
			print_heap(heap);
			printf("\n��尡 �̵��� Ƚ�� %d\n", cnt);
			break;
		case 'p':
			printf("Ʈ�� ������ ���\n");
			print_level_heap(heap);
			break;
		case 'q':
			break;
		default:
			printf("�ٽ� �Է��ϼ���\n");
		}
	}

	printf("���α׷��� �����մϴ�.\n");
	free(heap);
	return 0;
}
