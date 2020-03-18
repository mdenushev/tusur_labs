//
// Created by max on 3/18/20.
//
#include <stdio.h>
typedef struct {
    int rubles;
    int penny;
} price;

typedef struct {
    char *title;
    price price;
} item;

int get_price_in_penny(item item){
    return item.price.penny + item.price.rubles * 100;
}

char *max_price(item item1, item item2){
    int price1 = get_price_in_penny(item1), price2 = get_price_in_penny(item2);
    if (price1 > price2){
        return item1.title;
    } else {
        return item2.title;
    }
}

int main(){
    item item1, item2;

    item1.price.penny = 0;
    item1.price.rubles = 10;
    item1.title = "item1 title";

    item2.price.penny = 0;
    item2.price.rubles= 11;
    item2.title = "item2 title";

    printf("Max price item: %s", max_price(item1, item2));
    return 0;
}