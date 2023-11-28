#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20

int sorted[MAX_SIZE];
int total_compare = 0, total_move = 0;

// ��ü �迭�� ����ϴ� �Լ�
void print_array(int list[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", list[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

// �� �κ� �迭�� �պ��ϴ� �Լ�
void merge(int list[], int left, int mid, int right, int* compare_count, int* move_count, int is_first_iteration) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        (*compare_count)++;
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        (*move_count)++;
    }

    while (i <= mid) {
        sorted[k++] = list[i++];
        (*move_count)++;
    }
    while (j <= right) {
        sorted[k++] = list[j++];
        (*move_count)++;
    }

    for (int l = left; l <= right; l++) {
        list[l] = sorted[l];
    }

    // ù ��° �ݺ������� �迭�� ���� ���
    if (is_first_iteration) {
        print_array(list, MAX_SIZE);
    }
}

// �ݺ��� ���� ���� �Լ�
void iterative_merge_sort(int list[], int size, int* compare_count, int* move_count, int is_first_iteration) {
    for (int width = 1; width < size; width *= 2) {
        for (int i = 0; i < size; i = i + 2 * width) {
            int left = i;
            int mid = i + width - 1;
            int right = i + 2 * width - 1;
            if (right >= size) right = size - 1;
            if (mid >= size) break; // �迭 ũ�⸦ �ʰ��ϴ� �ʺ� ���ϱ� ����
            merge(list, left, mid, right, compare_count, move_count, is_first_iteration);
        }
        // �� ��ü �н� ��, ù ��° �ݺ����� �迭�� ���
        if (is_first_iteration) {
            print_array(list, size);
        }
    }
}

int main(void) {
    int list[MAX_SIZE];
    srand(time(NULL));

    for (int count = 0; count < 20; count++) {
        // �� �ݺ����� �� �� �̵� Ƚ���� �ʱ�ȭ
        int compare_count = 0, move_count = 0;

        // �� �ݺ����� ���� ���ڷ� ����Ʈ ä���
        for (int i = 0; i < MAX_SIZE; i++) {
            list[i] = rand() % 100;
        }

        // ù ��° �ݺ������� ���� �� ���ĵ� �迭 ���
        if (count == 0) {
            printf("Original list:\n");
            print_array(list, MAX_SIZE);
            printf("Merge Sort\n");
        }

        // �ݺ��� ���� ���� ����
        iterative_merge_sort(list, MAX_SIZE, &compare_count, &move_count, count == 0);

        // ù ��° �ݺ������� ���ĵ� �迭 ���
        if (count == 0) {
            printf("Sorted list:\n");
            print_array(list, MAX_SIZE);
        }

        // �� �� �� �̵� Ƚ���� ���ϱ�
        total_compare += compare_count;
        total_move += move_count;
    }

    // ��� �� �� �̵� Ƚ�� ��� �� ���
    printf("��� �� Ƚ��: %f\n", (double)total_compare / 20);
    printf("��� �̵� Ƚ��: %f\n", (double)total_move / 20);

    return 0;
}
