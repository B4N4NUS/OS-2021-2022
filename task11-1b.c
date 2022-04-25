#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255

int main(void) {
    int msqid;
    char pathname[] = "task11-1a.c";
    key_t key;
    int len, maxlen;

    struct mymsgbuf {
        long mtype;
        struct {
            int iinfo;
            float finfo;
        } info;
    } mybuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("B: Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("B: Can\'t get msqid\n");
        exit(-1);
    }

    maxlen = sizeof(mybuf.info);
    while (1) {
        len = msgrcv(msqid, &mybuf, maxlen, 0, 0) < 0;
        if (len) {
            printf("B: Can\'t receive message from queue\n");
            exit(-1);
        }

        if (mybuf.mtype == LAST_MESSAGE) {
            msgctl(msqid, IPC_RMID, NULL);
            exit(0);
        }

        printf("B: Message type = %ld, integer info = %i, float info = %f\n", mybuf.mtype, mybuf.info.iinfo,
               mybuf.info.finfo);
    }
}
