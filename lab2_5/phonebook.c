//
// Created by max on 3/18/20.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *phone;
} contact;

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

// Returns contract's name
char *find_contact_by_phone(contact* contacts, char *phone, int count){
    int i;
    for (i = 0; i < count; ++i){
        if (is_str_same(((contacts+i)->phone), phone)) return (contacts + i) -> name;
    }
    return NULL;
}

// Returns contract's phone
char *find_contact_by_name(contact* contacts, char *name, int count){
    int i;
    for (i = 0; i < count; ++i){
        if (is_str_same(((contacts+i)->name), name)) return (contacts + i) -> phone;
    }
    return NULL;
}


int main(){
    contact* contacts = malloc(2 * sizeof(contact));
    contacts->phone = "+79999999999";
    contacts->name = "Max";

    (contacts+1)->phone = "+78888888888";
    (contacts+1)->name = "Mom";

    printf("Searching for contact with name: \"Max\"\n");
    char *contact1 = find_contact_by_name(contacts, "Max", 2);
    if (contact1 != NULL){
        printf("Found contact: %s.\n\n", contact1);
    } else {
        printf("No contact found.\n\n");
    }

    printf("Searching for contact with name: \"Dad\"\n");
    char *contact2 = find_contact_by_name(contacts, "Dad", 2);
    if (contact2 != NULL){
        printf("Found contact: %s.\n\n", contact2);
    } else {
        printf("No contact found.\n\n");
    }

    printf("Searching for contact with phone: \"+78888888888\"\n");
    char *contact3 = find_contact_by_phone(contacts, "+78888888888", 2);
    if (contact3 != NULL){
        printf("Found contact: %s.\n\n", contact3);
    } else {
        printf("No contact found.\n\n");
    }

    printf("Searching for contact with phone: \"+71234567890\"\n");
    char *contact4 = find_contact_by_phone(contacts, "+1234567890", 2);
    if (contact4 != NULL){
        printf("Found contact: %s.\n\n", contact4);
    } else {
        printf("No contact found.\n\n");
    }
    return 0;
}