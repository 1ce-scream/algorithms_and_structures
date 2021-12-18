//
//  main.c
//  Talalay_VV_C
//
//  Created by Vitaliy Talalay on 18.12.2021.
//

#include <stdio.h>
#include <math.h>

void task1(void);
int DecToBin(int n);
void task2(void);
int task2_recursion(int input, int degree);
int task2_fast(int a, int b, int n);
void task3(void);
int getSolutionsCount(int number1, int number2);


void menu(void);

int main(int argc, const char * argv[]) {
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
            case 3:
                task3();
                break;
            case 0:
                printf("Программа завершена, всего доброго!\n");
                break;
            default:
                printf("Такого задания нет\n");
                break;
        }
    } while (taskNumber != 0);
    
    return 0;
}

void menu() {
    printf("******************\n");
    printf("Введите номер задания:\n");
    printf("'1' - Перевод числа из DEC в BIN\n");
    printf("'2' - Возведение числа в степень\n");
    printf("'3' - Исполнитель калькулятор\n");
    printf("'0' - Выход\n");
}

/*
 Задание 1. Реализовать функцию перевода из десятичной системы в двоичную,
 используя рекурсию.
 */

void task1() {
    int input = 0;
    printf("******************\n");
    printf("Задание 1\n");
    printf("Введите число для перевода в двоичную систему\n");
    scanf("%i", &input);
    
    int result = DecToBin(input);
    printf("Число %i в двоичном формате %d", input, result);
}

int DecToBin(int n) {
    if (n < 2) {
        return n;
    } else if (n == 0) {
        return 0;
    } else
        return n % 2 + 10 * DecToBin(n / 2);
}

/*
 Задание 2. Реализовать функцию возведения числа a в степень b:
 a. без рекурсии;
 b. рекурсивно;
 c. *рекурсивно, используя свойство четности степени.
 */

void task2(void) {
    int input, degree = 0;
    printf("******************\n");
    printf("Задание 2\n");
    printf("Введите число и степень: \n");
    scanf("%i %i", &input, &degree);
    
    int result1 = 1;
    for(int i = degree ; i >= 1; --i) {
        result1 *= input;
    }
    printf("Без рекурсии: ");
    printf("%i ˆ %i = %d \n", input, degree, result1);
    
    int result2 = task2_recursion(input, degree);
    printf("Рекурсия: ");
    printf("%i ˆ %i = %d \n", input, degree, result2);
    
    int result3 = task2_fast(input, degree, 1);
    printf("Ускоренная рекурсия: ");
    printf("%i ˆ %i = %d \n", input, degree, result3);
}

int task2_recursion(int input, int degree) {
    if (degree <= 1) {
        return input;
    } else if (degree == 0)
        return 1;
    else
        return input * task2_recursion(input, --degree);
}

int task2_fast(int a, int b, int n){
    if (b == 0) {
        return n;
    }
    if (b % 2) {
        return task2_fast(a, --b, n * a);
    } else {
        return task2_fast(a * a, b / 2, n);
    }
}

/*
 Задание 3. **Исполнитель Калькулятор преобразует целое число, записанное
 на экране. У исполнителя две команды, каждой команде присвоен номер:
 1) Прибавь 1
 2) Умножь на 2
 Первая команда увеличивает число на экране на 1, вторая увеличивает это число
 в 2 раза. Сколько существует программ, которые число 3 преобразуют в число 20?
 */

void task3(void) {
    int count = getSolutionsCount(3, 20);
    printf("******************\n");
    printf("Задание 3\n");
    printf("Количество решений: %i\n", count);
}

int getSolutionsCount(int number1, int number2) {
    if (number1 > number2 / 2) {
        return 1;
    }
    return getSolutionsCount(number1 + 1, number2)
    + getSolutionsCount(number1 * 2, number2);
}
