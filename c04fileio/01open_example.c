//
// Created by liyi on 2020/5/27.
//
#include "../lib/tlpi_hdr.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    int fd = open("startup", O_RDONLY);
    if (fd == -1)
    {
        errExit("open");
    }

    fd = open("myfile", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        errExit("open");
    }

    fd = open("w.log", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        errExit("open");
    }
}
