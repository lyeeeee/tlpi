//
// Created by liyi on 2020/5/18.
//
#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include <stdlib.h>


enum tstate{
    TS_ALIVE,
    TS_TERMINATED,
    TS_JOINED
};
static struct thread_state{
    pthread_t t;
    enum tstate state;
    int sleepTime;
};

static struct thread_state* ts = NULL;
static int unJoined = 0;
static int numAlive = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t hasDied = PTHREAD_COND_INITIALIZER;

void*
thread_func(void* arg)
{
    printf("%d\n", (int)arg);
    int idx = (int)arg;
    sleep(ts[idx].sleepTime);
    printf("Thread %d terminated\n", idx);
    int s = pthread_mutex_lock(&mutex);
    if (s != 0)
    {
        errExitEN(s, "pthread_mutex_lock");
    }
    ts[idx].state = TS_TERMINATED;
    unJoined++;
    s = pthread_cond_signal(&hasDied);
    if (s != 0)
    {
        errExitEN(s, "pthread_cond_signal");
    }
    s = pthread_mutex_unlock(&mutex);
    if (s != 0)
    {
        errExitEN(s, "pthread_mutex_unlock");
    }
}
int
main()
{
    int totalThread = 10;
    ts = malloc(sizeof(struct thread_state) * 10);
    numAlive = totalThread;
    for (int i = 0;i < 10; ++i)
    {
        ts[i].sleepTime = rand()%10;
        ts[i].state = TS_ALIVE;
        int s = pthread_create(&(ts[i].t), NULL, thread_func, (void*)i);
        if (s != 0)
        {
            errExitEN(s, "pthread_create");
        }
    }

    while (numAlive > 0)
    {
        int s = pthread_mutex_lock(&mutex);
        if (s != 0)
        {
            errExitEN(s, "pthread_mutex_lock");
        }

        while (unJoined == 0)
        {
            s = pthread_cond_wait(&hasDied, &mutex);
        }

        for (int j = 0;j < 10; ++j)
        {
            if (ts[j].state == TS_TERMINATED)
            {
                s = pthread_join(ts[j].t, NULL);
                if (s != 0)
                {
                    errExitEN(s, "pthread_join");
                }
                ts[j].state = TS_JOINED;
                unJoined--;
                numAlive--;
                printf("joined thread %d\n", j);
            }
        }
        s = pthread_mutex_unlock(&mutex);
        if (s != 0)
        {
            errExitEN(s, "pthread_mutex_unlock");
        }
    }
    free(ts);

    exit(EXIT_SUCCESS);
}
