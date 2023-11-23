#include <stdio.h>
#include <stdlib.h>
#define MAX 20
// �̵�Ƚ���� ��Ƚ���� ī��Ʈ �� ����
int com, mov;
// ���� ����
inc_insertion_sort(int list[], int first, int last, int gap) {
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap) {
        key = list[i];
        for (j = i - gap; j >= first && key < list[j]; j = j - gap) {
            list[j + gap] = list[j];
        }
        list[j + gap] = key;
    }
}
// ���� ������ ����Ͽ� �� ���� �˰��� ����
void shell_sort(int list[], int n) {
    int i, gap;
    for (gap = n / 2; gap > 0; gap = gap / 2) {
        if ((gap % 2) == 0) gap++;
        for (i = 0; i < gap; i++)
            inc_insertion_sort(list, i, n - 1, gap);
        for (int k = 0; k < n; k++)
            printf("%d ", list[k]);
        printf("\n");
    }
}
// ī��Ʈ�� �� ����ϴ� ���� ���� �Լ�
// �̵� �� �� Ƚ���� ī��Ʈ�ϱ� ���� ���� ����
inc_insertion_sort_re(int list[], int first, int last, int gap) {
    int i, j, key;
    for (i = first + gap; i <= last; i = i + gap) {
        key = list[i];
        j = i - gap;
        while (j >= first && key < list[j]) {
            list[j + gap] = list[j];
            com++;
            j = j - gap;
        }
        list[j + gap] = key;
        mov++;
    }
}
// ī��Ʈ�� �� ����ϴ� �� ���� �Լ�
// �̵� �� �� Ƚ���� ī��Ʈ�ϱ� ���� �� ����
void shell_sort_re(int list[], int n) {
    int i, gap;
    for (gap = n / 2; gap > 0; gap = gap / 2) {
        if ((gap % 2) == 0) gap++;
        for (i = 0; i < gap; i++)
            inc_insertion_sort_re(list, i, n - 1, gap);
    }
}

int main(void) {
    int n = MAX;
    srand(time(NULL));
    int list[MAX];

    for (int i = 0; i < n; i++) {
        list[i] = rand() % 100;
    }
    printf("�� ���� \n\n");
    printf("���� ����Ʈ\n");
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n\n");
    shell_sort(list, n);
    printf("\n\n");

    mov = 0;
    com = 0;

    for (int t = 0; t < n - 1; t++) {
        for (int i = 0; i < n; i++) {
            list[i] = rand() % 100;
        }
        shell_sort_re(list, n);
    }

    printf("�� ���� \n��� �̵� Ƚ��: %d \n", (mov / (n - 1)));
    printf("��� �� Ƚ��: %d \n \n", (com / (n - 1)));


    return 0;
}