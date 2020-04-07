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
    
    if (list_info(args)<0){
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
        logExit(1);
    }

    char origpath[256]; //DU prints without '/' in the end of the path if it wasn't given, saving path to print dir later
    strcpy(origpath, args.path);

    if (args.path[strlen(args.path) - 1] != '/')
        strcat(args.path, "/");

    while ((direntp = readdir(dir)) != NULL) {
        char path[256];
        strcpy(path, args.path);
        strcat(path, direntp->d_name);

        if(!strcmp(direntp->d_name,"..")) continue;
        else if (!strcmp(direntp->d_name,".")){
            stat(path, &stat_buf);

            dirSize+=get_size(stat_buf, args);
            continue;
        }

        if (args.dereference)
            stat(path, &stat_buf);
        else
            lstat(path, &stat_buf);
        
        //Files
        if (S_ISREG(stat_buf.st_mode) || S_ISLNK(stat_buf.st_mode)){
            int fileSize = get_size(stat_buf, args);
            dirSize+=fileSize;
            logEntry(path, fileSize);
            if(args.all && args.maxDepth>0)
                printf("%d\t%s\n", fileSize, path);
        }
        //Directories
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
                wait(NULL);

                if(!args.separateDirs){
                    close(pp[1]);
                    int size;
                    read(pp[0], &size, sizeof(int));
                    dirSize+=size;
                }
            }
            else{ //Child
                strcpy(args.path, path);
                strcat(args.path, "/");
                if(args.maxDepth!=__INT64_MAX__)
                    args.maxDepth--;
                int size = list_info(args);

                if(!args.separateDirs){
                    close(pp[0]);
                    write(pp[1], &size, sizeof(int));
                }

                logExit(0);
            }
        }
    }

    if(args.maxDepth>=0){
        printf("%d\t%s\n", dirSize, origpath);
    }

    return dirSize;
}

int get_size(struct stat stat_buf, Args args){
    int size;
    if (args.bytes){
        size = stat_buf.st_size;
    }
    else {//get Size in blocks
        size = stat_buf.st_blocks*512/args.blockSize;
        if ((stat_buf.st_blocks*512)%args.blockSize !=0)
            size+=1;
    }
    return size;
}
