//
// Created by liyi on 2020/5/29.
//
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <>

int main(int argc, char* argv[])
{
    int fd = dup(STDIN_FILENO);
    printf("%d\n", fd);

    int fd2 = dup2(STDIN_FILENO, fd);

    printf("%d\n", fd2);

    int fd3 = dup3(STDIN_FILENO, fd2, O_CLOEXEC);

    printf("%d\n", fd3);

    close(fd3);

}

