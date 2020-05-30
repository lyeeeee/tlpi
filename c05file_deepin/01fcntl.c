//
// Created by liyi on 2020/5/29.
//
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char* argv[])
{
    int fd = open(argv[1], O_RDWR);
    if (fd == -1)
    {
        errExit("open");
    }

    int flags, accessMode;

    flags = fcntl(fd, F_GETFL);
    if (flags == -1)
    {
        errExit("fcntl");
    }

    if (flags & O_SYNC)
    {
        printf("writes are sync\n");
    }

    accessMode = flags & O_ACCMODE;
    if (accessMode == O_WRONLY || accessMode == O_RDWR)
    {
        printf("file is writable\n");
    }

    flags |= O_APPEND;
    if (fcntl(fd, F_SETFL, flags) == -1)
    {
        errExit("fcntl");
    }
}
