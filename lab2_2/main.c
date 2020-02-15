#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int str_size(char *str) {
    int i = 0;
    while (*(str + i)) { ++i; }
    return i;
}

int int_size(int num) {
    int i = 0;
    while (num / 10 != 0) {
        ++i;
        num /= 10;
    }
    return i;
}

int get_decimal_on_position(int num, int pos) {
    return (int) fmod(num / pow(10, pos), 10);
}

char *numtos(int num) {
    int size = int_size(num), i;
    char *A = (char *) malloc((size + 1) * sizeof(char));
    if (num < 0) {
        *A = 45;
    } else {
        *A = 43;
    }
    if (num < 0) {
        num *= -1;
    }
    for (i = 0; i <= size; ++i) {
        *(A + i + 1) = get_decimal_on_position(num, size - i) + 48;
    }
    *(A + 1 + size + 1) = 0;
    return A;
}

int stonum(char *str) {
    int is_neg = 0, num = 0, i;
    int len = str_size(str);
    if (*str == 45) {
        is_neg = 1;
        len -= 1;
    } else if (*str == 43) {
        len -= 1;
    }

    for (i = len; i > 0; --i) {
        num += (*(str + i) - 48) * pow(10, len - i);
    }
    if (is_neg) {
        num *= -1;
    }
    return num;
}

char *stoupper(unsigned char *str) {
    int i;
    for (i = 0; i < str_size(str); ++i) {
        int ascii = *(str + i);
        if (ascii >= 97 && ascii <= 122) {
            *(str + i) = ascii - 32;
        } else if (ascii >=224 && ascii <= 255){
            *(str + i) = ascii - 32;
        }
    }
    return str;
}

char *bintodec(char *bin) {
    int size = str_size(bin)-1, i, num = 0;
    for(i=0; i<=size; ++i){
        num += (*(bin + size - i) - 48) * pow(2, size-i);
    }
    return numtos(num);
}


int main() {
    printf("numtos: %s\n", numtos(-12334534));
    printf("bintodec: %s\n",bintodec("1110"));
    printf("%d\n", stonum("-12323452343456"));
    return 0;
}
