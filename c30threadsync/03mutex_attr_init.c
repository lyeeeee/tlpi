//
// Created by liyi on 2020/5/18.
//
#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"

int
main()
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t attr;

    int s, type;

    s = pthread_mutexattr_init(&attr);
    if (s != 0)
    {
        errExitEN(s, "pthread_mutexattr_init");
    }

    s = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_DEFAULT);
    if (s != 0)
    {
        errExitEN(s, "pthread_mutexattr_settype");
    }

    s = pthread_mutex_init(&mutex, &attr);
    if (s != 0)
    {
        errExitEN(s, "pthread_mutex_init");
    }

    s = pthread_mutexattr_destroy(&attr);
    if (s != 0)
    {
        errExitEN(s, "pthread_mutexattr_destroy");
    }

    s = pthread_mutex_destroy(&mutex);
    if (s != 0)
    {
        errExitEN(s, "pthread_mutex_destroy");
    }
}
