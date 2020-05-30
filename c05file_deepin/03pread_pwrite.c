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
int main(int argc, char* argv[])
{
    int fd = open(argv[1], O_RDWR);
    if (fd == -1)
    {
        errExit("open");
    }

    char* buff;
    if (argv[2][0] == 'r')
    {
        buff = malloc(1024);
        size_t len = pread(fd, buff, getInt(argv[3], GN_ANY_BASE, argv[3]), getInt(argv[4], GN_ANY_BASE, argv[4]));
        if (len == -1)
        {
            errExit("pread");
        }

        *(buff+len) = '\0';
        printf("%s\n", buff);
        free(buff);
    }

    if (argv[2][0] == 'w')
    {
        size_t len = pwrite(fd, argv[3], strlen(argv[3]), getInt(argv[4], GN_ANY_BASE, argv[4]));
        if (len != strlen(argv[3]))
        {
            errExit("pwrite");
        }
    }
}
