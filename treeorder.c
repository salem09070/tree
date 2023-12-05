//����� ���
//#include <stdio.h>
//#include <stdlib.h>
//
//#define MAX_SIZE 20 // ���� ũ��
//#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
//
//int comparisons = 0; // �� Ƚ��
//int swaps = 0; // ���� Ƚ��
//
//void print_array(int list[], int size) {
//    for (int i = 0; i < size; i++) {
//        printf("%d ", list[i]);
//    }
//    printf("\n");
//}
//
//int partition(int list[], int left, int right, int is_first)
//{
//    int pivot, temp;
//    int low, high;
//
//    low = left;
//    high = right + 1;
//    pivot = list[left];
//    do {
//        do {
//            low++;
//            comparisons++; // �� Ƚ�� ����
//        } while (low <= right && list[low] < pivot);
//
//        do {
//            high--;
//            comparisons++; // �� Ƚ�� ����
//        } while (high >= left && list[high] > pivot);
//
//        if (low < high) {
//            SWAP(list[low], list[high], temp);
//            swaps++; // ���� Ƚ�� ����
//            if (is_first) {
//                print_array(list, MAX_SIZE); // ���� �� �迭 ���� ���
//            }
//        }
//    } while (low < high);
//
//    SWAP(list[left], list[high], temp);
//    swaps++; // ���� Ƚ�� ����
//    if (is_first) {
//        print_array(list, MAX_SIZE); // ���� �� �迭 ���� ���
//    }
//    return high;
//}
//
//void quick_sort(int list[], int left, int right, int is_first)
//{
//    if (left < right) {
//        int q = partition(list, left, right, is_first);
//        quick_sort(list, left, q - 1, is_first);
//        quick_sort(list, q + 1, right, is_first);
//    }
//}
//
//int main(void)
//{
//    int list[MAX_SIZE];
//    int n, i, repeat;
//    n = MAX_SIZE;
//    srand(time(NULL));
//
//    int total_comparisons = 0;
//    int total_swaps = 0;
//    int repeat_count = 20;
//    printf("quick sort\n");
//    for (repeat = 0; repeat < repeat_count; repeat++) {
//        // �迭 �ʱ�ȭ
//        for (i = 0; i < n; i++) {
//            list[i] = rand() % 100; // 0���� 99������ ���� ����
//        }
//
//        comparisons = 0;
//        swaps = 0;
//        
//        quick_sort(list, 0, n - 1, repeat == 0); // ������ ȣ��, ù ��° �ݺ������� �迭 ���� ���
//
//        total_comparisons += comparisons;
//        total_swaps += swaps;
//    }
//
//    printf("��� �� Ƚ��: %f\n", (double)total_comparisons / repeat_count);
//    printf("��� �̵�(����) Ƚ��: %f\n", (double)total_swaps / repeat_count);
//
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20  // �迭�� �ִ� ũ�� ����
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t)) // �� ���� ���� ��ȯ�ϴ� ��ũ��

typedef struct {
    int left;
    int right;
} Range; // �� ���Ŀ��� ���ҵ� ������ ��Ÿ���� ����ü

int comparisons = 0; // ���� ������ �� Ƚ�� ����
int swaps = 0; // ���� ������ ���� Ƚ�� ����

// �迭�� ���� ���¸� ����ϴ� �Լ�
void print_array(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// �� ���Ŀ��� ��Ƽ���� �����ϴ� �Լ�
int partition(int list[], int left, int right, int is_first)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left]; // �ǹ��� ���� ��ҷ� ����

    do {
        // �ǹ����� ū �� ã��
        do {
            low++;
            comparisons++;
        } while (low <= right && list[low] < pivot);

        // �ǹ����� ���� �� ã��
        do {
            high--;
            comparisons++;
        } while (high >= left && list[high] > pivot);

        // �� ��ȯ
        if (low < high) {
            SWAP(list[low], list[high], temp);
            swaps++;
            if (is_first) {
                print_array(list, MAX_SIZE); // ù ��° �ݺ����� �迭 ���� ���
            }
        }
    } while (low < high);

    // �ǹ� ��ȯ
    SWAP(list[left], list[high], temp);
    swaps++;
    if (is_first) {
        print_array(list, MAX_SIZE); // ù ��° �ݺ����� �迭 ���� ���
    }
    return high;
}

// �� ������ �ݺ������� �����ϴ� �Լ�
void iterative_quick_sort(int list[], int left, int right, int is_first) {
    Range stack[MAX_SIZE]; // ������ �����ϱ� ���� ����
    int top = -1; // ������ �� ���� ����Ű�� �ε���

    stack[++top] = (Range){ left, right }; // �ʱ� ������ ���ÿ� Ǫ��

    while (top >= 0) {
        Range range = stack[top--]; // ���ÿ��� ���� ��

        if (range.left < range.right) {
            int q = partition(list, range.left, range.right, is_first);

            // ���ο� ������ ���ÿ� Ǫ��
            stack[++top] = (Range){ range.left, q - 1 };
            stack[++top] = (Range){ q + 1, range.right };
        }
    }
}

// ���� �Լ�
int main(void)
{
    int list[MAX_SIZE]; // ������ �迭
    int n, i, repeat;
    n = MAX_SIZE; // �迭 ũ�� ����
    srand(time(NULL)); // ���� �ʱ�ȭ

    int total_comparisons = 0; // ��ü �� Ƚ��
    int total_swaps = 0; // ��ü ���� Ƚ��
    int repeat_count = 20; // �ݺ� Ƚ��

    printf("quick sort �ݺ��� ���\n");
    for (repeat = 0; repeat < repeat_count; repeat++) {
        // �迭�� ������ �ʱ�ȭ
        for (i = 0; i < n; i++) {
            list[i] = rand() % 100;
        }

        comparisons = 0;
        swaps = 0;

        // �ݺ��� ������ ȣ��, ù ��° �ݺ������� �迭 ���� ���
        iterative_quick_sort(list, 0, n - 1, repeat == 0);

        total_comparisons += comparisons; // �� Ƚ�� ����
        total_swaps += swaps; // ���� Ƚ�� ����
    }

    // ��� �� �� ���� Ƚ�� ���
    printf("��� �� Ƚ��: %f\n", (double)total_comparisons / repeat_count);
    printf("��� �̵�(����) Ƚ��: %f\n", (double)total_swaps / repeat_count);

    return 0;
}
