//
// Created by liyi on 2020/5/21.
//
#include "../lib/tlpi_hdr.h"
#include <stdio.h>

static int istatic = 111;
int main()
{
    int istack = 123;

    pid_t pid;
    pid = fork();

    if (pid == -1)
    {
        errExit("fork");
    }
    else if (pid == 0)
    {
        printf("%d   %d\n", istack, istatic);
    }
    else
    {
        istack++;
        istatic++;
        sleep(3);
        printf("%d   %d\n", istack, istatic);
    }
    exit(EXIT_SUCCESS);
}
