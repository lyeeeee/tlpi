//
// Created by liyi on 2020/5/21.
//
#include "../lib/tlpi_hdr.h"
#include <stdio.h>
static void atexitFunc1(void)
{
    printf("atexitFunc1\n");
}
static void atexitFunc2(void)
{
    printf("atexitFunc2\n");
}

static void onexitFunc(int exitStatus, void* arg)
{
    printf("onexitFunc, exitStatus: %d, arg:%d\n", exitStatus, (long)arg);
}
int main()
{
    if (atexit(atexitFunc1) != 0)
    {
        fatal("atexitFunc1");
    }
    if (atexit(atexitFunc2) != 0)
    {
        fatal("atexitFunc2");
    }
    if (on_exit(onexitFunc, (void*)10) != 0)
    {
        fatal("on_exit");
    }
}
