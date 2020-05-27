//
// Created by liyi on 2020/5/21.
//
#include "../lib/tlpi_hdr.h"
#include <stdio.h>
#include <unistd.h>

int main()
{
    int istack = 111;

    switch (vfork())
    {
        case -1:
            errExit("vfork");
        case 0:
            sleep(3);
            istack++;
            write(STDOUT_FILENO, "child\n", 6);
            _exit(EXIT_SUCCESS);
        default:
            write(STDOUT_FILENO, "parent\n", 7);
            printf("%d\n", istack);
            exit(EXIT_SUCCESS);

    }
}
