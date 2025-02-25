#include <stdio.h>


/*
тип данных long long int
упорядочить по нубыванию
сортировки: простым выбором и пирамидальная
*/


void swap(long long int* a, long long int* b) {
    long long int temp = *a;
    *a = *b;
    *b = temp;
}

void print_list(long long int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lld ", arr[i]);
    }
}

void simple_choice_sort(long long int* arr, int n) {
    int j = n - 1;
    int max_i = 0;

    for (int i = 0; i < n; i++) {
        for (int q = 0; q <= j; q++) {
            if (arr[q] > arr[max_i]) {
                max_i = q;
            }
        }

        swap(&arr[max_i], &arr[j]);

        max_i = 0;
    }
}

void heapify(long long int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        long long int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heap_sort(long long int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        long long int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main(void) {
    long long int arr[] = { 1, 4, 3, 2 };
    heap_sort(arr, 4);
    print_list(arr, 4);

    return 0;
}