#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int msqid;
    char pathname[] = "task11-2a.c";
    key_t key;
    int len;

    struct mymsgbuf {
        long mtype;
        int iinfo;
    } mybuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("A: Can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("A: Can't get msqid\n");
        exit(-1);
    }

    mybuf.mtype = 1;
    len = sizeof(mybuf.iinfo);
    for (int i = 0; i < 5; ++i) {

        mybuf.iinfo = i*10 + i;


        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("A: Can't send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    for (int i = 1; i <= 5; ++i) {
        len = msgrcv(msqid, (struct msgbuf *) &mybuf, sizeof(mybuf.iinfo), 2, 0) < 0;
        if (len) {
            printf("A: Can't receive message from queue\n");
            exit(-1);
        }
        printf("A: Got message: type = %ld, integer info = %i\n", mybuf.mtype, mybuf.iinfo);
    }

    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);

    return 0;
}