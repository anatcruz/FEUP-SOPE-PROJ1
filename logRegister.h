#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

double getInstant(clock_t current);
void initLog();
void writeLog(double instant, char *action, char *info);
void logArgs(int argc, char *argv[]);