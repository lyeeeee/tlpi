//
// Created by liyi on 2020/5/29.
//
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"
#include <ctype.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        usageErr("%s file {r<length> | R<length> | w<string> | s<offset>}...\n");
    }

    int fd = open(argv[1], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR |S_IRGRP | S_IWGRP | S_IROTH |S_IWOTH);
    if (fd == -1)
    {
        errExit("open");
    }
    size_t offset;
    size_t len;
    for (int i = 2;i < argc; ++i)
    {
        switch (argv[i][0])
        {
            case 'r':
            case 'R':

                len = getLong(argv[i]+1, GN_ANY_BASE, argv[i]);
                char* buff = malloc(len);
                if (buff == NULL)
                    errExit("malloc");
                if (read(fd, buff, len) == -1)
                {
                    errExit("read");
                }
                for (int j = 0;j < len; ++j)
                {
                    if (argv[i][0] == 'r')
                    {
                        printf("%c", isprint((unsigned char)buff[j]) ? buff[j] : '?');
                    }
                    else
                    {
                        printf("%X", isprint((unsigned char)buff[j]) ? buff[j] : '?');
                    }
                }
                printf("\n");
                free(buff);
                break;
            case 's':

                offset = getLong(argv[i]+1, GN_ANY_BASE, argv[i]);
                if (lseek(fd, offset, SEEK_SET) == -1)
                {
                    errExit("lseek");
                }
                printf("%s: seek succeed\n", argv[i]);
                break;
            case 'w':
                if ((len = write(fd, argv[i]+1, strlen(argv[i]+1))) == -1)
                {
                    errExit("write");
                }
                printf("%s: write %ld bytes\n",argv[i], len);
                break;
            default:
                cmdLineErr("argument invalid\n");
        }
    }
}
