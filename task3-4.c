#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

// Адрес исполняемой программы должен являться вторым аргументом в argv.

int main(int argc, char **argv) {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        printf("this is child process with pid = %d and ppid = %d\n", (int) getpid(), (int) getppid());
        printf("running program from path: %s\n", argv[1]);
        execv(argv[1], argv);
        printf("ERROR");
        return 1;
    } else {
        printf("this is parent process with pid = %d ans ppid = %d\n", (int) getpid(), (int) getppid());
    }

    return 0;
}
