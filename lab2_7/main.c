#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    long body;
    int power;
    int neg;
} DECIMAL;

int str_size(const char *str) {
    int i = 0;
    while (*(str + i)) { ++i; }
    return i;
}

int count_body_length(long body) {
    int i = 0;
    while (body / 10 != 0) {
        ++i;
        body /= 10;
    }
    return i;
}

int get_number_on_position(long num, int pos) {
    return (int) fmod((double) num / pow(10, pos), 10);
}

DECIMAL *str_to_decimal(char *str) {
    int len = str_size(str);
    DECIMAL *new_num = (DECIMAL *) malloc(sizeof(DECIMAL));
    new_num->power = 0;
    new_num->neg = *str == 45;

    new_num->body = 0;
    int i, power = 0;
    for (i = len; i >= 0; --i) {
        if (*(str + i) == 46) {
            new_num->power = -1 * power;
        } else if (*(str + i) > 47 && *(str + i) <= 57) {
            new_num->body += (long) ((*(str + i) - 48) * pow(10, power));
            ++power;
        }

    }
    return new_num;
}

void print_decimal(DECIMAL *num) {
    int body_len = count_body_length(num->body);
    if (num->neg) {
        printf("-");
        num->body = labs(num->body);
    }
    if (num->power == 0) {
        printf("%lu", num->body);
    } else if (num->power > 0) {
        printf("%lu", num->body);
        int i;
        for (i = 0; i < num->power; ++i) {
            printf("0");
        }
    } else if (abs(num->power) > body_len) {
        int i;
        printf("0.");
        for (i = -1; i > num->power; --i) {
            printf("0");
        }
        printf("%lu", num->body);
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

DECIMAL *summarize(DECIMAL *num1, DECIMAL *num2) {
    DECIMAL *new_num = (DECIMAL *) malloc(sizeof(DECIMAL));
    int power_difference = 0;
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
    DECIMAL *new_num = (DECIMAL *) malloc(sizeof(DECIMAL));
    int power_difference = 0;
    if (num1->power < num2->power) {
        power_difference = num2->power - num1->power;
        new_num->power = num1->power;
        new_num->body = (long) (pow(-1, num1->neg) * (double) num1->body -
                                pow(-1, num2->neg) * (double) num2->body * pow(10, power_difference));
    } else {
        power_difference = num1->power - num2->power;
        new_num->power = num2->power;
        new_num->body = (long) (pow(-1, num1->neg) * (double) num1->body * pow(10, power_difference) -
                                pow(-1, num2->neg) * (double) num2->body
        );
    }
    if (new_num->body < 0) {
        new_num->neg = 1;
        new_num->body = labs(new_num->body);
    } else {
        new_num->neg = 0;
    }
    return new_num;
}

DECIMAL *multiply(DECIMAL *num1, DECIMAL *num2) {
    DECIMAL *new_num = (DECIMAL *) malloc(sizeof(DECIMAL));
    new_num->body = num1->body * num2->body;
    new_num->power = num1->power + num2->power;
    if (num1->neg + num2->neg == 1) {
        new_num->neg = 1;
    } else {
        new_num->neg = 0;
    }
    return new_num;
}

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
