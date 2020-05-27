//
// Created by liyi on 2020/5/18.
//
#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"

static void*
thread_func(void* arg)
{
    char* s = (char*) arg;
    printf("%s\n", s);
    return (void*)strlen(s);
}
int
main()
{
    pthread_t pthread;

    int s = pthread_create(&pthread, NULL, thread_func, "hello world");

    if (s != 0)
    {
        errExitEN(s, "pthread_create");
    }

    printf("message form main\n");

    void* ret;
    pthread_join(pthread, &ret);
    printf("message return from sub pthread:%s\n", (long)ret);
}

