#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20

int sorted[MAX_SIZE];
int total_compare = 0, total_move = 0;

// 전체 배열을 출력하는 함수
void print_array(int list[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", list[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

// 두 부분 배열을 합병하는 함수
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

    // 첫 번째 반복에서만 배열의 상태 출력
    if (is_first_iteration) {
        print_array(list, MAX_SIZE);
    }
}

// 반복적 병합 정렬 함수
void iterative_merge_sort(int list[], int size, int* compare_count, int* move_count, int is_first_iteration) {
    for (int width = 1; width < size; width *= 2) {
        for (int i = 0; i < size; i = i + 2 * width) {
            int left = i;
            int mid = i + width - 1;
            int right = i + 2 * width - 1;
            if (right >= size) right = size - 1;
            if (mid >= size) break; // 배열 크기를 초과하는 너비를 피하기 위함
            merge(list, left, mid, right, compare_count, move_count, is_first_iteration);
        }
        // 각 전체 패스 후, 첫 번째 반복에서 배열을 출력
        if (is_first_iteration) {
            print_array(list, size);
        }
    }
}

int main(void) {
    int list[MAX_SIZE];
    srand(time(NULL));

    for (int count = 0; count < 20; count++) {
        // 각 반복마다 비교 및 이동 횟수를 초기화
        int compare_count = 0, move_count = 0;

        // 각 반복마다 랜덤 숫자로 리스트 채우기
        for (int i = 0; i < MAX_SIZE; i++) {
            list[i] = rand() % 100;
        }

        // 첫 번째 반복에서만 원본 및 정렬된 배열 출력
        if (count == 0) {
            printf("Original list:\n");
            print_array(list, MAX_SIZE);
            printf("Merge Sort\n");
        }

        // 반복적 병합 정렬 수행
        iterative_merge_sort(list, MAX_SIZE, &compare_count, &move_count, count == 0);

        if (count == 0) { // 첫 번째 실행에서 난수 배열 및 정렬 과정 출력
            //printf("첫 번째 난수 배열 정렬 과정: 선택 정렬\n");
            //printf("첫 번째 난수 배열 정렬 과정: 삽입 정렬\n");
            printf("첫 번째 난수 배열 정렬 과정: 버블 정렬\n");
        }

        // 총 비교 및 이동 횟수에 더하기
        total_compare += compare_count;
        total_move += move_count;
    }

    // 평균 비교 및 이동 횟수 계산 및 출력
    printf("평균 비교 횟수: %f\n", (double)total_compare / 20);
    printf("평균 이동 횟수: %f\n", (double)total_move / 20);

    return 0;
}
