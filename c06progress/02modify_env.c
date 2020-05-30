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
    int j;
    char** ep;

    clearenv();

    for (j = 1;j < argc; ++j)
    {
        if (putenv(argv[j]) != 0)
        {
            errExit("putenv");
        }
    }

    unsetenv("BYE");

    for (ep = environ; *ep != NULL; ++ep)
    {
        puts(*ep);
    }
    exit(EXIT_SUCCESS);
}