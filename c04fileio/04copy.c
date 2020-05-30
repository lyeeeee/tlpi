//
// Created by liyi on 2020/5/29.
//
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <../lib/tlpi_hdr.h>
#include <ctype.h>
#include <unistd.h>

#define BUFF_SIZE 1024
int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        usageErr("%s oldfile newfile", argv[0]);
    }

    int ifd, ofd;
    size_t len;
    ifd = open(argv[1], O_RDONLY);
    ofd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH | S_IRGRP | S_IWGRP);
    if (ifd == -1)
    {
        errExit("open");
    }
    char buff[BUFF_SIZE];
    while ((len = read(ifd, buff, BUFF_SIZE)) > 0)
    {
        if (write(ofd, buff, len) != len)
        {
            errExit("write");
        }
    }

    if (len == -1)
    {
        errExit("read");
    }

    if (close(ifd) == -1)
    {
        errExit("close");
    }
    if (close(ofd) == -1)
    {
        errExit("close");
    }
    exit(EXIT_SUCCESS);
}
