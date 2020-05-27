//
// Created by liyi on 2020/5/19.
//
#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include <stdlib.h>
#include <string.h>

void* thead_func(void* arg)
{
    printf("other thread call strerror\n");
    char* error = strerror(EPERM);
    printf("other thread, address: (%p), content:%s\n", error, error);
}
int main()
{
    pthread_t pthread;
    int s = 0;

    printf("main thread\n");

    s = pthread_create(&pthread, NULL, thead_func, NULL);
    if (s != 0)
    {
        errExitEN(s, "pthread_create");
    }

    s = pthread_join(pthread, NULL);
    if (s != 0)
    {
        errExitEN(s, "pthread_join");
    }
    char* error = strerror(EPERM);
    printf("main thread, address: (%p), content:%s\n", error, error);
}
