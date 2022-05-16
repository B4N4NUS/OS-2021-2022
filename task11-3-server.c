#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/file.h>
#include <errno.h>

int main() {
    int msqid;
    char pathname[] = "task11-3-server.c";
    key_t key;
    int len, maxlen;

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


    int pid_file = open(pathname, O_CREAT | O_RDWR, 0666);
    int rc = flock(pid_file, LOCK_EX | LOCK_NB);
    if (rc) {
        if (EWOULDBLOCK == errno) {
            printf("[S] Another server instance was found\nShutting down...\n");
            exit(-1);
        }
    }

    if ((key = ftok(pathname, 0)) < 0) {
        printf("[S] Can't generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("[S] Can't get msqid\n");
        exit(-1);
    }

    printf("[S] Server is running\n");
    while (1) {
        maxlen = sizeof(request_buf.request);
        if (len = msgrcv(msqid, (struct msgbuf *) &request_buf, maxlen, 1, 0) < 0) {
            printf("[S] Can't receive message from queue\n");
            printf("[S] Shutting down...\n");
            exit(-1);
        }

        if (request_buf.mtype == 1) {
            response_buf.mtype = request_buf.request.client_pid;
            response_buf.response.server_response =
                    request_buf.request.client_request * request_buf.request.client_request;
            len = sizeof(response_buf.response);

            if (msgsnd(msqid, (struct msgbuf *) &response_buf, len, 0) < 0) {
                printf("[S] Server was killed\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                printf("[S] Shutting down...\n");
                exit(-1);
            }
            printf("[S] Response %lf was sent\n", response_buf.response.server_response);
        }
    }
}
