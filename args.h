#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Arguments {
    unsigned int all; //-a, -all
    unsigned int bytes; //-b, --bytes
    unsigned int blockSize; //-B, --block-size=SIZE ; default SIZE=1024
    unsigned int countLinks; //-l, --count-links
    unsigned int dereference; //-L, --dereference
    unsigned int separateDirs; //-S, --separate-dirs
    long int maxDepth; //--max-depth=N ; N(0,1,...)
    char path[256]; //Dir path
}Args;

void init_args(Args *args);
int get_args(Args *args, int argc, char *argv[]);
void print_args(Args *args);
