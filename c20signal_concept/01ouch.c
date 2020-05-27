//
// Created by liyi on 2020/5/19.
//
#include <signal.h>
#include <stdio.h>

static void signalHandler(int sig)
{
    printf("ouch\n");
}
int main()
{
    if (signal(SIGINT, signalHandler) == SIG_ERR)
    {
        errExit("signal");
    }

    for (int j = 0;; j++)
    {
        printf("%d\n", j);
        sleep(3);
    }
}
