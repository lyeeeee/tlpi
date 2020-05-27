#include "../lib/tlpi_hdr.h"
#include <string.h>
#include <fcntl.h>

#ifndef BUFF_SIZE
#define BUFF_SIZE 1024
#endif

int main(int argc, char* argv[]) {
    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        usageErr("%s old-file new-file\n", argv[0]);
    }
    int inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1) {
        errExit("open file %s", argv[1]);
    }

    int openFalgs = O_TRUNC | O_CREAT | O_WRONLY;
    //mode_t mode = S_IRUSR | S_IWUSR |
}