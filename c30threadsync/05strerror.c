//
// Created by liyi on 2020/5/19.
//
#include <pthread.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE
#define MAX_ERROR_LEN 256

static char buff[MAX_ERROR_LEN];

char*
strerror(int err)
{
    if (err < 0 || err >= MAX_ERROR_LEN)
    {
        snprintf(buff, MAX_ERROR_LEN, "UnKnown error %d", err);
    }
    else
    {
        strcpy(buff, _sys_errlist[err], MAX_ERROR_LEN - 1);
        buff[MAX_ERROR_LEN-1] = '\0';
    }
    return buff;
}
