#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
    int move_count;
} HeapType;

HeapType heap1;

void init(HeapType* h) {
    h->heap_size = 0;
    h->move_count = 0;
}

void print_current_heap(HeapType* h) {
    for (int i = 1; i <= h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

void insert_max_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key > h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
        h->move_count++;
    }
    h->heap[i] = item;
    print_current_heap(h);
}

element delete_max_heap(HeapType* h) {
    int parent, child;
    element item, temp;
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];
    parent = 1;
    child = 2;
    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
            child++;
        }
        if (temp.key >= h->heap[child].key) {
            break;
        }
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
        h->move_count++;
        
    }
    h->heap[parent] = temp;
    print_current_heap(h);
    return item;
}

int main() {
    init(&heap1);

    int initialValues[] = { 90, 89, 20, 36, 75, 63, 65, 21, 18, 15 };
    for (int i = 0; i < sizeof(initialValues) / sizeof(int); i++) {
        element item;
        item.key = initialValues[i];
        insert_max_heap(&heap1, item);
    }
    heap1.move_count = 0; // 초기 설정에 따른 이동 횟수를 0으로 재설정

    char command;
    element item;

    while (1) {
        printf("Menu:\n");
        printf("i: 노드 삽입\n");
        printf("d: 노드 삭제\n");
        printf("q: 종료\n");
        printf("메뉴입력: ");
        scanf(" %c", &command);
        heap1.move_count = 0;
        switch (command) {
        case 'i':
            printf("삽입할 값 입력: ");
            scanf("%d", &item.key);
            insert_max_heap(&heap1, item);
            printf("노드가 이동된 횟수: %d\n\n", heap1.move_count);
            break;

        case 'd':
            item = delete_max_heap(&heap1);
            printf("노드가 이동된 횟수: %d\n\n", heap1.move_count);
            break;

        case 'q':
            return 0;

        default:
            printf("Invalid command\n");
            break;
        }
    }
    return 0;
}
