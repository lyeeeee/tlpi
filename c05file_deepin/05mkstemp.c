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

int main(int argc, char* argv[])
{
    char template[] = "/tmp/somestringXXXXXX";
    int fd = mkstemp(template);
    if (fd == -1)
    {
        errExit("mkstemp");
    }

    printf("generate filename: %s\n", template);

    unlink(template);

    if (close(fd) == -1)
    {
        errExit("close");
    }
}
