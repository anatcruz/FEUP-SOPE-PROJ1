#include "logRegister.h"

char *logfile;
int fd;
clock_t start;

double getInstant(clock_t current){
    return (current - start)/(CLOCKS_PER_SEC /(double)1000);
}

void initLog(){
    start = clock();

    logfile = getenv("LOG_FILENAME");
    if (logfile==NULL){
        logfile = "log.txt";
        setenv(logfile, "LOG_FILENAME", 1);
    }

    fd=open(logfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1){
        perror("Error openning log file");
        exit(1);
    }
}

void writeLog(double instant, char *action, char *info){
    char temp[256];
    char pid[256];
    sprintf(temp,"%.2f - ",instant);
    sprintf(pid, "%d - ", getpid());
    strcat(temp, pid);
    strcat(temp, action);
    strcat(temp, " - ");
    strcat(temp, info);
    strcat(temp, "\0");

    write(fd, temp, sizeof(temp));
}

void logArgs(int argc, char *argv[]){
    clock_t current = clock();
    char temp[256] = "";

    for(int i=1;i<argc;i++){
        strcat(temp, argv[i]);
        if(i!=argc-1){
            strcat(temp, " ");
        }
    }

    writeLog(getInstant(current), "CREATE", temp);
}