#include "hashtable.h"
#include "hashtable.c"
#include "sha256.c"

#define MAX_LINE 4096

/*uint64_t hash(char *passw, size_t length){
    uint64_t hash_value = 0;
    for(int i=0; i<length; i++){
        hash_value += passw[i];
        hash_value = hash_value * passw[i];
    }
    return hash_value;
}*/

#define FNV_PRIME 0x100000001b3
#define FNV_OFFSET 0xcbf29ce48422325UL

uint64_t hash_fnv1(char *passw, size_t length){
    uint64_t hash_value = FNV_OFFSET;
    for(int i=0; i<length; i++){
        hash_value *= FNV_PRIME;
        hash_value ^= passw[i];
    }
    return hash_value;
}

#define FNV_PRIME 0x100000001b3
#define FNV_OFFSET 0xcbf29ce48422325UL

uint64_t hash_fnv1a(char *passw, size_t length){
    uint64_t hash_value = FNV_OFFSET;
    for(int i=0; i<length; i++){
        hash_value ^= passw[i];
        hash_value *= FNV_PRIME;
    }
    return hash_value;
}

void cleafunction(void *p){
    printf("destroying %p\n", p);
    free(p);
}

int main(int argc, char**argv){
    if (argc != 3){
        printf("usage: %s <wordlist filename> <destination file>\n");
        return EXIT_FAILURE;
    }

    char *filename = argv[1];
    
    char *filedest = argv[2];
    //char *hashfind = argv[3];



    const int tablesize = (1<<20); // 1MegaEntry == 1048576

    hash_table *table = hash_table_create(tablesize, hash_fnv1a, NULL);

    FILE *fp = fopen(filename, "r");
    FILE *fout = fopen(filedest, "w");
    char buffer[MAX_LINE];
    uint32_t numwords = 0;

    // loop for SHA256

    while (!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL){
        buffer[strcspn(buffer, "\n\r")] = 0;
        char *newentry = malloc(strlen(buffer)+1);
        strcpy(newentry, buffer);

        


        unsigned char *data = newentry;        
        //char *newhash = malloc(sizeof(SHA256(data)));
        char *newhash = SHA256(data);

        //fprintf(fout,"%s", newentry, "%s ", newhash);
        fprintf(fout, "%s %s\n", newentry, newhash);

        hash_table_insert(table, newhash, newentry);
        numwords++;

        free(data);
        free(newhash);
    }

    fclose(fp);
    fclose(fout);

    //hash_table_print(table);
    printf("loaded %d words into table.\n", numwords);

    printf("\t... with %lu collisions\n", hash_table_collisions(table));
    

    /*char *tmp = hash_table_lookup(table, hashfind);

    if (tmp == NULL){
        printf("Not found !\n");
    } else {
        printf("Found !! Password is --->  %s\n", tmp);
    }*/

    

    hash_table_destroy(table);
}
