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
    
    int choice;
    
    printf("Que voulez vous faire ?\n");
    printf("1 - Charger un dictionnaire en mémoire et print un fichier d association en générant les hashes.\n");
    printf("2 - Charger un fichier d association en mémoire et effectuer des recherches.\n");
    printf("3 - Charger un dictionnaire en mémoire, gébérer les hashes et effectuer des recherches.\n");
    printf("Votre choix: ");

    scanf("%d",&choice);

    if(choice == 1){

        printf("\n Indiquez le fichier source: ");
        char *filename = malloc(sizeof(strlen +1));
        scanf("%s", &filename);
        printf("%s", &filename);
        printf("\n Indiquez le fichier de destination: ");
        char *filedest = malloc(sizeof(strlen));
        scanf("%s", &filedest);
        printf("%s", &filedest);

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
            char *newhash = SHA256(data);
            fprintf(fout, "%s %s\n", newentry, newhash);
            hash_table_insert(table, newhash, newentry);
            numwords++;
            free(data);
            free(newhash);
        }

        fclose(fp);
        fclose(fout);
        printf("loaded %d words into table.\n", numwords);
        printf("\t... with %lu collisions\n", hash_table_collisions(table));
        hash_table_destroy(table);

    } else if (choice == 2){

        printf("Indiquez le fichier source: \n");
        char *filename;
        scanf("%s", &filename);
        printf("Attention : Ce mode prend en compte un espace ' ' comme délimiteur. \n");
        printf("Il est possible d'utiliser le mode 3 pour effectuer une autre recherche.\n");

        const int tablesize = (1<<20);
        hash_table *table = hash_table_create(tablesize, hash_fnv1a, NULL);

        FILE *fp = fopen(filename, "r");
        char buffer[MAX_LINE];
        uint32_t numwords = 0;
        
        // loop for SHA256
        while (!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL){
            buffer[strcspn(buffer, "\n\r")] = 0;
            char *newentry = malloc(strlen(buffer)+1);
            strcpy(newentry, buffer);
            char* token;
            char* saveptr;
            char *entry;
            char *newhash;
            token = strtok_r(newentry," ", &saveptr);

            while (token != NULL){
                    char *entry = token;
                    char *newhash = saveptr;
                    hash_table_insert(table, newhash, entry);
                    numwords++;
                    token = NULL;
            }
        }

        fclose(fp);

        printf("loaded %d words into table.\n", numwords);
        printf("\t... with %lu collisions\n", hash_table_collisions(table));

        char search[64];
        while(strcmp(search, "exit") != 0){
            printf("Enter a 256digest \n");
            fflush( stdout );
            scanf( "%[^\n]", search );
            fgetc( stdin );
            char *tmp = hash_table_lookup(table, search);
            if (tmp == NULL){
                printf("Not found !\n");
            } else {
                printf("\nFound !! Password is --->  %s\n", tmp);
            }
            printf("\nPour quitter, entrez 'exit'.\n");
            scanf("%s", &search);

        }
        hash_table_destroy(table);

    } else if (choice == 3){

        printf("\n Indiquez le fichier source: ");
        char *filename;
        scanf("%s", &filename);

        FILE *fp = fopen(filename, "r");
        char buffer[MAX_LINE];
        uint32_t numwords = 0;
        const int tablesize = (1<<20); // 1MegaEntry == 1048576
        hash_table *table = hash_table_create(tablesize, hash_fnv1a, NULL);

        while (!feof(fp) && fgets(buffer, MAX_LINE, fp) != NULL){
            buffer[strcspn(buffer, "\n\r")] = 0;
            char *newentry = malloc(strlen(buffer)+1);
            strcpy(newentry, buffer);
            unsigned char *data = newentry;
            char *newhash = SHA256(data);
            hash_table_insert(table, newhash, newentry);
            numwords++;
            free(data);
            free(newhash);
        }
        fclose(fp);
        printf("loaded %d words into table.\n", numwords);
        printf("\t... with %lu collisions\n", hash_table_collisions(table));

        char search[64];
        while(strcmp(search, "exit") != 0){
            printf("Enter a 256digest \n");
            fflush( stdout );
            scanf( "%[^\n]", search );
            fgetc( stdin );
            char *tmp = hash_table_lookup(table, search);
            if (tmp == NULL){
                printf("Not found !\n");
            } else {
                printf("\nFound !! Password is --->  %s\n", tmp);
            }
            printf("\nPour quitter, entrez 'exit'.\n");
            scanf("%s", &search);

        }
        hash_table_destroy(table);
    };

}
