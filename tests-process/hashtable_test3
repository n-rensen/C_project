#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_PASSW 256
#define TABLE_SIZE 10

typedef struct password{
    char passw[MAX_PASSW];
    int hashpass;
    struct password *next;
} password;

password * hash_table[TABLE_SIZE];

// hash function
unsigned int hash(char *passw){
    int length = strnlen(passw, MAX_PASSW);
    unsigned int hash_value = 0;

    for (int i = 0; i < length; i++){
        hash_value += passw[i];
        hash_value = (hash_value * passw[i]) % TABLE_SIZE; // La contenance maximale etant fixee a 10.
    }

    return hash_value;
}

// initialise table
void init_hash_table() {
    for (int i=0; i < TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
}


// printing table
void print_table(){
    printf("TABLE START \n");
    for(int i=0; i < TABLE_SIZE; i++){
        if (hash_table[i] == NULL){
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t ", i);
            password *tmp = hash_table[i];
            while (tmp != NULL){
                printf("%s - ", tmp->passw);
                tmp = tmp->next;
            }
        }
    }
    printf("TABLE END \n");
}

// insert function
bool hash_table_insert(password *p){
    if (p == NULL) return false;
    int index = hash(p->passw);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

// lookup function
password *hashtable_lookup (char *passw){
    int index = hash(passw);

    password *tmp = hash_table[index];
    while(tmp!= NULL && strncmp(tmp->passw, passw, MAX_PASSW) != 0){
        tmp = tmp->next;
    }
    return tmp;
}

password*hash_table_delete(char *passw){
    int index = hash(passw);

    password *tmp = hash_table[index];
    password *prev = NULL;
    while(tmp!= NULL && strncmp(tmp->passw, passw, MAX_PASSW) != 0){
        prev = tmp;
        tmp = tmp->next;
    }
    if(tmp != NULL){
        return NULL;
    }
    if (prev == NULL){
        // delete head
        hash_table[index] = tmp->next;
    } else {
        prev->next = tmp->next;
    }
    return tmp;
}

// main function
int main() {
    init_hash_table();
    print_table();
    //return 0;

    password Azertyuiop = {.passw="Azertyuiop", .hashpass=5};
    password Azerty = {.passw="Azerty", .hashpass=6};
    password admin = {.passw="admin", .hashpass=12};

    hash_table_insert(&Azertyuiop);
    hash_table_insert(&Azerty);
    hash_table_insert(&admin);

    print_table();

    password *tmp = hashtable_lookup("admin");

    if (tmp == NULL){
        printf("Not found !\n");
    } else {
        printf("Found %s.\n");
    }

    tmp = hashtable_lookup("BruceToutPuissant");

    if (tmp == NULL){
        printf("Not found !\n");
    } else {
        printf("Found %s.\n");
    }
}