#include <stdio.h>

#define SIZE 17

// 배열 출력 함수
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 두 정수의 위치를 바꾸는 함수
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 주어진 노드와 그 자식 노드들을 비교하여 힙 성질을 만족하게 만드는 함수
void heapify(int arr[], int n, int i) {
    int largest = i;      // 루트
    int left = 2 * i + 1; // 왼쪽 자식
    int right = 2 * i + 2; // 오른쪽 자식

    // 왼쪽 자식이 부모보다 큰 경우
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 오른쪽 자식이 현재 가장 큰 값보다 큰 경우
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 가장 큰 값이 루트가 아니라면 바꾸고 다시 heapify
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// 새로운 원소를 힙에 추가하는 함수
void insertHeap(int arr[], int n) {
    int i = n;
    // 새로운 원소가 부모보다 큰 경우 계속 위치를 바꿈
    while (i && arr[(i - 1) / 2] < arr[i]) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 배열로부터 최대 힙을 구성하는 함수
void buildHeap(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        insertHeap(arr, i);
        printArray(arr, i + 1); // 현재 상태 출력
    }
}

// 힙 정렬 함수
void heapSort(int arr[], int n) {
    buildHeap(arr, n);  // 먼저 최대 힙을 구성

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);  // 루트(가장 큰 값)와 마지막 원소를 바꿈
        heapify(arr, i, 0);      // 나머지 원소로 다시 힙을 구성
        printArray(arr, i);      // 현재 상태 출력
    }
    printArray(arr, 1); // 마지막 상태 출력
}

int main() {
    int arr[SIZE] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86 };
    heapSort(arr, SIZE); // 힙 정렬 실행
    return 0;
}
