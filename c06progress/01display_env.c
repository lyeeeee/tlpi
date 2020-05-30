//
// Created by liyi on 2020/5/29.
//

#include <fcntl.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>
#include <stdlib.h>

extern char** environ;
int main(int argc, char* argv[])
{
    for (char** p = environ; *p != NULL; ++p)
    {
        printf("%s\n", *p);
    }
}