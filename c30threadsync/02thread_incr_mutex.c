//
// Created by liyi on 2020/5/18.
//
#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"

static long total = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static
void* thread_func(void* arg)
{
    int loop = *((int*)((void*)arg));
    for (int i = 0;i < loop; ++i)
    {
        int s = pthread_mutex_lock(&mutex);
        if (s != 0)
        {
            errExitEN(s, "pthread_mutex_lock");
        }
        total += 1;
        s = pthread_mutex_unlock(&mutex);
        if (s != 0)
        {
            errExitEN(s, "pthread_mutex_unlock");
        }
    }
}
int
main()
{
    pthread_t t1, t2;

    int loops = 1000000000;


    int s = pthread_create(&t1, NULL, thread_func, (void*)(&loops));
    if (s != 0)
    {
        errExitEN(s, "pthread_create");
    }
    s = pthread_create(&t2, NULL, thread_func, (void*)(&loops));
    if (s != 0)
    {
        errExitEN(s, "pthread_create");
    }

    s = pthread_join(t1, NULL);
    if (s != 0)
    {
        errExitEN(s, "pthread_join");
    }
    s = pthread_join(t2, NULL);
    if (s != 0)
    {
        errExitEN(s, "pthread_join");
    }

    printf("%ld\n", total);
}
