//
//  main.c
//  Talalay_VV_C
//
//  Created by Vitaliy Talalay on 18.12.2021.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Array_Size 30

void task1(int N, int *a, int *b);
int bubble_sort(int N, int *a);
int improved_bubble_sort(int N, int *a);

void task2(int N, int *a);
int shaker_sort(int N, int *a);

void task3(int N, int *a);
int binary_search(int N, int *a, int val);

void swap(int *a, int *b);
void print_arr(int N, int *a);
void menu(void);

int main() {
    int taskNumber = 0;
    do {
        srand(time(0));
        int arr[Array_Size];
        int arr1[Array_Size];
        int arr2[Array_Size];
        for(int i = 0; i < Array_Size; ++i){
            arr[i] = rand() % 100;
            arr1[i] = arr[i];
            arr2[i] = arr[i];
        }
        menu();
        scanf("%i",&taskNumber);
        switch (taskNumber) {
            case 1:
                task1(Array_Size, arr1, arr2);
                break;
            case 2:
                task2(Array_Size, arr1);
                break;
            case 3:
                shaker_sort(Array_Size, arr1);
                task3(Array_Size, arr1);
                break;
            case 0:
                printf("Программа завершена, всего доброго!\n");
                break;
            default:
                printf("Такого задания нет\n");
                break;
        }
    }
    while (taskNumber != 0);
    return 0;
}

void menu() {
     printf("******************\n");
     printf("Введите номер задания:\n");
     printf("'1' - Пузырьковая сортировка\n");
     printf("'2' - Шейкерная сортировка\n");
     printf("'3' - Бинарный алгоритм\n");
     printf("'0' - Выход\n");
 }

/*
 Задание 1. Попробовать оптимизировать пузырьковую сортировку. Сравнить
 количество операций сравнения оптимизированной и не оптимизированной программы.
 Написать функции сортировки, которые возвращают количество операций.
 */

void task1(int N, int *a, int *b) {
    printf("******************\n");
    printf("Задание 1\n");
    printf("Заданный массив: ");
    print_arr(Array_Size, a);
    
    int counter = bubble_sort(Array_Size, b);
    int counter_improved = improved_bubble_sort(Array_Size, a);
    
    printf("Массив после сортировки: ");
    print_arr(Array_Size, a);
    printf("Количество операций пузырьковой сортировки - \t%d\n", counter);
    printf("Количество операций улучшенной пузырьковой сортировки - \t%d\n", counter_improved);
}

int bubble_sort(int N, int *a) {
    int counter = 0;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N-1; ++j) {
            ++counter;
            if( a[j] > a[j+1] ) {
                swap(&a[j], &a[j+1]);
            }
        }
    }
    return counter;
}

int improved_bubble_sort(int N, int *a) {
    int counter = 0;
    int flag = 0;
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N-1; ++j) {
            ++counter;
            if( a[j] > a[j+1] ) {
                swap(&a[j], &a[j+1]);
                flag = 1;
            }
        }
        if(!flag) return counter;
        ++counter;
        flag = 0;
    }
    return counter;
}

// Задание 2. *Реализовать шейкерную сортировку.

void task2(int N, int *a) {
    printf("******************\n");
    printf("Задание 2\n");
    printf("Заданный массив: ");
    print_arr(Array_Size, a);
    int count = shaker_sort(N, a);
    printf("Массив после сортировки: ");
    print_arr(Array_Size, a);
    printf("Количество операций - \t%d\n", count);
}

int shaker_sort(int N, int *a){
    int counter = 0;
    int is_change = 0;
    for(int i = 0; i < N; ++i) {
        for(int j=i; j<N-1-i; ++j) {
            ++counter;
            if( a[j] > a[j+1] ) {
                swap(&a[j], &a[j+1]);
                is_change = 1;
            }
        }
        for(int j=N-1-i; j>0+i; --j) {
            ++counter;
            if( a[j-1] > a[j] ) {
                swap(&a[j-1], &a[j]);
                is_change = 1;
            }
        }
        if(!is_change) return counter;
        ++counter;
        is_change = 0;
    }
    return counter;
}

/*
 Задание 3. Реализовать бинарный алгоритм поиска в виде функции, которой
 передается отсортированный массив. Функция возвращает индекс найденного
 элемента или -1, если элемент не найден.
 */

void task3(int N, int *a){
    printf("******************\n");
    printf("Задание 3\n");
    printf("Индексы массива: ");
    for(int i=0; i<N; ++i)
        printf("%2d ", i);
    printf("\nЗаданный массив: ");
    print_arr(N, a);
    printf("Введите значение из массива для поиска его индекса: ");
    int num = 0;
    scanf("%d", &num);
    int result = binary_search(N, a, num);
    if(result == -1){
        printf("В массиве нет значения %d\n", num);
        return;
    }
    printf("Значение %d находится под индексом %d\n",num ,result);
}

int binary_search(int N, int *a, int val){
    int lht = 0, rht = N - 1;
    while(lht <= rht) {
        int mid = lht + (rht - lht) / 2;
        if (val == a[mid]) return mid;
        if (val < a[mid]) rht = mid - 1;
        else if ( val > a[mid]) lht = mid + 1;
    }
    return -1;
}

//Дополнительные функции

void swap(int *a, int *b) {
    if (a != b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

void print_arr(int N, int *a) {
    for (int i = 0; i < N; ++i) {
        printf("%2i ", a[i]);
    }
    printf("\n");
}
