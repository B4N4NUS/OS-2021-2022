#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main() {
    char pathname[] = "task9-3.c";
    key_t key;
    struct sembuf buffer;
    int fd[2], result, id, n;
    char message[16];
    size_t size;

    printf("(Parent):input N value -> ");

    scanf("%d", &n);

    if (n < 2) {
        printf("(Parent):wrong N value");
        exit(-1);
    }

    if (pipe(fd) < 0) {
        printf("(Parent):can\'t open pipe\n");
        exit(-1);
    }

    if ((key = ftok(pathname, 0)) < 0) {
        printf("(Parent):can\'t generate key\n");
        exit(-1);
    }

    if ((id = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
        printf("(Parent):can\'t get semaphore set\n");
        exit(-1);
    }

    result = fork();
    if (result < 0) {
        printf("(Parent):can\'t fork child\n");
        exit(-1);
    }

    for (int i = 0; i < n; ++i) {
        if (result > 0) {
            size = write(fd[1], "|Greetings,  Child|", 20);
            if (size != 20) {
                printf("(Parent):can\'t write all string to pipe\n");
                exit(-1);
            }

            buffer.sem_op = 2;
            buffer.sem_num = 0;
            buffer.sem_flg = 0;
            if (semop(id, &buffer, 1) < 0) {
                printf("(Parent):can\'t wait for condition\n");
                exit(-1);
            }

            buffer.sem_op = 0;
            if (semop(id, &buffer, 1) < 0) {
                printf("(Parent):can\'t wait for condition\n");
                exit(-1);
            }

            size = read(fd[0], message, 20);
            if (size != 20) {
                printf("(Parent):can\'t read from pipe\n");
                exit(-1);
            }

            printf("(Parent):[%d] read from pipe: %s\n", i, message);
        } else {
            buffer.sem_op = -1;
            buffer.sem_num = 0;
            buffer.sem_flg = 0;
            if (semop(id, &buffer, 1) < 0) {
                printf("(Child):can\'t wait for condition\n");
                exit(-1);
            }

            size = read(fd[0], message, 20);
            if (size != 20) {
                printf("(Child):can\'t read from pipe\n");
                exit(-1);
            }

            printf("(Child): [%d] read from pipe: %s\n", i, message);

            size = write(fd[1], "|Greetings, Parent|", 20);
            if (size != 20) {
                printf("(Child):can\'t write all string to pipe\n");
                exit(-1);
            }

            if (semop(id, &buffer, 1) < 0) {
                printf("(Parent):can\'t wait for condition\n");
                exit(-1);
            }
        }
    }

    if (close(fd[0]) < 0) {
        if (result > 0) {
            printf("(Parent):can\'t close reading side of pipe\n");
        } else {
            printf("(Child): can\'t close reading side of pipe\n");
        }
        exit(-1);
    }

    if (close(fd[1]) < 0) {
        if (result > 0) {
            printf("(Parent):can\'t close writing side of pipe\n");
        } else {
            printf("(Child): can\'t close reading side of pipe\n");
        }
        exit(-1);
    }
    return 0;
}
