//
// Created by max on 4/28/20.
//

#ifndef LAB2_7_UTILS_H
#define LAB2_7_UTILS_H

#include <math.h>
// Считает длину строки
int str_size(const char *str) {
    int i = 0;
    while (*(str + i)) { ++i; }
    return i;
}

// Считает количество цифр в числе
int count_body_length(long body) {
    int i = 0;
    while (body / 10 != 0) {
        ++i;
        body /= 10;
    }
    return i;
}

// Возвращает цифру в позиции числа
int get_number_on_position(long num, int pos) {
    return (int) fmod((double) num / pow(10, pos), 10);
}
#endif //LAB2_7_UTILS_H
