//
// Created by liyi on 2020/5/19.
//
#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include <stdlib.h>
#include <string.h>

void* thread_func(void* arg)
{
    for (;;)
    {
        printf("hello\n");
        sleep(1);
    }
}
int main()
{
    pthread_t pthread;
    int s = 0;

    s = pthread_create(&pthread, NULL, thread_func, NULL);
    if (s != 0)
    {
        errExitEN(s, "pthread_create");
    }

    sleep(3);

    s = pthread_cancel(pthread);
    if (s != 0)
    {
        errExitEN(s, "pthread_cancel");
    }
    void* ret;
    s = pthread_join(pthread, ret);
    if (s != 0)
    {
        errExitEN(s, "pthread_join");
    }

    if (ret != NULL)
    {
        printf("thread canceled\n");
    }

    exit(EXIT_SUCCESS);
}
