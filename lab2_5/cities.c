#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* title;
    char* country;
} city;

int str_size(const char *str){
    int i=0;
    while(*(str + i)) ++i;
    return i;
}

int is_str_same(char *str1, char *str2){
    int i, size = str_size(str1);
    if (size != str_size(str2)){
        return 0;
    }
    for (i = 0; i < size; ++i){
        if (*(str1 + i) != *(str2 + i)) return 0;
    }
    return 1;
}

void print_city(city city){
    printf("City: %s.\n", city.title);
    printf("Country: %s.\n\n", city.country);
}

void print_by_country(city* cities, char *country, int count){
    int i;
    for(i = 0; i < count; ++i){
        if (is_str_same((cities + i)->country, country)) print_city(*(cities + i));
    }
}

int main() {
    city* cities = (city*) malloc(sizeof(city) * 3);
    (cities + 0)->title = (char*) "Moscow";
    (cities + 0)->country = (char*) "Russia";

    (cities + 1)->title = (char*) "St. Petersburg";
    (cities + 1)->country = (char*) "Russia";

    (cities + 2)->title = (char*) "Kiev";
    (cities + 2)->country = (char*) "Ukraine";

    print_by_country(cities, (char*) "Ukraine", 3);

    return 0;
}
