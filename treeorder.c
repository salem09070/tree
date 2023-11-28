#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define MAX_SIZE 20

void selection_sort(int list[], int n, int* compare_count, int* move_count, int iteration)
{
    int i, j, least, temp;
    *compare_count = 0;
    *move_count = 0;

    for (i = 0; i < n - 1; i++) {
        least = i;
        for (j = i + 1; j < n; j++) {
            (*compare_count)++;
            if (list[j] < list[least]) least = j;
        }
        SWAP(list[i], list[least], temp);
        (*move_count)++;
        if (iteration == 0) { // ù ��° ���� ���� ���
            for (int k = 0; k < n; k++) {
                printf("%d ", list[k]);
            }
            printf("\n");
        }
    }
}

void insertion_sort(int list[], int n, int* compare_count, int* move_count, int iteration) {
    int i, j, key;
    *compare_count = 0;
    *move_count = 0;

    for (i = 1; i < n; i++) {
        key = list[i];
        for (j = i - 1; j >= 0 && list[j] > key; j--) {
            list[j + 1] = list[j];
            (*compare_count)++;
            (*move_count)++;
        }
        list[j + 1] = key;
        (*move_count)++;
        if (iteration == 0) { // ù ��° ���� ���� ���
            for (int k = 0; k < n; k++) {
                printf("%d ", list[k]);
            }
            printf("\n");
        }
    }
}

void bubble_sort(int list[], int n, int* compare_count, int* move_count, int iteration) {
    int i, j, temp;
    *compare_count = 0;
    *move_count = 0;

    for (i = n - 1; i > 0; i--) {
        for (j = 0; j < i; j++){ //�յ� ���ڵ� ���� ��ü
            (*compare_count)++;
            if (list[j] > list[j + 1]) {
                SWAP(list[j], list[j + 1], temp);
                (*move_count)++;
            }
        }
        if (iteration == 0) { // ù ��° ���� ���� ���
            for (int k = 0; k < n; k++) {
                printf("%d ", list[k]);
            }
            printf("\n");
        }
    }
}



int main(void)
{
    int list[MAX_SIZE], n, i;
    int total_compare = 0, total_move = 0;
    int compare_count, move_count;

    n = MAX_SIZE;
    srand(time(NULL));

    for (int count = 0; count < 20; count++) {
        for (i = 0; i < n; i++) {
            list[i] = rand() % 100;
        }


        if (count == 0) { // ù ��° ���࿡�� ���� �迭 �� ���� ���� ���
            //printf("ù ��° ���� �迭 ���� ����: ���� ����\n");
            //printf("ù ��° ���� �迭 ���� ����: ���� ����\n");
            printf("ù ��° ���� �迭 ���� ����: ���� ����\n");
        }
        //selection_sort(list, n, &compare_count, &move_count, count);
        //insertion_sort(list, n, &compare_count, &move_count, count);
        bubble_sort(list, n, &compare_count, &move_count, count);
        total_compare += compare_count;//�� �� Ƚ�� 
        total_move += move_count;//�� �̵� Ƚ��

    }

    printf("��� �̵� Ƚ��: %f\n", (double)total_move / 20);
    printf("��� �� Ƚ��: %f\n", (double)total_compare / 20);
  

    return 0;
}
