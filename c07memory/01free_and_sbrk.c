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

#define MAX_ALLOCS 1000000

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        usageErr("%s num-allocs blocksize [step [min [max]]]", argv[0]);
    }

    char* ptr[MAX_ALLOCS];

    int numAllocs = getInt(argv[1], GN_ANY_BASE, "num-callocs");
    int blocksize = getInt(argv[2], GN_ANY_BASE, "blocksize");
    int step = argc > 3 ? getInt(argv[3], GN_ANY_BASE, "step") : 1;
    int min = argc > 4 ? getInt(argv[4], GN_ANY_BASE, "min") : 1;
    int max = argc > 5 ? getInt(argv[5], GN_ANY_BASE, "max") : numAllocs;

    if (max > numAllocs)
        cmdLineErr("free max > numALlocs\n");

    printf("initial program break %10p\n", sbrk(0));
    for (int i = 0;i < numAllocs; ++i)
    {
        ptr[i] = malloc(blocksize);
        if (ptr[i] == NULL)
        {
            errExit("malloc");
        }
    }

    printf("allocate %d*%d bytes\n", numAllocs, blocksize);
    printf("after malloc program break %10p\n", sbrk(0));
    for (int i = min-1;i < max; ++i)
    {
        free(ptr[i]);
    }
    printf("after free program break %10p\n", sbrk(0));

    exit(EXIT_SUCCESS);


}
