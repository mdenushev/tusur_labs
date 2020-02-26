#include <stdio.h>
#include <stdlib.h>

struct IncludesArray {
    int *array;
    int size;
};

int str_size(const char *str) {
    int i = 0;
    while (*(str + i)) { ++i; }
    return i;
}

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

struct IncludesArray find_includes(char *source, char *search) {
    int found_start = -1, count = 0, i, search_size = str_size(search), found_count = 0, source_size = str_size(source);

    int *found = (int *) malloc(sizeof(int) * source_size / search_size);

    for (i = 0; i < source_size; ++i) {
        if (count == search_size) {
            *(found + found_count++) = found_start;
        }
        if (count > 0 && *(source + i) == *(search + count)) {
            ++count;
        } else if (*(source + i) == *search) {
            found_start = i;
            count = 1;
        } else {
            count = 0;
        }
    }
    if (count == search_size) {
        *(found + found_count++) = found_start;
    }
    struct IncludesArray *result = malloc(sizeof(struct IncludesArray));
    result->array = found;
    result->size = found_count;
    return *result;
}


char *find_between_spaces(char *str) {
    char *result = (char *) malloc(sizeof(char) * str_size(str));
    int started = 0, i = 0, count = 0, finished = 0;
    for (i = 0; i < str_size(str); ++i) {
        if (*(str + i) == 32 && started == 0) {
            started = 1;
        } else if (*(str + i) == 32 && started == 1) {
            finished = 1;
            break;
        }
        if (started && *(str + i) != 32) {
            *(result + count) = *(str + i);
            ++count;
        }
    }
    if (started * finished) {
        *(result + count) = 0;
        return result;
    } else {
        return "";
    }
}

void remove_includes(char *source, char *search, int max) {
    int search_size = str_size(search);
    struct IncludesArray includes = find_includes(source, search);
    int limit = 0, i;
    if (max != 0) {
        if (max > includes.size) {
            limit = includes.size;
        } else {
            limit = max;
        }
    } else {
        limit = includes.size;
    }

    int offset = 0;
    for (i = 0; i < limit; ++i) {
        move_string(source, *(includes.array + i) + search_size + offset, -1 * search_size);
        offset -= search_size;
    }
}

void set_in_place(char *source, char *str, int start) {
    int i;
    for (i = 0; i < str_size(str); ++i) {
        *(source + start + i) = *(str + i);
    }
}

void replace_includes(char *source, char *search, char *replace, int max) {
    int search_size = str_size(search), replace_size = str_size(replace);
    struct IncludesArray includes = find_includes(source, search);
    int limit = 0, i;
    if (max != 0) {
        if (max > includes.size) {
            limit = includes.size;
        } else {
            limit = max;
        }
    } else {
        limit = includes.size;
    }

    int offset = 0;
    for (i = 0; i < limit; ++i) {
        move_string(source, *(includes.array + i) + search_size + offset, replace_size - search_size);
        offset += replace_size - search_size;
        set_in_place(source, replace, *(includes.array + i));
    }
}

int main() {
    printf("Find between spaces: %s\n", find_between_spaces("haha  haha "));
    char first[] = "hahahehehaha";
    remove_includes(first, "he", 1);
    printf("Remove first 'he': %s\n", first);
    char second[] = "hahahehehaha";
    remove_includes(second, "he", 0);
    printf("Remove all 'he': %s\n", second);
    char third[] = "hahahehehaha";
    replace_includes(third, "hehe", "hu", 1);
    printf("Remove first 'hehe' to 'hu': %s\n", third);
    return 0;
}
