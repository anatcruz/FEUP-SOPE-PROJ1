#include "simpledu.h"
#include "logRegister.h"

int main(int argc, char *argv[], char *envp[]){
    Args args;

    initLog();
    init_args(&args);

    if (get_args(&args, argc, argv)!=0){
        printf("Error getting args!\n");
        logExit(1);
    }
    
    logArgs(argc, argv);

    return 0;
}
