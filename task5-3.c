#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2];
    char chr = 'o';

    if (pipe(fd) != 0) {
        printf("Can't open pipe\n");
        exit(-1);
    }

    printf("Max equals last printed number of bytes\n");

    for (int i = 0;; i++) {
        fprintf(stdout, "%d bytes written successfully\n", i + 1);
        if (write(fd[1], &chr, 1) != 1) {
            printf("Error");
            exit(-1);
        }
    }
    return 0;
}