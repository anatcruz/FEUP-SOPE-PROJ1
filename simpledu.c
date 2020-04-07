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
    
    if (list_info(args)==-1){
        printf("Error reading directory\n");
        logExit(1);
    }

    logExit(0);
}

int list_info(Args args) {
    DIR *dir;
    struct dirent *direntp;
    struct stat stat_buf;
    int dirSize=0;

    if ((dir = opendir(args.path)) == NULL){
        perror(args.path);  
        return -1;
    }

    while ((direntp = readdir(dir)) != NULL) {
        if(!strcmp(direntp->d_name,".") || !strcmp(direntp->d_name,".."))
            continue;

        char path[256];
        strcpy(path, args.path);
        strcat(path, direntp->d_name);

        if (args.dereference)
            stat(path, &stat_buf);
        else
            lstat(path, &stat_buf);
        
        int fileSize;
        //Files
        if (S_ISREG(stat_buf.st_mode) || S_ISLNK(stat_buf.st_mode)){
            if (args.bytes){
                fileSize = stat_buf.st_size;
            }
            else {//get fileSize in blocks
                fileSize = stat_buf.st_blocks*512/args.blockSize;
                if ((stat_buf.st_blocks*512)%args.blockSize !=0)
                    fileSize+=1;
            }
            dirSize+=fileSize;

            logEntry(path, fileSize);
            if(args.all && args.maxDepth>0)
                printf("%d\t%s\n", fileSize, path);
        }
        //Directories - NEEDS CHECKING!
        else if(S_ISDIR(stat_buf.st_mode)){
            int pp[2];
            if (pipe(pp) < 0) {
                perror("Pipe error!");
                logExit(1);
            }

            pid_t pid = fork();

            if(pid < 0){ //Erro
                printf("Fork error!");
                logExit(1);
            }
            else if(pid > 0){ //Parent
                close(pp[1]);
                wait(NULL);

                if(!args.separateDirs){
                    int size;
                    read(pp[0], &size, sizeof(int));
                    dirSize+=size;
                }
            }
            else{ //Child
                close(pp[0]);

                strcpy(args.path, path);
                strcat(args.path, "/");
                if(args.maxDepth!=__INT64_MAX__)
                    args.maxDepth--;
                int size = list_info(args);

                if(!args.separateDirs){
                    write(pp[1], &size, sizeof(int));
                }

                logExit(0);
            }
        }
    }

    if(args.maxDepth>=0){
        printf("%d\t%s\n", dirSize, args.path);
    }

    return dirSize;
}
