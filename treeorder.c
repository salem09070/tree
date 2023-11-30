#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20 // 예시 크기
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int comparisons = 0; // 비교 횟수
int swaps = 0; // 스왑 횟수

void print_array(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int partition(int list[], int left, int right, int is_first)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left];
    do {
        do {
            low++;
            comparisons++; // 비교 횟수 증가
        } while (low <= right && list[low] < pivot);

        do {
            high--;
            comparisons++; // 비교 횟수 증가
        } while (high >= left && list[high] > pivot);

        if (low < high) {
            SWAP(list[low], list[high], temp);
            swaps++; // 스왑 횟수 증가
            if (is_first) {
                print_array(list, MAX_SIZE); // 스왑 후 배열 상태 출력
            }
        }
    } while (low < high);

    SWAP(list[left], list[high], temp);
    swaps++; // 스왑 횟수 증가
    if (is_first) {
        print_array(list, MAX_SIZE); // 스왑 후 배열 상태 출력
    }
    return high;
}

void quick_sort(int list[], int left, int right, int is_first)
{
    if (left < right) {
        int q = partition(list, left, right, is_first);
        quick_sort(list, left, q - 1, is_first);
        quick_sort(list, q + 1, right, is_first);
    }
}

int main(void)
{
    int list[MAX_SIZE];
    int n, i, repeat;
    n = MAX_SIZE;
    srand(time(NULL));

    int total_comparisons = 0;
    int total_swaps = 0;
    int repeat_count = 20;
    printf("quick sort\n");
    for (repeat = 0; repeat < repeat_count; repeat++) {
        // 배열 초기화
        for (i = 0; i < n; i++) {
            list[i] = rand() % 100; // 0부터 99까지의 난수 생성
        }

        comparisons = 0;
        swaps = 0;
        
        quick_sort(list, 0, n - 1, repeat == 0); // 퀵정렬 호출, 첫 번째 반복에서만 배열 상태 출력

        total_comparisons += comparisons;
        total_swaps += swaps;
    }

    printf("평균 비교 횟수: %f\n", (double)total_comparisons / repeat_count);
    printf("평균 이동(스왑) 횟수: %f\n", (double)total_swaps / repeat_count);

    return 0;
}
