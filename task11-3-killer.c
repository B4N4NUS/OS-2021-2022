#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int msqid;
    char pathname[] = "task11-3-server.c";
    key_t key;
    int len, maxlen;
    double input;

    struct client_data {
        long mtype;
        struct {
            pid_t client_pid;
            double client_request;
        } request;
    } request_buf;

    struct server_data {
        long mtype;
        struct {
            double server_response;
        } response;
    } response_buf;

    printf("[K] Type anything and press Enter to kill server -> ");
    scanf("%lf", &input);

    if ((key = ftok(pathname, 0)) < 0) {
        printf("[K] Can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("[K] Can't get msqid\n");
        exit(-1);
    }

    request_buf.mtype = 0;
    request_buf.request.client_pid = getpid();
    request_buf.request.client_request = input;
    len = sizeof(request_buf.request);

    if (msgsnd(msqid, (struct msgbuf *) &request_buf, len, 0) < 0) {
        printf("[K] Successfully sent server a death letter\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    }
    return 0;
}
