#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2], result, fd2[2];

    size_t size, size2;
    char resstring[14], aboba[5];

    if (pipe(fd) < 0 || pipe(fd2) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    result = fork();

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {

        /* Parent process */

        if (close(fd[0]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n");
            exit(-1);
        }

        size = write(fd[1], "Hello, world!", 14);

        if (size != 14) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }

        if (close(fd[1]) < 0) {
            printf("parent: Can\'t close writing side of pipe\n");
            exit(-1);
        }

        size2 = read(fd2[0], aboba, 5);

        if (size2 != 5) {
            printf("Can\'t read all string from pipe\n");
            exit(-1);
        }

        printf("Parent exit, got string:%s\n", aboba);
        if (close(fd2[0]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n");
            exit(-1);
        }

    } else {

        /* Child process */

        if (close(fd[1]) < 0) {
            printf("child: Can\'t close writing side of pipe\n");
            exit(-1);
        }

        size = read(fd[0], resstring, 14);

        if (size < 0) {
            printf("Can\'t read string from pipe\n");
            exit(-1);
        }

        size2 = write(fd2[1], "aboba", 5);

        if (size2 != 5) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }

        if (close(fd2[1]) < 0) {
            printf("child: Can\'t close writing side of pipe\n");
            exit(-1);
        }

        printf("Child exit, got string:%s\n", resstring);

        if (close(fd[0]) < 0) {
            printf("child: Can\'t close reading side of pipe\n");
            exit(-1);
        }
    }

    return 0;
}
