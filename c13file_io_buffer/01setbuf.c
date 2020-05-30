//
// Created by liyi on 2020/5/30.
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

#define BUFF_SIZE 1024
static char buff[BUFF_SIZE];
int main(int argc, char* argv[])
{
    setvbuf(stdout, buff, _IOFBF, BUFF_SIZE);

}