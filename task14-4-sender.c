//
// Created by bananus on 06.06.22.
//
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int connection_gained = 1;

void waitConnection() {
    connection_gained = 1;
}

int main(void) {
    (void) signal(SIGUSR1, waitConnection);

    printf("[S] PID: %d\n", getpid());

    int recpid;
    printf("[S] Receiver's PID -> ");
    scanf("%d", &recpid);

    int number;
    printf("[S] Number -> ");
    scanf("%d", &number);

    for (int i = 0; i < 32; ++i) {
        if ((number & (1 << i)) == 0) {
            kill(recpid, SIGUSR1);
        } else {
            kill(recpid, SIGUSR2);
        }
        connection_gained = 0;
        while (i != 31 && connection_gained == 0) {}
    }

    printf("[S] Send number: %d to PID: %d\n", number, recpid);
    printf("[S] Exiting...\n");

    return 0;
}
