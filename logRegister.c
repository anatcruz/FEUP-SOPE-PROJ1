#include "logRegister.h"

int fd;
struct timespec start;

double getInstant(){
    struct timespec current;
    clock_gettime(CLOCK_MONOTONIC, &current);
    return ((current.tv_sec - start.tv_sec)*1e9 + (current.tv_nsec - start.tv_nsec)*1e-6);
}

void initLog(){
    clock_gettime(CLOCK_MONOTONIC, &start);
    char *logfile;

    logfile = getenv("LOG_FILENAME");
    if (logfile==NULL){
        logfile = "log.txt";
        if(setenv("LOG_FILENAME", logfile, 1)!=0){
            perror("Setenv error");
            logExit(1);
        }
    }

    fd=open(logfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1){
        perror("Error openning log file");
        logExit(1);
    }
}

void writeLog(double instant, char *action, char *info){
    char temp[256];
    sprintf(temp,"%.2f - %.8d - %s - %s\n", instant, getpid(), action, info);

    write(fd, temp, strlen(temp));
}

void logArgs(int argc, char *argv[]){
    char temp[256] = "";

    for(int i=0;i<argc;i++){
        strcat(temp, argv[i]);
        if(i!=argc-1){
            strcat(temp, " ");
        }
    }

    writeLog(getInstant(), "CREATE", temp);
}

void logExit(int status){
    char stat[2];
    sprintf(stat, "%d", status);

    writeLog(getInstant(), "EXIT", stat);
    
    close(fd);
    exit(status);
}

void logEntry(char *path, long int size){
    char temp[256];
    sprintf(temp, "%ld %s", size, path);

    writeLog(getInstant(), "ENTRY", temp);
}