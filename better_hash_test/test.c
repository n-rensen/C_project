#include "hashtable.h"
#include "hashtable.c"

#define MAX_LINE 4096

uint64_t hash(char *passw, size_t length){
    uint64_t hash_value = 0;
    for(int i=0; i<length; i++){
        hash_value += passw[i];
        hash_value = hash_value * passw[i];
    }
    return hash_value;
}

void cleafunction(void *p){
    printf("destroying %p\n", p);
    free(p);
}

int main(int argc, char**argv){
    if (argc != 3){
        printf("usage: %s <wordlist filename> <num guess>\n");
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    uint32_t num_guesses = atol(argv[2]);

    const int tablesize = (1<<20); // 1MegaEntry == 1048576

    hash_table *table = hash_table_create(tablesize, hash, NULL);

    FILE *fp = fopen(filename, "r");
    char buffer[MAX_LINE];
    uint32_t numwords = 0;
    while (!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL){
        buffer[strcspn(buffer, "\n\r")] = 0;
        char *newentry = malloc(strlen(buffer)+1);
        strcpy(newentry, buffer);
        hash_table_insert(table, newentry, newentry);
        numwords++;
    }
    fclose(fp);
    printf("loaded %d words into table.\n", numwords);

    //hash_table_print(table);
    hash_table_destroy(table);
}