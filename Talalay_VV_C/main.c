//
//  main.c
//  Talalay_VV_C
//
//  Created by Vitaliy Talalay on 18.12.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MaxArraySize 1000

void menu(void);
void task1(void);
void task2(void);

int main(int argc, const char * argv[]) {
    setlocale(LC_ALL, "RU");
    int taskNumber = 0;
    do {
        menu();
        scanf("%i",&taskNumber);
        switch (taskNumber) {
            case 1:
                task1();
                break;
            case 2:
                task2();
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
    printf("'1' - Сортировка подсчетом\n");
    printf("'2' - Быстрая сортировка\n");
    printf("'0' - Выход\n");
    printf("******************\n");
}


// 1. Реализовать сортировку подсчетом.

void countingSort(int *initialArray, int *sortedArray, int arrayLength) {
    int tempArray[MaxArraySize];
    for (int i = 0; i < MaxArraySize; i++) {
        tempArray[i] = 0;
    }
    for (int j = 0; j < arrayLength; j++) {
        tempArray[initialArray[j]] = tempArray[initialArray[j]] + 1;
    }
    for (int i = 1; i < MaxArraySize; i++) {
        tempArray[i] = tempArray[i] + tempArray[i - 1];
    }
    for (int j = arrayLength - 1; j >= 0; j--) {
        sortedArray[tempArray[initialArray[j]] - 1] = initialArray[j];
        tempArray[initialArray[j]] = tempArray[initialArray[j]] - 1;
    }
//    printf("\n Количество операций - %d\n", counter);
}


void task1(void) {
    int arrLenght;
    
    printf("Введите количество элементов для генерации массива: ");
    scanf("%d", &arrLenght);
    
    int unsortedArray[arrLenght];
    int sortedArray[arrLenght];
    
    printf("Исходный массив:\n");
    for (int i = 0 ; i < arrLenght; i++) {
        unsortedArray[i] = rand() % 1000;
        printf("%i ", unsortedArray[i]);
    }
    
    countingSort(unsortedArray, sortedArray, arrLenght);
    
    printf("\nОтсортированный массив:\n");
    for (int i = 0; i < arrLenght; i++) {
        printf("%i ", sortedArray[i]);
    }
    printf("\n");
}


// 2. Реализовать быструю сортировку.

void quickSort(int *numbersArray, int left, int right) {
    int pivot;
    int lHold = left;
    int rHold = right;
    pivot = numbersArray[left];
    while (left < right) {
        while ((numbersArray[right] >= pivot) && (left < right)) {
            right--;
        }
        
        if (left != right) {
            numbersArray[left] = numbersArray[right];
            left++;
        }
        
        while ((numbersArray[left] <= pivot) && (left < right)) {
            left++;
        }
        
        if (left != right) {
            numbersArray[right] = numbersArray[left];
            right--;
        }
    }
    
    numbersArray[left] = pivot;
    pivot = left;
    left = lHold;
    right = rHold;
    
    if (left < pivot) quickSort(numbersArray, left, pivot);
    if (right > pivot) quickSort(numbersArray, pivot + 1, right);
}

void task2(void) {
    
    int arrLenght;
    
    printf("Введите количество элементов для генерации массива: ");
    scanf("%d", &arrLenght);
    
    int unsortedArray[arrLenght];
    
    printf("Исходный массив:\n");
    for (int i = 0 ; i < arrLenght; i++) {
        unsortedArray[i] = rand() % 1000;
        printf("%i ", unsortedArray[i]);
    }
    
    quickSort(unsortedArray, 0, arrLenght - 1);
    
    printf("\nОтсортированный массив: \n");
    for (int i = 0 ; i < arrLenght; i++) {
        printf("%i ", unsortedArray[i]);
    }
}
