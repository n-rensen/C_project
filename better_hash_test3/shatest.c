#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sha256b.c"

int main(int argc, char**argv){

    unsigned char *data = "123jesuisleRoi";
    char *sha256 = SHA256(data);

    printf(sha256);
}