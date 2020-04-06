#include "simpledu.h"

int main(int argc, char *argv[], char *envp[]){
    Args args;

    initLog();
    init_args(&args);

    if (get_args(&args, argc, argv)!=0){
        printf("Error getting args!\n");
        logExit(1);
    }
    logArgs(argc, argv);

    if (list_info(&args)!=0){
        printf("Error reading directory\n");
        logExit(1);
    }

    logExit(0);
}

int list_info(Args *args) {
    DIR *dir;
    struct dirent *direntp;
    struct stat stat_buf;

    if ((dir = opendir(args->path)) == NULL){
        perror(args->path);  
        return -1;
    }

    while ((direntp = readdir(dir)) != NULL) {
        char path[256];
        strcpy(path, args->path);
        strcat(path, direntp->d_name);

        if (args->dereference)
            stat(path, &stat_buf);
        else
            lstat(path, &stat_buf);
        

        //Regular Files
        if (S_ISREG(stat_buf.st_mode) && args->all){
            if (args->bytes){
                printf("%ld\t%s\n",stat_buf.st_size, path);
            }
            else {
                int blocks = stat_buf.st_blocks*512/args->blockSize;
                if ((stat_buf.st_blocks*512)%args->blockSize !=0)
                    blocks+=1;

                printf("%d\t%s\n",blocks, path);
            }
        }
        //Directories
        /*else {
            ...
        }*/
    }

    return 0;
}
