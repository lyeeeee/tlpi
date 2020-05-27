//
// Created by liyi on 2020/5/19.
//
#include <signal.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"

static void signal_handler(int arg)
{
    if (arg == SIGINT)
    {
        printf("sigint\n");
    }
    printf("sigqit\n");
}
int main()
{
    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        errExit("signal");
    }
    if (signal(SIGQUIT, signal_handler) == SIG_ERR)
    {
        errExit("signal");
    }
    for (;;)
    {
        sleep(1);
    }
}
