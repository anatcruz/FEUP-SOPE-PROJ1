#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <math.h>

#include "args.h"
#include "logRegister.h"

int list_info(Args args);
int get_size(struct stat stat_buf, Args args);