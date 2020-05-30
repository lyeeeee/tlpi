//
// Created by liyi on 2020/5/29.
//
#include "../lib/tlpi_hdr.h"
#include <stdio.h>
#include <unistd.h>

#define BUFF 10
int main()
{
    char arr[BUFF+1];
    size_t size;
    if ((size = read(STDIN_FILENO, arr, BUFF)) == -1)
    {
        errExit("read");
    }
    arr[size] = '\0';
    printf("buff content: %s\n", arr);
}
