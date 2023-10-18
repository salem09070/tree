#include <stdio.h>

#define SIZE 17

// �迭 ��� �Լ�
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// �� ������ ��ġ�� �ٲٴ� �Լ�
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// �־��� ���� �� �ڽ� ������ ���Ͽ� �� ������ �����ϰ� ����� �Լ�
void heapify(int arr[], int n, int i) {
    int largest = i;      // ��Ʈ
    int left = 2 * i + 1; // ���� �ڽ�
    int right = 2 * i + 2; // ������ �ڽ�

    // ���� �ڽ��� �θ𺸴� ū ���
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // ������ �ڽ��� ���� ���� ū ������ ū ���
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // ���� ū ���� ��Ʈ�� �ƴ϶�� �ٲٰ� �ٽ� heapify
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// ���ο� ���Ҹ� ���� �߰��ϴ� �Լ�
void insertHeap(int arr[], int n) {
    int i = n;
    // ���ο� ���Ұ� �θ𺸴� ū ��� ��� ��ġ�� �ٲ�
    while (i && arr[(i - 1) / 2] < arr[i]) {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// �迭�κ��� �ִ� ���� �����ϴ� �Լ�
void buildHeap(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        insertHeap(arr, i);
        printArray(arr, i + 1); // ���� ���� ���
    }
}

// �� ���� �Լ�
void heapSort(int arr[], int n) {
    buildHeap(arr, n);  // ���� �ִ� ���� ����

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);  // ��Ʈ(���� ū ��)�� ������ ���Ҹ� �ٲ�
        heapify(arr, i, 0);      // ������ ���ҷ� �ٽ� ���� ����
        printArray(arr, i);      // ���� ���� ���
    }
}

int main() {
    int arr[SIZE] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 34, 85, 29, 78, 41, 56, 86 };
    heapSort(arr, SIZE); // �� ���� ����
    printArray(arr, SIZE); // �߰��� �κ�: ���ĵ� �迭 ���
    return 0;
}
