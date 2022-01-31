#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        printf("this is child process with pid = %d and ppid = %d\n", (int) getpid(), (int) getppid());
    } else {
        printf("this is parent process with pid = %d ans ppid = %d\n", (int) getpid(), (int) getppid());
    }

    return 0;
}
