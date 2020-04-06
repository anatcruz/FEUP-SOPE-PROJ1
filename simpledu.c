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
        
        int fileSize;
        //Files
        if ((S_ISREG(stat_buf.st_mode) || S_ISLNK(stat_buf.st_mode)) && args->all){
            if (args->bytes){
                fileSize = stat_buf.st_size;
            }
            else {//get fileSize in blocks
                fileSize = stat_buf.st_blocks*512/args->blockSize;
                if ((stat_buf.st_blocks*512)%args->blockSize !=0)
                    fileSize+=1;
            }

            printf("%d\t%s\n", fileSize, path);
            logEntry(path, fileSize);
        }
        //Directories - NEEDS CHECKING!
        else if(S_ISDIR(stat_buf.st_mode)){
            pid_t pid = fork();

            if(pid < 0){ //Erro
                printf("ERROR!");
                logExit(1);
            }
            else if(pid < 0){ //Parent
                wait(NULL);
            } 
            else{ //Child
                strcpy(args->path, path);
                strcat(args->path, direntp->d_name);
                list_info(&args);
                args->maxDepth--;
                logExit(0);
            }
        }
    }

    return 0;
}
