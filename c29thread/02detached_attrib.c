//
// Created by liyi on 2020/5/18.
//
#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"

static void*
thread_func(void* arg)
{
    printf("11111111%d\n", (int) arg);
}
int
main()
{
    pthread_t t1;
    pthread_attr_t attr;

    int s = pthread_attr_init(&attr);
    if (s != 0)
    {
        errExitEN(s, "pthread_attr_init");
    }

    s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (s != 0)
    {
        errExitEN(s, "pthread_attr_setdetachstate");
    }

    s = pthread_create(&t1, &attr, thread_func, (void*)1);
    if (s != 0)
    {
        errExitEN(s, "pthread_create");
    }

    s = pthread_attr_destroy(&attr);
    if (s != 0)
    {
        errExitEN(s, "pthread_attr_destroy");
    }
    int sum = 0;
    for (int i = 0;i < 10000000; ++i)
    {
        sum += (sum + 10)%4;
    }
    printf("main end\n");
}
