#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

//Gets elapsed time in ms from start
double getInstant();

//Gets start time and Sets and Opens log file
void initLog();

//Writes to log file with format <instant –pid –action –info>
void writeLog(double instant, char *action, char *info);

void logArgs(int argc, char *argv[]);
void logExit(int status);
void logEntry(char *path, long int size);