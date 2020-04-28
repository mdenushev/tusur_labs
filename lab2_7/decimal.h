//
// Created by max on 4/28/20.
//

#ifndef LAB2_7_DECIMAL_H
#define LAB2_7_DECIMAL_H

#include "utils.h"
#include <stdlib.h>
typedef struct {
    long body;
    int power;
    int neg;
} DECIMAL;
// Конвертирует строку в DECIMAL
DECIMAL *str_to_decimal(char *str) {
    int len = str_size(str);
    DECIMAL *new_num = (DECIMAL *) malloc(sizeof(DECIMAL));
    new_num->power = 0;
    // Проверяем негативное ли число
    new_num->neg = *str == 45;

    new_num->body = 0;
    int i, power = 0;
    for (i = len; i >= 0; --i) {
        // Если находим точку, то записываем степень числа.
        if (*(str + i) == 46) {
            new_num->power = -1 * power;
            // Если цифра, то прибавляем к телу числа.
        } else if (*(str + i) > 47 && *(str + i) <= 57) {
            new_num->body += (long) ((*(str + i) - 48) * pow(10, power));
            ++power;
        }

    }
    return new_num;
}

// Выводим правильно сформатированное число.
void print_decimal(DECIMAL *num) {
    int body_len = count_body_length(num->body);
    // Если число негативное, то в начале пишем минус.
    if (num->neg) {
        printf("-");
        num->body = labs(num->body);
    }
    // Если степень числа равна 0, то число целое.
    if (num->power == 0) {
        printf("%lu", num->body);
        // Если степень числа больше 0, то выводим число и дописываем нули в конце.
    } else if (num->power > 0) {
        printf("%lu", num->body);
        int i;
        for (i = 0; i < num->power; ++i) {
            printf("0");
        }
        // Если модуль степени числа меньше длины его тела, то выводим передние нули, а затем само число.
    } else if (abs(num->power) > body_len) {
        int i;
        printf("0.");
        for (i = -1; i > num->power; --i) {
            printf("0");
        }
        printf("%lu", num->body);
        // Если модуль степени числа больше длины его тела, то число с точкой.
    } else {
        int i;
        for (i = 0; i <= body_len; ++i) {
            printf("%d", get_number_on_position(num->body, body_len - i));
            if (i - body_len == num->power) {
                printf(".");
            }
        }
    }
    printf("\n");
}

// Суммируем числа с точкой.
DECIMAL *summarize(DECIMAL *num1, DECIMAL *num2) {
    DECIMAL *new_num = (DECIMAL *) malloc(sizeof(DECIMAL));
    int power_difference = 0;
    // Приводим числа к большей по модулю степени и суммируем с учетом отрицательности чисел.
    if (num1->power < num2->power) {
        power_difference = num2->power - num1->power;
        new_num->power = num1->power;
        new_num->body = (long) (pow(-1, num2->neg) * (double) num2->body * pow(10, power_difference) +
                                pow(-1, num1->neg) * (double) num1->body);
    } else {
        power_difference = num1->power - num2->power;
        new_num->power = num2->power;
        new_num->body = (long) (pow(-1, num1->neg) * (double) num1->body * pow(10, power_difference) +
                                pow(-1, num2->neg) * (double) num2->body);
    }
    if (new_num->body < 0) {
        new_num->neg = 1;
        new_num->body = labs(new_num->body);
    } else {
        new_num->neg = 0;
    }
    return new_num;
}

DECIMAL *subtract(DECIMAL *num1, DECIMAL *num2) {
    DECIMAL *new_num2 = (DECIMAL *) malloc(sizeof(DECIMAL));
    // Создаем новое число, которое является копией второго с инвертированной отрицательностью
    new_num2->body = num2->body;
    new_num2->power = num2->power;
    new_num2->neg = !num2->neg;
    // Возвращаем сумму первого числа и видоизмененного второго.
    return summarize(num1, new_num2);
}

DECIMAL *multiply(DECIMAL *num1, DECIMAL *num2) {
    DECIMAL *new_num = (DECIMAL *) malloc(sizeof(DECIMAL));
    // Перемножаем тела чисел и складываем их степени
    new_num->body = num1->body * num2->body;
    new_num->power = num1->power + num2->power;
    // Новое число будет отрицательным только когда лишь одно из чисел отрицательно
    if (num1->neg + num2->neg == 1) {
        new_num->neg = 1;
    } else {
        new_num->neg = 0;
    }
    return new_num;
}

#endif //LAB2_7_DECIMAL_H
