//
// Created by liyi on 2020/5/21.
//
#include "../lib/tlpi_hdr.h"
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        usageErr("%s sleeptime ...", argv[0]);
    }

    int numDead = 0;
    setbuf(stdout, NULL);
    for (int j = 1;j < argc; ++j)
    {
        switch (fork())
        {
            case 0:
                printf("child %d\n", j);
                sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
                _exit(EXIT_SUCCESS);
            case -1:
                errExit("fork");
            default:
                break;
        }
    }
    pid_t cpid;

    for (;;)
    {
        cpid = wait(NULL);
        if (cpid == -1){
            if (errno == ECHILD)
            {
                printf("no more child\n");
            } else{
                errExit("wait");
            }
            break;
        }
        else{
            numDead++;
            printf("wait() return child pid : %ld", (long)cpid);
        }
    }
}

