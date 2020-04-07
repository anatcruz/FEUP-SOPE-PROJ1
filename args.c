#include "args.h"

void init_args(Args *args){
    args->all = 0;
    args->bytes = 0;
    args->blockSize = 1024; //default value
    args->countLinks = 0;
    args->dereference = 0;
    args->separateDirs = 0;
    args->maxDepth = __INT64_MAX__; //default value to search all
    args->path[0]=0;
}

int get_args(Args *args, int argc, char *argv[]){

    char *token;

    if(argc < 2 || argc > 10){
        printf("Usage: %s -l [path] [-a] [-b] [-B size] [-L] [-S] [--max-depth=N]\n", argv[0]);
        return -1;
    }

    for (int i = 1; i < argc; i++){
        if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--count-links")){
            if (args->countLinks) return -1;
            args->countLinks = 1;
        }
        else if (!strcmp(argv[i], "-a") || !strcmp(argv[i], "--all")){
            if (args->all) return -1;
            args->all = 1;
        }
        else if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--bytes")){
            if (args->bytes) return -1;
            args->bytes = 1;
        }
        else if (!strcmp(argv[i], "-B")){
            if (args->blockSize != 1024) return -1;
            if (atoi(argv[i+1])){
                args->blockSize = atoi(argv[i+1]);
                i++;
            }
            else{
                return -1; //The next argument is not a number
            } 
        }
        else if (!strcmp(token = strtok(argv[i], "="), "--block-size") ) {
            if (args->blockSize != 1024) return -1;
            token = strtok(NULL, "=");
            if (atoi(token)){
                args->blockSize = atoi(token);
            }
            else{
                return -1; //SIZE is not a number
            }
        }
        else if (!strcmp(argv[i], "-L") || !strcmp(argv[i], "--dereference")){
            if (args->dereference) return -1;
            args->dereference = 1;
        }
        else if (!strcmp(argv[i], "-S") || !strcmp(argv[i], "--separate-dirs")){
            if (args->separateDirs) return -1;
            args->separateDirs = 1;
        }
        else if (!strcmp(argv[i], "--max-depth") ) {
            if (args->maxDepth!=__INT64_MAX__) return -1;
            token = strtok(NULL, "=");
            if(!strcmp(token,"0")){
                args->maxDepth = 0;
            }
            else{
                int num = atoi(token);
                if (num>0){
                    args->maxDepth = atoi(token);
                }
                else {
                    return -1; //N is not a number or is not valid
                }
            }
        }
        else if (argv[i][1] != '-'){
            if (strlen(args->path)!=0) return -1;
            strncpy(args->path, argv[i], sizeof(args->path));
        }
    }

    //print_args(args);

    return 0;
}

//Testing function
void print_args(Args *args) {
    printf("->all: %u\n", args->all);
    printf("->bytes: %u\n", args->bytes);
    printf("->blockSize: %u\n", args->blockSize);
    printf("->countLinks: %u\n", args->countLinks);
    printf("->dereference: %u\n", args->dereference);
    printf("->separateDirs: %u\n", args->separateDirs);
    printf("->maxDepth: %ld\n", args->maxDepth);
    printf("->path: %s\n", args->path);
}