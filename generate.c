#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

#define INPUT_CATALOG "files/inputs/"
#define OUTPUT_CATALOG "files/outputs/"

#define SMALL_NUM 10
#define LITTLE_NUM 100
#define MIDDLE_NUM 1000
#define BIG_NUM 10000

#define MAX_BUF_SIZE 80

#define BORDER 100000


FILE* file_open(char* filename, char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        if (strcmp("w", mode) == 0) {
            printf("Ошибка при открытии файла на запись!!\n");
        }

        if (strcmp("r", mode) == 0) {
            printf("Ошибка при открытии файла на чтение!!\n");
        }

        return NULL;
    }

    return file;
}

void print_list(long long int* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%lld ", arr[i]);
    }
}

long long int get_rand_number() {
    return ((long long int)rand() << 32) | rand();
}

long long int* generate_array(int n) {
    long long int* arr = (long long int*) malloc(sizeof(long long int) * n);

    for (int i = 0; i < n; i++) {
        arr[i] = get_rand_number();
        
        while (arr[i] >= LLONG_MAX - BORDER || arr[i] <= LLONG_MIN + BORDER) {
            arr[i] = get_rand_number();
        }
    }

    return arr;
}

long long int* generate_sorted_array(int n) {
    long long int* arr = (long long int*) malloc(sizeof(long long int*) * n);

    arr[0] = get_rand_number();
    for (int i = 1; i < n; i++) {
        int ost = get_rand_number() % 10;
        
        while (ost == 0) {
            ost = get_rand_number() % 10;
        }

        arr[i] = arr[i - 1] + ost;
    }

    return arr;
}

long long int* generate_rotated_sorted_array(int n) {
    long long int* arr = (long long int*) malloc(sizeof(long long int*) * n);

    arr[0] = get_rand_number();
    for (int i = 1; i < n; i++) {
        int ost = get_rand_number() % 10;

        while (ost == 0) {
            ost = get_rand_number() % 10;
        }

        arr[i] = arr[i - 1] - ost;
    }

    return arr;
}

void create_file(char* filename, char* filname_sorted, char* filename_rotated_sorted, int n) {
    long long int* arr = generate_array(n);
    long long int* sorted_arr = generate_sorted_array(n);
    long long int* rotated_sorted_arr = generate_rotated_sorted_array(n);

    FILE* file = file_open(filename, "w");
    FILE* file_sorted = file_open(filname_sorted, "w");
    FILE* file_rotated_sorted = file_open(filename_rotated_sorted, "w");

    for (int i = 0; i < n; i++) {
        fprintf(file, "%lld\n", arr[i]);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file_sorted, "%lld\n", sorted_arr[i]);
    }

    for (int i = 0; i < n; i++) {
        fprintf(file_rotated_sorted, "%lld\n", rotated_sorted_arr[i]);
    }

    fclose(file);
    fclose(file_sorted);
    fclose(file_rotated_sorted);

    free(arr);
    free(sorted_arr);
    free(rotated_sorted_arr);
}

void generate_data() {
    int num_params[] = { SMALL_NUM, LITTLE_NUM, MIDDLE_NUM, BIG_NUM };
    int len = sizeof(num_params) / sizeof(num_params[0]);

    for (int i = 0; i < len; i++) {
        char filename[MAX_BUF_SIZE];
        char filename_sorted[MAX_BUF_SIZE];
        char filename_rotated_sorted[MAX_BUF_SIZE];

        sprintf(filename, "%sunsorted%d.txt", INPUT_CATALOG, num_params[i]);
        sprintf(filename_sorted, "%ssorted%d.txt", INPUT_CATALOG, num_params[i]);
        sprintf(filename_rotated_sorted, "%srotated_sorted%d.txt", INPUT_CATALOG, num_params[i]);

        create_file(filename, filename_sorted, filename_rotated_sorted, num_params[i]);
    }
}

int main(void) {
    srand(time(NULL));

    generate_data();

    return 0;
}