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
struct stat
{
    int x;
};
int main(int argc, char* argv[])
{
    struct iovec iov[3];
    int x;
    struct stat myStruct;
#define STR_SIZE 100;
    char str[STR_SIZE];

    if (argc != 2)
    {
        usageErr("%s file\n", argv[0]);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        errExit("open");
    }

    size_t totalRequired = 0;
    iov[0].iov_base = &myStruct;
    iov[0].iov_len = sizeof(struct stat);
    totalRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(int);
    totalRequired += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    totalRequired += iov[2].iov_len;

    int numRead = readv(fd, iov, 3);
    if (numRead == -1)
    {
        errExit("readv");
    }

    if (numRead != totalRequired)
    {
        printf("read fewer bytes than requests\n");
    }

    printf("total bytes request: %ld, bytes read: %ld\n", totalRequired, numRead);
    exit(EXIT_SUCCESS);
}
