//
// Created by bananus on 29.05.22.
//

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <stdlib.h>

void my_handler(int nsig) {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) != 0) {
        if (pid >= 0) {
            if ((status & 0xff) == 0) {
                printf("[process %d] was forced to exit with [code %d]\n", pid, status >> 8);
            } else {
                if ((status & 0xff00) == 0) {
                    if (status & 0x80) {
                        printf("[process %d] was slain by [signal %d] with core file\n", pid, status & 0x7f);
                    } else {
                        printf("[process %d] was slain by [signal %d] without core file\n", pid, status & 0x7f);
                    }
                }
            }
        } else {
            if (errno == 10) {
                printf("No processes to close :(\n");
                exit(EXIT_SUCCESS);
            } else {
                printf("An error occurred on waitpid with errno %d\n", errno);
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(void) {
    pid_t pid;
    int i, j;

    (void) signal(SIGCHLD, my_handler);

    for (i = 0; i < 10; i++) {
        if ((pid = fork()) < 0) {
            printf("Can\'t fork child 1\n");
            exit(1);
        } else if (pid == 0) {
            for (j = 1; j < 10000000; j++);
            exit(200 + i);
        }
    }

    while (1);
}
