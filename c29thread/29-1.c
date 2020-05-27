//
// Created by liyi on 2020/5/18.
//

#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
static void*
thread_func(void* arg)
{

}
int
main()
{
    pthread_t  t1;

    int s = pthread_create(&t1, NULL, thread_func, NULL);
    if (s != 0)
    {
        errExitEN(s, "pthread_create");
    }
    /*
     * 等待自身会死锁
     * */
    s = pthread_join(pthread_self(), NULL);
    if (s != 0)
    {
        errExitEN(s, "pthread_join");
    }

    printf("main end\n");
}