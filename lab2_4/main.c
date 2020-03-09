#include <stdio.h>
#include <stdlib.h>

struct Word {
    int start;
    int end;
};

int str_size(const char *str) {
    int i = 0;
    while (*(str + i)) { ++i; }
    return i;
}

struct WordsArray {
    struct Word **array;
    int count;
};

void change_chars(char *str, int from, int to) {
    *(str + from) = *(str + from) + *(str + to);
    *(str + to) = *(str + from) - *(str + to);
    *(str + from) = *(str + from) - *(str + to);
}

void move_string(char *str, int start, int change) {
    int i, size = str_size(str);
    if (change == 0) {
        return;
    }
    if (change > 0) {
        for (i = size; i < start; --i) {
            change_chars(str, i, i + change);
        }
    } else {
        for (i = start; i < size; ++i) {
            change_chars(str, i, i + change);
        }
    }
    *(str + size + change) = 0;
}

struct WordsArray *find_words(char *str) {
    int size = str_size(str), start = 0, word_flag = 0, count = 0;
    int i;

    struct Word **words = (struct Word **) malloc(sizeof(struct Word *) * size / 2 + 1);

    for (i = 0; i < size; ++i) {
        if (*(str + i) != 32 && !word_flag) {
            word_flag = 1;
            start = i;
        } else if (*(str + i) == 32 && word_flag) {
            *(words + count) = malloc(sizeof(struct Word));
            (*(words + count))->start = start;
            (*(words + count))->end = i - 1;
            count++;
            start = i;
            word_flag = 0;
        } else if (*(str + i) == 32 && !word_flag) {
            start = i;
        }
    }
    if (word_flag) {
        *(words + count) = malloc(sizeof(struct Word));
        (*(words + count))->start = start;
        (*(words + count))->end = i-1;
        count++;
    }

    struct WordsArray *result = malloc(sizeof(struct WordsArray));
    result->array = words;
    result->count = count;
    return result;
}

int count_similar_words(struct WordsArray *words, const char *str) {
    int count = 0, i, j, first_letters_equal, last_letter_equal;
    for (i = 0; i < words->count; ++i) {
        for (j = i + 1; j < words->count; ++j) {
            first_letters_equal = *(str + (*(words->array + i))->start) == *(str + (*(words->array + j))->start);
            last_letter_equal = *(str + (*(words->array + i))->end) == *(str + (*(words->array + j))->end);
            if (first_letters_equal && last_letter_equal) count++;
        }
    }
    return count;
}

int count_similar(struct WordsArray *words, const char *str){
    int count = 0, i, first_letter_equals_last;
    for (i = 0; i < words->count; ++i){
        first_letter_equals_last = *(str + (*(words->array + i))->start) == *(str + (*(words->array + i))->end);
        if (first_letter_equals_last){
            count++;
        }
    }
    return count;
}

int largest_size(struct WordsArray *words){
    int max = 0, i, size;
    for (i = 0; i < words->count; ++i){
        size = (*(words->array + i))->end - (*(words->array + i))->start + 1;
        if (size > max){
            max = size;
        }
    }
    return max;
}

void trim_str(char *str){
    int between_words = 0, last_letter_index = 0, i, offset = 0;
    for ( i = 0; i < str_size(str); ++i){
        if (*(str + i-offset) == 32 && !between_words){
            move_string(str, i - offset, -1);
            offset += 1;
        } else if (*(str + i-offset) == 32 && between_words){
            between_words = 0;
        } else {
            last_letter_index = i;
            between_words = 1;
        }
    }
    *(str + last_letter_index + 1) = 0;
}

int main() {
    char str[] = "     mom cleans   chips  window ";
    struct WordsArray *result = find_words(str);
    printf("Количество слов в строке: %d\n", result->count);
    printf("Количество слов с одинаковыми буквами в начале и конце: %d\n", count_similar_words(result, str));
    printf("Количество слов начинающихся и заканчивающихся на одну и ту же букву: %d\n", count_similar(result, str));
    printf("Длина самого длинного слова: %d\n", largest_size(result));
    trim_str(str);
    printf("Строка с удаленными пробелами: %s;\n", str);
    return 0;
}
