#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int compare = 0;
int transp = 0;

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
void generate_output(long long int* arr, char* mark, char* sort_type, int n) {
    char filename[MAX_BUF_SIZE];

    sprintf(
        filename,
        "%s%s%s_were_%s%d.txt",
        OUTPUT_CATALOG,
        sort_type,
        (strcmp(sort_type, "heap_sort/") == 0 ? "hs" : "sls"),
        mark,
        n
    );

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
            compare++;
            
            if (arr[q] > arr[max_i]) {
                max_i = q;
            }
        }

        swap(&arr[max_i], &arr[j]);
        transp++;

        j--;
        max_i = 0;
    }
}

// функции для пирамидальной сортировки
void heapify(long long int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        compare++;

        if (arr[left] > arr[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        compare++;

        if (arr[right] > arr[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        transp++;

        heapify(arr, n, largest);
    }
}

void heap_sort(long long int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        transp++;

        heapify(arr, i, 0);
    }
}

int main(void) {
    int values[] = { SMALL_NUM, LITTLE_NUM, MIDDLE_NUM, BIG_NUM };
    int values_len = sizeof(values) / sizeof(values[0]);

    // пусть тут и хард код но по усл сказано что только три состояния входных массивов
    char names[3][MEAN_BUF_SIZE] = { UNSORTED, SORTED, SORTED_ROTATED };

    char sort_types[2][MEAN_BUF_SIZE] = { "heap_sort/", "selection_sort/" };
    int sort_types_len = sizeof(sort_types) / sizeof(sort_types[0]);

    for (int j = 0; j < values_len; j++) {
        for (int i = 0; i < 3; i++) {
            for (int t = 0; t < sort_types_len; t++) {
                char filename[MAX_BUF_SIZE];
                int n = values[j];

                sprintf(filename, "%s%s%d.txt", INPUT_CATALOG, names[i], n);

                long long int* arr = get_data(filename, n);

                if (strcmp(sort_types[t], "heap_sort/") == 0) {
                    heap_sort(arr, n);
                }
                else {
                    selection_sort(arr, n);
                }

                printf("Array is %s, Size of input array - %d, Sort is %s, Compares: %d, Transpositions: %d\n", names[i], n, sort_types[t], compare, transp);

                generate_output(arr, names[i], sort_types[t], n);

                free(arr);

                compare = 0;
                transp = 0;
            }
        }
    }

    return 0;
}