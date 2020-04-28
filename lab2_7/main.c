#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "decimal.h"

int main() {
    char num1_str[100];
    char num2_str[100];
    printf("Введите первое число: ");
    scanf("%s", num1_str);
    printf("Введите второе число: ");
    scanf("%s", num2_str);
    DECIMAL *num1 = str_to_decimal(num1_str);
    DECIMAL *num2 = str_to_decimal(num2_str);
    printf("Сумма этих чисел: ");
    print_decimal(summarize(num1, num2));
    printf("Разность этих чисел: ");
    print_decimal(subtract(num1, num2));
    printf("Произведение этих чисел: ");
    print_decimal(multiply(num1, num2));
    return 0;
}
