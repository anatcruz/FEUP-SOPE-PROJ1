#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

#include "args.h"

int main(int argc, char *argv[], char *envp[]){
    get_args(argc, argv);
    return 0;
}
