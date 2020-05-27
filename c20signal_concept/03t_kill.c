//
// Created by liyi on 2020/5/20.
//
#include <signal.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        usageErr("%s sig-num pid\n", argv[0]);
    }

    int sig = getInt(argv[1], 0, "sig-num");

    pid_t pid = getLong(argv[2], 0, "pid");

    int s = kill(pid, sig);
    if (sig != 0)
    {
        if (s == -1)
        {
            errExit("kill");
        }
    }
    else
    {
        if (s == 0)
        {
            printf("process exist and we can send a signal to it\n");
        }
        else if (errno == EPERM)
        {
            printf("process exist and we can not  send a signal to it\n")
        }
        else if (errno == ESRCH)
        {
            printf("process do not exist\n")
        } else{
            errExit("kill");
        }
    }
}
