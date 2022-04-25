#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255 // Message type for termination of program 11-1b.c

int main(void) {
    int msqid;
    char pathname[] = "task11-1a.c";
    key_t key;
    int i, len;

    struct mymsgbuf // Custom structure for the message
    {
        long mtype;
        struct {
            int iinfo;
            float finfo;
        } info;
    } mybuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("A: Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("A: Can\'t get msqid\n");
        exit(-1);
    }

    /* Send information */

    len = sizeof(mybuf.info);
    for (i = 1; i <= 5; i++) {
        mybuf.mtype = 1;
        mybuf.info.iinfo = i * 10 + i;
        mybuf.info.finfo = 1.0 / i;

        if (msgsnd(msqid, &mybuf, len, 0) < 0) {
            printf("A: Can't send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    /* Send the last message */

    mybuf.mtype = LAST_MESSAGE;
    len = 0;

    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
        printf("A: Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    return 0;
}
