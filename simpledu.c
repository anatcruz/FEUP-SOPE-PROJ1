#include "simpledu.h"

int main(int argc, char *argv[], char *envp[]){
    Args args;

    init_args(&args);
    if (get_args(&args, argc, argv)!=0){
        printf("Error getting args!\n");
        exit(1);
    }

    return 0;
}
