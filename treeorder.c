//재귀적 방식
//#include <stdio.h>
//#include <stdlib.h>
//
//#define MAX_SIZE 20 // 예시 크기
//#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
//
//int comparisons = 0; // 비교 횟수
//int swaps = 0; // 스왑 횟수
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
//            comparisons++; // 비교 횟수 증가
//        } while (low <= right && list[low] < pivot);
//
//        do {
//            high--;
//            comparisons++; // 비교 횟수 증가
//        } while (high >= left && list[high] > pivot);
//
//        if (low < high) {
//            SWAP(list[low], list[high], temp);
//            swaps++; // 스왑 횟수 증가
//            if (is_first) {
//                print_array(list, MAX_SIZE); // 스왑 후 배열 상태 출력
//            }
//        }
//    } while (low < high);
//
//    SWAP(list[left], list[high], temp);
//    swaps++; // 스왑 횟수 증가
//    if (is_first) {
//        print_array(list, MAX_SIZE); // 스왑 후 배열 상태 출력
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
//        // 배열 초기화
//        for (i = 0; i < n; i++) {
//            list[i] = rand() % 100; // 0부터 99까지의 난수 생성
//        }
//
//        comparisons = 0;
//        swaps = 0;
//        
//        quick_sort(list, 0, n - 1, repeat == 0); // 퀵정렬 호출, 첫 번째 반복에서만 배열 상태 출력
//
//        total_comparisons += comparisons;
//        total_swaps += swaps;
//    }
//
//    printf("평균 비교 횟수: %f\n", (double)total_comparisons / repeat_count);
//    printf("평균 이동(스왑) 횟수: %f\n", (double)total_swaps / repeat_count);
//
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20  // 배열의 최대 크기 정의
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t)) // 두 변수 값을 교환하는 매크로

typedef struct {
    int left;
    int right;
} Range; // 퀵 정렬에서 분할된 범위를 나타내는 구조체

int comparisons = 0; // 전역 변수로 비교 횟수 추적
int swaps = 0; // 전역 변수로 스왑 횟수 추적

// 배열의 현재 상태를 출력하는 함수
void print_array(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

// 퀵 정렬에서 파티션을 수행하는 함수
int partition(int list[], int left, int right, int is_first)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = list[left]; // 피벗을 왼쪽 요소로 설정

    do {
        // 피벗보다 큰 값 찾기
        do {
            low++;
            comparisons++;
        } while (low <= right && list[low] < pivot);

        // 피벗보다 작은 값 찾기
        do {
            high--;
            comparisons++;
        } while (high >= left && list[high] > pivot);

        // 값 교환
        if (low < high) {
            SWAP(list[low], list[high], temp);
            swaps++;
            if (is_first) {
                print_array(list, MAX_SIZE); // 첫 번째 반복에서 배열 상태 출력
            }
        }
    } while (low < high);

    // 피벗 교환
    SWAP(list[left], list[high], temp);
    swaps++;
    if (is_first) {
        print_array(list, MAX_SIZE); // 첫 번째 반복에서 배열 상태 출력
    }
    return high;
}

// 퀵 정렬을 반복적으로 수행하는 함수
void iterative_quick_sort(int list[], int left, int right, int is_first) {
    Range stack[MAX_SIZE]; // 범위를 저장하기 위한 스택
    int top = -1; // 스택의 맨 위를 가리키는 인덱스

    stack[++top] = (Range){ left, right }; // 초기 범위를 스택에 푸시

    while (top >= 0) {
        Range range = stack[top--]; // 스택에서 범위 팝

        if (range.left < range.right) {
            int q = partition(list, range.left, range.right, is_first);

            // 새로운 범위를 스택에 푸시
            stack[++top] = (Range){ range.left, q - 1 };
            stack[++top] = (Range){ q + 1, range.right };
        }
    }
}

// 메인 함수
int main(void)
{
    int list[MAX_SIZE]; // 정렬할 배열
    int n, i, repeat;
    n = MAX_SIZE; // 배열 크기 설정
    srand(time(NULL)); // 난수 초기화

    int total_comparisons = 0; // 전체 비교 횟수
    int total_swaps = 0; // 전체 스왑 횟수
    int repeat_count = 20; // 반복 횟수

    printf("quick sort 반복적 방법\n");
    for (repeat = 0; repeat < repeat_count; repeat++) {
        // 배열을 난수로 초기화
        for (i = 0; i < n; i++) {
            list[i] = rand() % 100;
        }

        comparisons = 0;
        swaps = 0;

        // 반복적 퀵정렬 호출, 첫 번째 반복에서만 배열 상태 출력
        iterative_quick_sort(list, 0, n - 1, repeat == 0);

        total_comparisons += comparisons; // 비교 횟수 누적
        total_swaps += swaps; // 스왑 횟수 누적
    }

    // 평균 비교 및 스왑 횟수 출력
    printf("평균 비교 횟수: %f\n", (double)total_comparisons / repeat_count);
    printf("평균 이동(스왑) 횟수: %f\n", (double)total_swaps / repeat_count);

    return 0;
}
