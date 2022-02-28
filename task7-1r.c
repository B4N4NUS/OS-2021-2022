#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    char *array;
    int shmid;
    char pathname[] = "task7-1w.c";
    key_t key;
    char buffer[10000];

    if ((key = ftok(pathname, 1)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, 10000 * sizeof(char), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        if (errno != EEXIST) {
            printf("Can\'t create shared memory\n");
            exit(-1);
        } else {
            if ((shmid = shmget(key, 10000 * sizeof(char), 0)) < 0) {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
        }
    }

    if ((array = (char *) shmat(shmid, NULL, 0)) == (char *) (-1)) {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    printf("Successfully got source code for task7-1w.c via shared memory:\n");
    for (int i = 0; i < 10000; i++) {
        putchar(array[i]);
    }

    if (shmdt(array) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) != -1) {
        printf("\nSuccessfully cleaned shared memory");
    } else {
        printf("\nCan\'t free shared memory. Error number = %d", errno);
    }
    return 0;
}
