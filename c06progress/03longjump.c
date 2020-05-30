//
// Created by liyi on 2020/5/29.
//

#include <fcntl.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include <ctype.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <setjmp.h>
static jmp_buf env;

static void f2(void)
{
    longjmp(env, 2);
}

static void f1(int argc)
{
    if (argc == 1)
    {
        longjmp(env, 1);
    }
    f2();
}

int main(int argc, char* argv[])
{
    switch (setjmp(env))
    {
        case 0:
            printf("call f1\n");
            f1(argc);
            break;
        case 1:
            printf("jump from function 1\n");
            break;
        case 2:
            printf("jump from function 2\n");
            break;
    }
}