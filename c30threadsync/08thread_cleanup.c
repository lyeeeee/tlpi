//
// Created by liyi on 2020/5/19.
//
#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include <stdlib.h>
#include <string.h>

static int glob = 0;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static void clean_up(void* arg)
{
    printf("clean up: free block..\n");
    free(arg);
    printf("clean up: unlock mutex\n");
    int s = pthread_mutex_unlock(&mutex);
    if (s != 0)
    {
        errExitEN(s, "pthread_mutex_unlock");
    }
}
static void* thread_func(void* arg)
{
    char* buff = malloc(0x1000);
    printf("thread: alloc memeory at: %p", buff);

    int s = pthread_mutex_lock(&mutex);
    if (s != 0)
    {
        errExitEN(s, "pthread_mutex_lock");
    }

    pthread_cleanup_push(clean_up, buff);
    while (glob == 0)
    {
        s = pthread_cond_wait(&cond, &mutex);
        if (s != 0)
        {
            errExitEN(s, "pthread_cond_wait");
        }
    }
    pthread_cleanup_pop(1);
    printf("thread: condition wait complete\n");
    return NULL;
}
int main(int argc, char* argv[])
{
    pthread_t  pthread;
    int s;
    s = pthread_create(&pthread, NULL, thread_func, NULL);
    if (s != 0)
    {
        errExitEN(s, "pthread_create");
    }

    sleep(3);
    if (argc == 1)
    {
        printf("main: cancel thread\n");
        s = pthread_cancel(pthread);
        if (s != 0)
        {
            errExitEN(s, "pthread_cancel");
        }
    }
    else
    {
        printf("main: signal condition\n");
        glob = 1;
        s = pthread_cond_signal(&cond);
        if (s != 0)
        {
            errExitEN(s, "pthread_cond_signal");
        }
    }

    void* ret;
    s = pthread_join(pthread, &ret);
    if (s != 0)
    {
        errExitEN(s, "pthread_join");
    }

    if (ret == PTHREAD_CANCELED)
    {
        printf("main: thread canceled\n");
    }
    else
    {
        printf("main: thread exit normal\n");
    }
}
