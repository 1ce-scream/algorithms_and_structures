//
//  main.c
//  Talalay_VV_C
//
//  Created by Vitaliy Talalay on 18.12.2021.
//

#include <stdio.h>
#include <math.h>

void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);

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
            case 4:
                task4();
                break;
            case 5:
                task5();
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
    printf("Введите номер задания:\n");
    printf("'1' - Подсчет BMI\n");
    printf("'2' - Определение максимального числа из 4х\n");
    printf("'3' - ОБмен двух значений\n");
    printf("'4' - Нахождение корней квадратного уравнения\n");
    printf("'5' - Определение времени года\n");
    printf("'0' - Выход\n");
}

/*
 1. Ввести вес и рост человека. Рассчитать и вывести индекс массы тела по
 формуле I=m/(h*h); где m-масса тела в килограммах, h - рост в метрах.
*/

 void task1() {
     double bmi, height, weight;
     printf("******************\n");
     printf("Задача 1\n");
     printf("Введите рост в см\n");
     scanf("%lf", &height);
     printf("Введите вес в кг\n");
     scanf("%lf", &weight);
     bmi = weight / (height / 100 * height / 100);
     printf("Индекс массы тела: %lf \n", bmi);
 }

// 2. Найти максимальное из четырех чисел. Массивы не использовать.

 void task2() {
     double a, b, c, d, max;
     printf("******************\n");
     printf("Задача 2\n");
     printf("Введите первое число\n");
     scanf("%lf", &a);
     printf("Введите второе число\n");
     scanf("%lf", &b);
     printf("Введите третье число\n");
     scanf("%lf", &c);
     printf("Введите четвертое число\n");
     scanf("%lf", &d);
     max = a;

     if (max < b) {
         max = b;
     }
     if (max < c) {
         max = c;
     }
     if (max < d) {
         max = d;
     }
     printf("Наибольшее число %lf \n", max);
 }

/*
 3. Написать программу обмена значениями двух целочисленных переменных:
 a. с использованием третьей переменной;
 b. *без использования третьей переменной.
*/

 void task3() {
     int a, b, temp;
     printf("******************\n");
     printf("Задача 3\n");
     a = 10;
     b = 20;
     printf("Начальные значения:\n a = %i, b = %i \n", a, b);
     temp = a;
     a = b;
     b = temp;
     printf("Значения после обмена:\n a = %i, b = %i \n", a, b);
     a = a + b;
     b = a - b;
     a = a - b;
     printf("Значения после повторного обмена:\n a = %i, b = %i \n", a, b);
     a = a - b;
     b = a + b;
     a = b - a;
     printf("Значения после повторного обмена:\n a = %i, b = %i \n", a, b);
     a = a * b;
     b = a / b;
     a = a / b;
     printf("Значения после повторного обмена:\n a = %i, b = %i \n", a, b);
 }

// 4. Написать программу нахождения корней заданного квадратного уравнения.

 void task4() {
     double a, b, c, D, x1, x2;
     printf("******************\n");
     printf("Задача 4\n");
     printf("Введите коэффициент a \n");
     scanf("%lf", &a);
     printf("Введите коэффициент b \n");
     scanf("%lf", &b);
     printf("Введите коэффициент c \n");
     scanf("%lf", &c);
     D = pow(b,2) - (4 * a * c);
     if (D < 0) {
         printf("Корней нет \n");
     } else if (D == 0) {
         x1 = -b / (2 * a);
         printf("Один корень: %lf \n", x1);
     } else if (D > 0) {
         double sd = sqrt(D);
         x1 = (-b + sd) / (2 * a);
         x2 = (-b - sd) / (2 * a);
         printf("Корней два: \n x1 = %lf \n x2 = %lf \n", x1, x2);
     }
 }

/*
 5. С клавиатуры вводится номер месяца. Требуется определить, к какому
 времени года он относится.
*/

 void task5() {
     int n;
     printf("******************\n");
     printf("Задача 5\n");
     printf("Введите номер месяца n \n");
     scanf("%i", &n);

     if (n == 1 || n == 2 || n == 12) {
         printf("Месяц относится к зиме");
     } else if (n == 3 || n == 4 || n == 5) {
         printf("Месяц относится к весне");
     } else if (n == 6 || n == 7 || n == 8) {
         printf("Месяц относится к лету");
     } else if (n == 9 || n == 10 || n == 11) {
         printf("Месяц относится к осени");
     } else {
         printf("Не правильно введен номер месяца\n");
     }
 }
