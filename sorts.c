#include <stdio.h>
#include <stdlib.h>

#define INPUT_CATALOG "files/inputs/"
#define OUTPUT_CATALOG "files/outputs/"

#define SMALL_NUM 10
#define LITTLE_NUM 100
#define MIDDLE_NUM 1000
#define BIG_NUM 10000

#define UNSORTED "unsorted"
#define SORTED "sorted"
#define SORTED_ROTATED "rotated_sorted"

#define MAX_BUF_SIZE 1000
#define MEAN_BUF_SIZE 200

/*
тип данных long long int
упорядочить по нубыванию
сортировки: простым выбором и пирамидальная
*/

// вспомогательные функци

// взятие данных из массивов ввода
long long int* crate_array(int n) {
    long long int* res = (long long int*) malloc(sizeof(long long int*) * n);

    return res;
}

long long int* get_data(char* filename, int n) {
    long long int* arr = crate_array(n);

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Ошибка при чтении файла входных данных для сортировки\n");

        return NULL;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%lld", &arr[i]);
    }

    fclose(file);

    return arr;
}

// mark - показатель с каким именем сохранять 
void generate_output(long long int* arr, char* mark, int n) {
    char filename[MAX_BUF_SIZE];

    sprintf(filename, "%swere_%s%d.txt", OUTPUT_CATALOG, mark, n);

    FILE* output_file = fopen(filename, "w");
    if (output_file == NULL) {
        printf("Ошибка при создании файла для вывода данных\n");

        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(output_file, "%lld\n", arr[i]);
    }

    fclose(output_file);
}

// перестановка значений двух переменных
void swap(long long int* a, long long int* b) {
    long long int temp = *a;
    *a = *b;
    *b = temp;
}

// вывод массива
void print_list(long long int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lld ", arr[i]);
    }

    printf("\n");
}

// сортировки

// сортировка простым выбором
void selection_sort(long long int* arr, int n) {
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

// функции для пирамидальной сортировки
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
    int values[] = { SMALL_NUM, LITTLE_NUM, MIDDLE_NUM, BIG_NUM };
    int values_len = sizeof(values) / sizeof(values[0]);

    // пусть тут и хард код но по усл сказано что только три состояния входных массивов
    char names[3][MEAN_BUF_SIZE] = { UNSORTED, SORTED, SORTED_ROTATED };

    for (int i = 0; i < 3; i++) {
        for  (int j = 0; j < values_len; j++) {
            char filename[MAX_BUF_SIZE];
            int n = values[j];

            sprintf(filename, "%s%s%d.txt", INPUT_CATALOG, names[i], n);

            long long int* arr = get_data(filename, n);

            heap_sort(arr, n);
            generate_output(arr, names[i], n);  
            
            free(arr);
        }
    }

    return 0;
}