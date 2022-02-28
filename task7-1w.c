#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *array;
    char buffer[10000];
    int shmid;
    char pathname[] = "task7-1w.c";
    FILE *file;
    key_t key;

    file = fopen(pathname, "r");
    if (file == NULL) {
        printf("Cant open file task7-1w.c to get its source code");
        exit(-1);
    }
    int i = -1;
    do {
        buffer[++i] = fgetc(file);
    } while (buffer[i] != EOF);
    fclose(file);


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

    for(i = 0; i < 10000; i++) {
        array[i] = buffer[i];
    }

    printf("Program successfully passed its source code to shared memory\n");

    if (shmdt(array) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    return 0;
}
