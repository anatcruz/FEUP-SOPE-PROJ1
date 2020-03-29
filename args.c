#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "args.h"

struct Args args = {0, 0, 1024, 0, 0, 0, -1};

int get_args(int argc, char *argv[]){

    char *token;

    if(argc < 3){
        printf("Usage: %s -l [path] [-a] [-b] [-B size] [-L] [-S] [--max-depth=N]\n", argv[0]);
        return -1;
    }

    for (int i = 1; i < argc; i++){
        if (!strcmp(argv[i], "-a") || !strcmp(argv[i], "--all")){
            args.all = 1;
        }
        else if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--bytes")){
            args.bytes = 1;
        }
        else if (!strcmp(argv[i], "-B")){
            if (atoi(argv[i+1])){
                args.blockSize = atoi(argv[i+1]);
                i++;
            }
            else{
                return -1; //The next argument is not a number
            } 
        }
        else if (!strcmp(token = strtok(argv[i], "="), "--block-size") ) {
            token = strtok(NULL, "=");
            if (atoi(token)){
                args.blockSize = atoi(token);
            }
            else{
                return -1; //SIZE is not a number
            }
        }
        else if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--count-links")){
            args.countLinks = 1;
        }
        else if (!strcmp(argv[i], "-L") || !strcmp(argv[i], "--dereference")){
            args.dereference = 1;
        }
        else if (!strcmp(argv[i], "-S") || !strcmp(argv[i], "--separate-dirs")){
            args.separeteDirs = 1;
        }
        else if (!strcmp(argv[i], "--max-depth") ) {
            token = strtok(NULL, "=");
            if (atoi(token)){
                args.maxDepth = atoi(token);
            }
            else {
                return -1; //N is not a number
            }
        }        
    }

    //testing
    printf(".all: %u\n", args.all);
    printf(".bytes: %u\n", args.bytes);
    printf(".blockSize: %u\n", args.blockSize);
    printf(".countLinks: %u\n", args.countLinks);
    printf(".dereference: %u\n", args.dereference);
    printf(".separateDirs: %u\n", args.separeteDirs);
    printf(".maxDepth: %d\n", args.maxDepth);

    return 0;
}